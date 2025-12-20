#!/bin/bash
set -e

# Guardrail: refuse to deploy helper directory
if [ "$(basename "$PWD")" = "_helpers" ]; then
  echo "Refusing to deploy from _helpers"
  exit 1
fi

if [ -z "$1" ]; then
  echo "Usage: s3-push.sh <bucket-name> [region]"
  exit 1
fi

BUCKET="$1"
REGION="$2"

echo "Pushing from $(pwd) to s3://$BUCKET"

aws s3 sync . "s3://$BUCKET" \
  --delete \
  --exclude ".git/*" \
  --exclude "node_modules/*" \
  ${REGION:+--region "$REGION"}

echo "Push complete"
