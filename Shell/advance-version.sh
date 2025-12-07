#!/bin/sh
set -e

# Ensure we are in the project root (optional but recommended)
# cd "$(dirname "$0")/.."

# Advance the version
python3 advance-version.py

# Read version file
VERSION_FILE="public/version.txt"

if [ ! -f "$VERSION_FILE" ]; then
    echo "Error: version file not found at $VERSION_FILE" >&2
    exit 1
fi

VERSION="$(cat "$VERSION_FILE")"

if [ -z "$VERSION" ]; then
    echo "Error: version file is empty" >&2
    exit 1
fi

echo "Version: $VERSION"

# Ensure working directory is clean
if [ -n "$(git status --porcelain)" ]; then
    echo "Warning: working directory is not clean."
    echo "Commit or stash changes before tagging."
    exit 1
fi

# Create annotated tag
if git rev-parse "$VERSION" >/dev/null 2>&1; then
    echo "Error: tag '$VERSION' already exists"
    exit 1
fi

git tag -a "$VERSION" -m "$VERSION"

# Push tag to origin
git push origin "$VERSION"
