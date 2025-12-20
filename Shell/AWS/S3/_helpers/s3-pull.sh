#!/bin/bash
set -e

if [ -z "$1" ]; then
  echo "Usage: s3-pull.sh <bucket-name> [region]"
  exit 1
fi

BUCKET="$1"
REGION="$2"

echo "Pulling from s3://$BUCKET"

aws s3 sync "s3://$BUCKET" . \
  --exact-timestamps \
  ${REGION:+--region "$REGION"}

echo "Pull complete"
