#!/usr/bin/env python3

"""
hg_sync.py - Automated Mercurial Repository Sync

This script automates the process of transferring a Mercurial repository,
including all subrepositories, from one server to another. It:

1. Detects subrepositories dynamically.
2. Creates bundles for the main repo and all subrepos.
3. Copies the bundles and the .hgsub file to the remote server via SSH.
4. Initializes remote repositories if they don't exist.
5. Unbundles and updates the repositories on the remote server.
6. Uses an SSH key for passwordless authentication.

Usage:
    python3 hg_sync.py

Requirements:
- Mercurial (hg) installed on both local and remote servers.
- SSH access to the remote server.
- An SSH key configured for passwordless authentication.

Author: Your Name
"""

import os
import subprocess
import sys

# ================= CONFIG ===================
LOCAL_REPO = os.path.expanduser("~/mainrepo")
BUNDLE_DIR = os.path.join(LOCAL_REPO, "bundles")
REMOTE_REPO = "/home/ubuntu/mainrepo"
SERVER_B = "192.168.1.2" # Replace with IP Address of Server B
SSH_USER = "ubuntu"
SSH_KEY = os.path.expanduser("~/.ssh/hg_sync_key")
# ===========================================

def run(cmd):
    """Run a shell command, print it, and exit on failure."""
    print(f"[RUN] {cmd}")
    try:
        subprocess.check_call(cmd, shell=True)
    except subprocess.CalledProcessError:
        raise RuntimeError(f"Command failed: {cmd}")

def detect_subrepos():
    """Detect subrepos from .hgsub file in main repo."""
    hgsub_path = os.path.join(LOCAL_REPO, ".hgsub")
    subrepos = []
    if os.path.exists(hgsub_path):
        with open(hgsub_path) as f:
            for line in f:
                line = line.strip()
                if line and not line.startswith("#"):
                    sub_name = line.split("=")[0].strip()
                    subrepos.append(sub_name)
    return subrepos

def create_bundles(subrepos):
    """Create bundles for main repo and all subrepos."""
    os.makedirs(BUNDLE_DIR, exist_ok=True)
    print("=== Creating Bundles ===")
    # Subrepos first
    for sub in subrepos:
        sub_path = os.path.join(LOCAL_REPO, sub)
        bundle_path = os.path.join(BUNDLE_DIR, f"{sub}.hg")
        run(f"hg bundle {bundle_path} --all --repository {sub_path}")
    # Main repo
    main_bundle = os.path.join(BUNDLE_DIR, "mainrepo.hg")
    run(f"hg bundle {main_bundle} --all --repository {LOCAL_REPO}")
    return main_bundle

def copy_bundles_and_hgsub(subrepos, main_bundle):
    """Copy all bundles and .hgsub to remote server."""
    print("=== Copying Bundles and .hgsub to Remote ===")
    # Ensure main repo directory exists
    run(f"ssh -i {SSH_KEY} {SSH_USER}@{SERVER_B} 'mkdir -p {REMOTE_REPO}'")
    
    # Copy .hgsub if it exists
    hgsub_file = os.path.join(LOCAL_REPO, ".hgsub")
    if os.path.exists(hgsub_file):
        run(f"scp -i {SSH_KEY} {hgsub_file} {SSH_USER}@{SERVER_B}:{REMOTE_REPO}/")

    # Copy subrepo bundles
    for sub in subrepos:
        remote_sub_dir = os.path.join(REMOTE_REPO, sub)
        run(f"ssh -i {SSH_KEY} {SSH_USER}@{SERVER_B} 'mkdir -p {remote_sub_dir} && cd {remote_sub_dir} && hg init'")
        local_bundle = os.path.join(BUNDLE_DIR, f"{sub}.hg")
        run(f"scp -i {SSH_KEY} {local_bundle} {SSH_USER}@{SERVER_B}:{remote_sub_dir}/")

    # Copy main repo bundle
    run(f"ssh -i {SSH_KEY} {SSH_USER}@{SERVER_B} 'cd {REMOTE_REPO} && hg init'")
    run(f"scp -i {SSH_KEY} {main_bundle} {SSH_USER}@{SERVER_B}:{REMOTE_REPO}/")

def unbundle_remote(subrepos):
    """Unbundle main repo and subrepos on remote server."""
    print("=== Unbundling on Remote ===")
    # Subrepos first
    for sub in subrepos:
        remote_sub_dir = os.path.join(REMOTE_REPO, sub)
        remote_bundle = os.path.join(remote_sub_dir, f"{sub}.hg")
        run(f"ssh -i {SSH_KEY} {SSH_USER}@{SERVER_B} 'cd {remote_sub_dir} && hg unbundle {remote_bundle} && hg update --check'")
    
    # Main repo last
    main_bundle_remote = os.path.join(REMOTE_REPO, "mainrepo.hg")
    run(f"ssh -i {SSH_KEY} {SSH_USER}@{SERVER_B} 'cd {REMOTE_REPO} && hg unbundle {main_bundle_remote} && hg update -C'")

def main():
    subrepos = detect_subrepos()
    print(f"=== Detecting Subrepos ===\nFound subrepos: {subrepos}")
    
    main_bundle = create_bundles(subrepos)
    copy_bundles_and_hgsub(subrepos, main_bundle)
    unbundle_remote(subrepos)
    
    print("Transfer Complete")

if __name__ == "__main__":
    main()
