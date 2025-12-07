#!/bin/sh
# Increase Node.js memory limit for large builds
export NODE_OPTIONS="--max_old_space_size=16048"

# Disable generation of source maps to reduce build size
export GENERATE_SOURCEMAP=false

# Increment version number
./advance-version.sh

# Read the current version after increment
VERSION=$(cat public/version.txt)
echo "Building version: $VERSION"

# Run the build
npm run build

# Optionally, create a zip of the build directory (uncomment if needed)
# ZIP_FILE="build-$VERSION.zip"
# echo "Creating zip: $ZIP_FILE"
# zip -r "$ZIP_FILE" build/

# Optionally, you could also tag the version in git (if not done in advance-version.sh)
# git tag -a "$VERSION" -m "Release $VERSION"
# git push origin "$VERSION"
