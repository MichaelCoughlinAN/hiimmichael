#!/bin/bash

# Host to connect to — replace with your actual public server
TARGET_HOST="example.com"

# Remove existing entry from known_hosts
ssh-keygen -f "$HOME/.ssh/known_hosts" -R "$TARGET_HOST" >/dev/null

# Establish SSH connection (backgrounded)
ssh -o StrictHostKeyChecking=accept-new \
    -o PasswordAuthentication=no \
    "$TARGET_HOST" -N &
