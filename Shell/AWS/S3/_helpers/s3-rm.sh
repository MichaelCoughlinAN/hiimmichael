#!/bin/bash
set -e

if [ -z "$2" ]; then
  echo "Usage: s3-rm.sh <bucket-name> <path> [region]"
  exit 1
fi

BUCKET="$1"
TARGET="$2"
REGION="$3"

echo "Removing s3://$BUCKET/$TARGET"

aws s3 rm "s3://$BUCKET/$TARGET" \
  --recursive \
  ${REGION:+--region "$REGION"}

echo "Remove complete"
