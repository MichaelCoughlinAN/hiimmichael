#!/usr/bin/env python3
"""
check_exposure.py

Quick tool to check whether your public IP appears "exposed" (i.e., has common ports
open to the internet) and whether your local address differs from your public IP
(quick NAT/CGNAT hint).

Usage:
    python3 check_exposure.py
    python3 check_exposure.py --ports 22,80,443 --timeout 2
    python3 check_exposure.py --range 1-2000    # BE CAREFUL: scanning large ranges may be slow/noisy

WARNING:
    Use only against your own public IP or systems you are authorized to test.
"""

import argparse
import socket
import json
import sys
import urllib.request
from concurrent.futures import ThreadPoolExecutor, as_completed
from typing import List, Tuple

DEFAULT_PORTS = [22, 23, 80, 443, 3389, 8080, 8443, 3306, 5900, 5357, 53, 137, 139, 445]

def get_public_ip(timeout=5) -> str:
    """Get public IP using ipify. Falls back to other services if needed."""
    services = [
        "https://api.ipify.org?format=json",
        "https://ifconfig.co/json",
        "https://ipinfo.io/json",
    ]
    for url in services:
        try:
            with urllib.request.urlopen(url, timeout=timeout) as resp:
                data = json.load(resp)
                # try common fields
                for key in ("ip", "ip_address", "query"):
                    if key in data:
                        return data[key]
                # fallback: sometimes 'ip' is top-level
                if isinstance(data, str):
                    return data.strip()
        except Exception:
            continue
    raise RuntimeError("Could not determine public IP (network issue?)")

def get_local_ip() -> str:
    """Return the local IP used to reach the internet (non-blocking trick)."""
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        # doesn't actually send data
        s.connect(("8.8.8.8", 80))
        return s.getsockname()[0]
    except Exception:
        # fallback to hostname lookup
        try:
            return socket.gethostbyname(socket.gethostname())
        except Exception:
            return "127.0.0.1"
    finally:
        s.close()

def parse_ports_arg(port_arg: str) -> List[int]:
    """Parse ports argument like '22,80,443' or ranges '1-1024'."""
    ports = set()
    for part in port_arg.split(","):
        part = part.strip()
        if "-" in part:
            a, b = part.split("-", 1)
            a = int(a); b = int(b)
            if a < 1 or b > 65535 or a > b:
                raise ValueError("Invalid port range")
            for p in range(a, b+1):
                ports.add(p)
        else:
            if part:
                ports.add(int(part))
    return sorted(p for p in ports if 1 <= p <= 65535)

def try_connect(host: str, port: int, timeout: float=1.5) -> Tuple[int, bool, str]:
    """Attempt a TCP connect to host:port. Returns (port, success, banner_or_error)."""
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.settimeout(timeout)
    try:
        s.connect((host, port))
        # try to recv a small banner (non-blocking)
        try:
            s.settimeout(0.6)
            data = s.recv(256)
            banner = data.decode('utf-8', errors='replace').strip()
        except Exception:
            banner = ""
        s.close()
        return (port, True, banner)
    except Exception as e:
        return (port, False, str(e))
    finally:
        try:
            s.close()
        except Exception:
            pass

def scan_ports(host: str, ports: List[int], timeout: float=1.5, workers: int=40) -> List[Tuple[int, bool, str]]:
    """Concurrently scan ports, return list of (port, open, info)."""
    results = []
    with ThreadPoolExecutor(max_workers=min(workers, max(2, len(ports)))) as ex:
        futures = {ex.submit(try_connect, host, p, timeout): p for p in ports}
        for fut in as_completed(futures):
            try:
                results.append(fut.result())
            except Exception as e:
                p = futures[fut]
                results.append((p, False, f"error: {e}"))
    results.sort(key=lambda x: x[0])
    return results

def main():
    parser = argparse.ArgumentParser(description="Check if your public IP has common ports open.")
    parser.add_argument("--ports", type=str, default=",".join(map(str, DEFAULT_PORTS)),
                        help="Comma-separated ports and/or ranges, e.g. '22,80,8000-8100'. Default common ports.")
    parser.add_argument("--timeout", type=float, default=1.5, help="Connection timeout (seconds) per port.")
    parser.add_argument("--workers", type=int, default=40, help="Number of concurrent workers.")
    parser.add_argument("--no-banner", action="store_true", help="Don't attempt to read remote banner (shorter scans).")
    args = parser.parse_args()

    try:
        public_ip = get_public_ip()
    except Exception as e:
        print("Error: couldn't fetch public IP:", e)
        sys.exit(2)

    local_ip = get_local_ip()

    print("\n--- Exposure Check — run only on your own IP ---\n")
    print(f"Your public IP:  {public_ip}")
    print(f"Your local IP:   {local_ip}")
    if public_ip == local_ip:
        print("=> Hint: your device has the public IP directly (no NAT between you and the internet).")
    else:
        print("=> Hint: your device is behind NAT (typical home router). If you forwarded ports on the router, services can still be reachable.")

    # parse ports
    try:
        ports = parse_ports_arg(args.ports)
    except Exception as e:
        print("Invalid --ports:", e)
        sys.exit(2)

    # safety: if ports count is huge, warn
    if len(ports) > 2000:
        print("\nWarning: you're scanning a very large number of ports. This can take a long time and may be noisy.")
        print("Aborting. If you really want to scan many ports, reduce the range or run a dedicated port scanner.")
        sys.exit(1)

    print(f"\nScanning {len(ports)} ports on {public_ip} (timeout {args.timeout}s) ...\n")

    results = scan_ports(public_ip, ports, timeout=args.timeout, workers=args.workers)

    open_ports = [r for r in results if r[1]]
    if not open_ports:
        print("No common ports were reachable from here. That is good (nothing obvious open).")
    else:
        print("Open ports found:")
        for port, ok, info in open_ports:
            info_str = f" — banner: {info}" if info else ""
            print(f" - {port}{info_str}")

    print("\nFull scan summary (port: status):")
    for port, ok, info in results:
        status = "OPEN" if ok else "closed"
        print(f"{port:5d} : {status}")

    print("\nNotes & next steps:")
    print("- If ports you expect to be open (e.g., you intentionally forwarded 80/443) are closed, check your router's port forwarding, your machine's firewall, and that the service is running and bound to 0.0.0.0.")
    print("- If ports are open unexpectedly: disable the service or close port forwarding on your router, or enable your host firewall (ufw / Windows Firewall).")
    print("- If your public IP equals your local IP and you're directly reachable, consider tightening firewall rules and/or contacting your ISP about security (or using a router/firewall).")
    print("- If you are behind CGNAT (you do NOT have a real public IP), port forwarding will not be possible; consider using a VPN/relay (Tailscale, Cloudflare Tunnel, ngrok) if you need inbound access.\n")

if __name__ == "__main__":
    main()
