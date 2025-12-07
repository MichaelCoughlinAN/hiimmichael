# advance-version.py
from pathlib import Path

VERSION_FILE = Path("public/version.txt")

# Read the current version
with VERSION_FILE.open("r") as f:
    content = f.read().strip().split(".")

# Ensure the version has at least 3 parts
while len(content) < 3:
    content.append("0")

# Increment the patch version
try:
    content[2] = str(int(content[2]) + 1)
except ValueError:
    raise ValueError(f"Invalid version number in {VERSION_FILE}: {content[2]}")

# Reassemble the version string
version = ".".join(content)

# Write the new version back to file
with VERSION_FILE.open("w") as f:
    f.write(version)

print(f"Version updated to {version}")
