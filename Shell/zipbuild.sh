#!/bin/sh
# Compress all files in the build directory in place
find build -type f | while read -r file; do
    gzip -c "$file" > "$file.gz" && mv "$file.gz" "$file"
done
