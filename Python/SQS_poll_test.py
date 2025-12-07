import os
import json
import uuid
import time
import boto3


# ----------------------------------------
# AWS CONFIG (Set these as environment vars)
# ----------------------------------------
# export AWS_REGION_NAME="ap-northeast-1"
# export SQS_QUEUE_URL="https://sqs.ap-northeast-1.amazonaws.com/123456789012/YourQueue.fifo"

AWS_REGION = os.getenv("AWS_REGION_NAME", "ap-northeast-1")
QUEUE_URL = os.getenv("SQS_QUEUE_URL")

if not QUEUE_URL:
    raise ValueError("SQS_QUEUE_URL environment variable must be set.")


# ----------------------------------------
# AWS SQS CLIENT
# ----------------------------------------
# Uses environment-provided IAM credentials (best practice)
sqs = boto3.client("sqs", region_name=AWS_REGION)


# ----------------------------------------
# MESSAGE PROCESSING LOGIC
# ----------------------------------------
def process_message(message: dict) -> None:
    """
    Processes the contents of a single SQS message.

    Args:
        message (dict): Raw SQS message.
    """
    body = json.loads(message["Body"])
    platform = body.get("platform")
    content = body.get("content")

    # Fake action: Replace with real social posting logic
    print(f"Posting to {platform}: {content}")


# ----------------------------------------
# POLLING LOOP
# ----------------------------------------
def poll_queue() -> None:
    """
    Continuously polls the SQS queue for messages.
    Uses long polling to reduce API spam and cost.
    """
    print("Starting queue polling...")

    while True:
        try:
            response = sqs.receive_message(
                QueueUrl=QUEUE_URL,
                MaxNumberOfMessages=1,
                WaitTimeSeconds=10,        # Long polling = efficient
                VisibilityTimeout=30       # Prevents double-processing
            )
        except Exception as e:
            print(f"Error receiving message: {e}")
            time.sleep(5)
            continue

        messages = response.get("Messages", [])

        if not messages:
            print("No messages. Waiting...")
            time.sleep(1)
            continue

        for message in messages:
            try:
                process_message(message)

                # Remove from the queue *after* successful processing
                sqs.delete_message(
                    QueueUrl=QUEUE_URL,
                    ReceiptHandle=message["ReceiptHandle"]
                )
                print("Message processed and deleted.")

            except Exception as e:
                # Keep it visible for retry attempts
                print(f"Error processing message: {e}")

        # Small breather between loops
        time.sleep(0.5)


# ----------------------------------------
# ENTRY POINT
# ----------------------------------------
if __name__ == "__main__":
    poll_queue()
