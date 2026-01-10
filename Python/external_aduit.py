#!/usr/bin/env python3
"""
External Audit Toolkit (Non-destructive)
- No exploits, no credential stuffing, no exfil, no DoS.
- Designed for authorized external posture assessment & reporting.

Outputs:
  - report.json
  - report.md
"""

from __future__ import annotations

import argparse
import dataclasses
import datetime as dt
import json
import random
import socket
import ssl
import sys
import time
from typing import Any, Dict, List, Optional, Tuple

import requests

try:
    import dns.resolver
except ImportError:
    dns = None  # type: ignore


# ----------------------------
# Safety defaults / guardrails
# ----------------------------

DEFAULT_PORTS = [
    21, 22, 23, 25, 53, 80, 110, 143, 443, 465, 587, 993, 995,
    3389, 5900, 8080, 8443
]

SEC_HEADERS = [
    "Strict-Transport-Security",
    "Content-Security-Policy",
    "X-Frame-Options",
    "X-Content-Type-Options",
    "Referrer-Policy",
    "Permissions-Policy",
]

USER_AGENT = "ExternalAuditToolkit/1.0 (authorized; non-destructive)"


# ----------------------------
# Helpers
# ----------------------------

def now_iso() -> str:
    return dt.datetime.now(dt.timezone.utc).isoformat()

def jitter_sleep(base: float, jitter: float) -> None:
    time.sleep(max(0.0, base + random.uniform(0, jitter)))

def safe_get(url: str, timeout: float = 10.0) -> requests.Response:
    return requests.get(
        url,
        timeout=timeout,
        headers={"User-Agent": USER_AGENT},
        allow_redirects=True,
    )

def safe_head(url: str, timeout: float = 10.0) -> requests.Response:
    return requests.head(
        url,
        timeout=timeout,
        headers={"User-Agent": USER_AGENT},
        allow_redirects=True,
    )


# ----------------------------
# DNS / Email posture
# ----------------------------

def dns_query(domain: str, rtype: str) -> List[str]:
    if dns is None:
        return [f"dnspython not installed; cannot query {rtype}"]
    out: List[str] = []
    try:
        answers = dns.resolver.resolve(domain, rtype)
        for r in answers:
            out.append(str(r).strip())
    except Exception as e:
        out.append(f"ERROR: {e}")
    return out

def parse_spf_dmarc(txt_records: List[str]) -> Dict[str, Any]:
    spf = [r for r in txt_records if "v=spf1" in r.lower()]
    dmarc = [r for r in txt_records if "v=dmarc1" in r.lower()]
    return {"spf": spf, "dmarc": dmarc}

def dmarc_domain(domain: str) -> str:
    return f"_dmarc.{domain}"


# ----------------------------
# Cert Transparency (crt.sh)
# ----------------------------

def crtsh_subdomains(domain: str, timeout: float = 15.0) -> List[str]:
    """
    Passive-ish: pulls subdomains from public certificate transparency logs.
    """
    url = f"https://crt.sh/?q=%25.{domain}&output=json"
    subs: set[str] = set()
    try:
        r = requests.get(url, timeout=timeout, headers={"User-Agent": USER_AGENT})
        if r.status_code != 200:
            return [f"ERROR: crt.sh returned {r.status_code}"]
        data = r.json()
        for entry in data:
            nv = entry.get("name_value", "")
            for name in str(nv).split("\n"):
                name = name.strip().lower()
                if name.endswith(domain) and "*" not in name:
                    subs.add(name)
        return sorted(subs)
    except Exception as e:
        return [f"ERROR: {e}"]


# ----------------------------
# TCP exposure scan (small)
# ----------------------------

def tcp_connect(host: str, port: int, timeout: float) -> bool:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.settimeout(timeout)
    try:
        s.connect((host, port))
        return True
    except Exception:
        return False
    finally:
        try:
            s.close()
        except Exception:
            pass

def banner_grab_http(host: str, port: int, timeout: float = 2.0) -> Optional[str]:
    """
    Minimal banner grab for HTTP-like services.
    Sends a simple HEAD and reads a small amount.
    """
    payload = b"HEAD / HTTP/1.0\r\nHost: %b\r\nUser-Agent: %b\r\n\r\n" % (
        host.encode(), USER_AGENT.encode()
    )
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.settimeout(timeout)
    try:
        s.connect((host, port))
        s.send(payload)
        data = s.recv(1024)
        return data.decode(errors="ignore").strip() if data else None
    except Exception:
        return None
    finally:
        try:
            s.close()
        except Exception:
            pass

def scan_ports(host: str, ports: List[int], timeout: float, delay: float, jitter: float) -> Dict[int, Dict[str, Any]]:
    results: Dict[int, Dict[str, Any]] = {}
    for p in ports:
        open_ = tcp_connect(host, p, timeout=timeout)
        entry: Dict[str, Any] = {"open": open_}
        if open_ and p in (80, 8080, 8443):
            banner = banner_grab_http(host, p)
            if banner:
                entry["banner_sample"] = banner[:300]
        results[p] = entry
        jitter_sleep(delay, jitter)
    return results


# ----------------------------
# TLS posture
# ----------------------------

def tls_info(host: str, port: int = 443, timeout: float = 5.0) -> Dict[str, Any]:
    out: Dict[str, Any] = {}
    ctx = ssl.create_default_context()
    try:
        with socket.create_connection((host, port), timeout=timeout) as sock:
            with ctx.wrap_socket(sock, server_hostname=host) as ssock:
                out["tls_version"] = ssock.version()
                cipher = ssock.cipher()
                if cipher:
                    out["cipher"] = {"name": cipher[0], "protocol": cipher[1], "bits": cipher[2]}
                cert = ssock.getpeercert()
                # notAfter is like: 'Jun  3 12:00:00 2026 GMT'
                na = cert.get("notAfter")
                out["cert_not_after"] = na
                out["cert_subject"] = cert.get("subject")
                out["cert_issuer"] = cert.get("issuer")
    except Exception as e:
        out["error"] = str(e)
    return out


# ----------------------------
# HTTP posture
# ----------------------------

def http_hygiene(base_url: str) -> Dict[str, Any]:
    out: Dict[str, Any] = {"url": base_url}
    try:
        r = safe_get(base_url, timeout=10)
        out["status_code"] = r.status_code
        out["final_url"] = r.url
        out["server_header"] = r.headers.get("Server")
        out["x_powered_by"] = r.headers.get("X-Powered-By")
        out["security_headers"] = {h: r.headers.get(h) for h in SEC_HEADERS}
        out["missing_security_headers"] = [h for h in SEC_HEADERS if not r.headers.get(h)]
        # quick checks
        out["has_hsts"] = bool(r.headers.get("Strict-Transport-Security"))
        out["cookies"] = []
        for c in r.cookies:
            out["cookies"].append({"name": c.name})
    except Exception as e:
        out["error"] = str(e)
    return out

def well_known_checks(base_url: str) -> Dict[str, Any]:
    """
    Checks common files that indicate maturity: /robots.txt, /.well-known/security.txt
    """
    out: Dict[str, Any] = {}
    for path in ["/robots.txt", "/.well-known/security.txt", "/security.txt"]:
        url = base_url.rstrip("/") + path
        try:
            r = safe_get(url, timeout=10)
            out[path] = {"status_code": r.status_code}
            if r.status_code == 200:
                out[path]["sample"] = r.text[:300]
        except Exception as e:
            out[path] = {"error": str(e)}
    return out


# ----------------------------
# Gentle rate-limit presence probe
# ----------------------------

def rate_limit_probe(url: str, attempts: int = 8, base_delay: float = 0.6, jitter: float = 0.6) -> Dict[str, Any]:
    """
    Non-destructive: sends a small number of GET requests, looking for 429,
    WAF challenge codes, or headers that indicate throttling.
    """
    out: Dict[str, Any] = {"url": url, "attempts": attempts, "results": []}
    codes: List[int] = []
    for i in range(attempts):
        try:
            r = safe_get(url, timeout=10)
            codes.append(r.status_code)
            out["results"].append({
                "n": i + 1,
                "status_code": r.status_code,
                "retry_after": r.headers.get("Retry-After"),
                "cf_ray": r.headers.get("CF-RAY"),
                "server": r.headers.get("Server"),
            })
        except Exception as e:
            out["results"].append({"n": i + 1, "error": str(e)})
        jitter_sleep(base_delay, jitter)

    out["status_code_set"] = sorted(set(codes))
    out["saw_429"] = 429 in codes
    out["notes"] = "This is a small probe. Absence of 429 does not prove absence of rate limiting."
    return out


# ----------------------------
# Reporting
# ----------------------------

def severity_hints(findings: Dict[str, Any]) -> List[str]:
    hints: List[str] = []

    # Ports
    ports = findings.get("tcp_ports", {})
    if isinstance(ports, dict):
        for p, info in ports.items():
            if not isinstance(info, dict):
                continue
            if info.get("open") and int(p) in (23, 21):
                hints.append(f"CRITICAL: Insecure service exposed externally on port {p}.")
            if info.get("open") and int(p) == 3389:
                hints.append("HIGH: RDP exposed externally (3389). Ensure MFA/VPN/allowlisting.")
            if info.get("open") and int(p) == 22:
                hints.append("MED: SSH exposed externally (22). Ensure allowlisting + strong auth.")

    # Headers
    http = findings.get("http", {})
    if isinstance(http, dict):
        missing = http.get("missing_security_headers", [])
        if missing:
            hints.append(f"LOW/MED: Missing security headers: {', '.join(missing)}")

    # DMARC
    email = findings.get("email", {})
    if isinstance(email, dict):
        dmarc = email.get("dmarc", [])
        if dmarc and isinstance(dmarc, list):
            # simple policy presence check
            joined = " ".join(dmarc).lower()
            if "p=none" in joined:
                hints.append("MED/HIGH: DMARC policy is p=none (monitor-only). Consider quarantine/reject after validation.")
        else:
            hints.append("MED: No DMARC record detected (or lookup failed).")

    return hints


def markdown_report(findings: Dict[str, Any]) -> str:
    lines: List[str] = []
    lines.append(f"# External Security Posture Report\n")
    lines.append(f"- Generated: {findings.get('generated_at')}\n")
    lines.append(f"- Target: {findings.get('target')}\n")

    lines.append("## Key Findings (Hints)\n")
    hints = findings.get("hints", [])
    if hints:
        for h in hints:
            lines.append(f"- {h}")
    else:
        lines.append("- No automated severity hints produced (review raw results).")
    lines.append("")

    lines.append("## DNS & Email\n")
    email = findings.get("email", {})
    lines.append(f"- MX: {email.get('mx')}")
    lines.append(f"- SPF: {email.get('spf')}")
    lines.append(f"- DMARC: {email.get('dmarc')}\n")

    lines.append("## Subdomains (Cert Transparency)\n")
    subs = findings.get("subdomains", [])
    if isinstance(subs, list):
        for s in subs[:200]:
            lines.append(f"- {s}")
        if len(subs) > 200:
            lines.append(f"\n(Truncated; total {len(subs)} subdomains.)")
    lines.append("")

    lines.append("## TCP Exposure (Common Ports)\n")
    ports = findings.get("tcp_ports", {})
    if isinstance(ports, dict):
        for p in sorted(ports.keys(), key=lambda x: int(x)):
            info = ports[p]
            if isinstance(info, dict) and info.get("open"):
                lines.append(f"- OPEN {p}  (banner: {bool(info.get('banner_sample'))})")
    lines.append("")

    lines.append("## TLS\n")
    lines.append(f"```json\n{json.dumps(findings.get('tls', {}), indent=2)}\n```\n")

    lines.append("## HTTP Security Headers\n")
    lines.append(f"```json\n{json.dumps(findings.get('http', {}), indent=2)}\n```\n")

    lines.append("## Well-known Files\n")
    lines.append(f"```json\n{json.dumps(findings.get('well_known', {}), indent=2)}\n```\n")

    lines.append("## Gentle Rate-limit Probe\n")
    lines.append(f"```json\n{json.dumps(findings.get('rate_limit_probe', {}), indent=2)}\n```\n")

    lines.append("## Notes\n")
    lines.append("- This tool does not exploit vulnerabilities, perform credential abuse, extract data, or generate high-volume traffic.\n")
    lines.append("- Validate any potentially sensitive findings with configuration review and change control.\n")

    return "\n".join(lines)


def main() -> int:
    parser = argparse.ArgumentParser(description="External Audit Toolkit (non-destructive)")
    parser.add_argument("--target", required=True, help="Primary domain or host (e.g., furyfordwaconiamn.com)")
    parser.add_argument("--https-url", default=None, help="Base HTTPS URL (default: https://<target>)")
    parser.add_argument("--ports", default=",".join(str(p) for p in DEFAULT_PORTS),
                        help="Comma-separated ports to check (default: common ports)")
    parser.add_argument("--tcp-timeout", type=float, default=1.5, help="TCP connect timeout seconds")
    parser.add_argument("--delay", type=float, default=0.15, help="Delay between port checks")
    parser.add_argument("--jitter", type=float, default=0.25, help="Random jitter added to delays")
    parser.add_argument("--rate-probe-url", default=None, help="URL to gently probe for throttling (GET).")
    parser.add_argument("--out-json", default="report.json", help="Output JSON file")
    parser.add_argument("--out-md", default="report.md", help="Output Markdown file")
    args = parser.parse_args()

    target = args.target.strip()
    base_url = args.https_url or f"https://{target}"

    ports = []
    for x in args.ports.split(","):
        x = x.strip()
        if not x:
            continue
        try:
            ports.append(int(x))
        except ValueError:
            print(f"Invalid port: {x}", file=sys.stderr)
            return 2

    findings: Dict[str, Any] = {
        "generated_at": now_iso(),
        "target": target,
        "base_url": base_url,
        "dns": {},
        "email": {},
        "subdomains": [],
        "tcp_ports": {},
        "tls": {},
        "http": {},
        "well_known": {},
        "rate_limit_probe": {},
        "hints": [],
    }

    # DNS
    findings["dns"]["A"] = dns_query(target, "A")
    findings["dns"]["AAAA"] = dns_query(target, "AAAA")
    findings["dns"]["CNAME"] = dns_query(target, "CNAME")
    findings["email"]["mx"] = dns_query(target, "MX")
    txt = dns_query(target, "TXT")
    dmarc_txt = dns_query(dmarc_domain(target), "TXT")
    parsed = parse_spf_dmarc(txt + dmarc_txt)
    findings["email"]["spf"] = parsed["spf"]
    findings["email"]["dmarc"] = parsed["dmarc"]
    findings["email"]["txt_sample"] = (txt[:10] if isinstance(txt, list) else txt)

    # CT subdomains (passive-ish)
    findings["subdomains"] = crtsh_subdomains(target)

    # TCP ports
    findings["tcp_ports"] = {str(k): v for k, v in scan_ports(
        target, ports, timeout=args.tcp_timeout, delay=args.delay, jitter=args.jitter
    ).items()}

    # TLS
    findings["tls"] = tls_info(target, 443)

    # HTTP
    findings["http"] = http_hygiene(base_url)
    findings["well_known"] = well_known_checks(base_url)

    # Gentle rate-limit probe (optional)
    if args.rate_probe_url:
        findings["rate_limit_probe"] = rate_limit_probe(args.rate_probe_url)

    # Hints
    findings["hints"] = severity_hints(findings)

    # Write outputs
    with open(args.out_json, "w", encoding="utf-8") as f:
        json.dump(findings, f, indent=2)

    md = markdown_report(findings)
    with open(args.out_md, "w", encoding="utf-8") as f:
        f.write(md)

    print(f"Saved: {args.out_json}")
    print(f"Saved: {args.out_md}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
