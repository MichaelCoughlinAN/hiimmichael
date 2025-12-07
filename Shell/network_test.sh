#!/bin/bash
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &> /dev/null && pwd)"
ISROUTER="$("$SCRIPT_DIR/isrouter.sh")"

# Determine link status
if [[ "$ISROUTER" == "1" ]]; then
    "$SCRIPT_DIR/setknownhosts.sh"
    LINKSTATUS="$(/home/user/network/getrouterlinkstatus.sh)"
else
    LINKSTATUS="$(cat /sys/class/net/eth0/carrier 2>/dev/null || echo 0)"
fi

# Use a reliable public hostname to test DNS
TEST_SERVER="cloudflare.com"    # super stable, fast responses

if [[ "$LINKSTATUS" != "1" ]]; then
    echo "Ethernet port is not connected. Please check the cables, equipment, and port lights."
    exit 0
fi

echo "Ethernet port is connected."

# Display addresses
if [[ "$ISROUTER" == "1" ]]; then
    "$SCRIPT_DIR/getrouteraddress.sh" | sed 's/^/\t/'
else
    "$SCRIPT_DIR/getlocaladdress.sh" | sed 's/^/\t/'
fi

# DNS lookup for public server
echo "Looking up server $TEST_SERVER..."
LOOKUPRESULT="$(nslookup "$TEST_SERVER" 2>&1)"
LOOKUPSTATUS=$?

if [[ $LOOKUPSTATUS -eq 0 ]]; then
    echo "$LOOKUPRESULT" | grep -A5 "answer" | tail -n 2
    echo
    echo "Testing download speed…"

    # speed test using a large public test file
    wget "https://speed.cloudflare.com/__down?bytes=5000000" \
        --report-speed=bits \
        -O /dev/null 2>&1 |
        grep -E 'saved|failed' |
        sed -E 's/.*\((.*)\).*/\1/'
else
    echo "$LOOKUPRESULT" | grep -A5 "answer" | tail -n 2

    echo "Retrying with Google…"
    GOOGLELOOKUP="$(nslookup www.google.com 2>&1)"

    if [[ $? -eq 0 ]]; then
        echo "$GOOGLELOOKUP" | grep -A5 "answer" | tail -n 2
        echo "DNS is working, but the main server test failed. Your internet connection may be restricted or filtered."
    else
        echo "$GOOGLELOOKUP" | grep -A5 "answer" | tail -n 2
        echo "Unable to reach any public DNS servers. Please check your internet connection."
    fi
fi
