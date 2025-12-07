import os
import json
import uuid
import boto3


# -----------------------------
# AWS CONFIG (Use environment variables!)
# -----------------------------
# export AWS_ACCESS_KEY_ID="..."
# export AWS_SECRET_ACCESS_KEY="..."
# export AWS_REGION_NAME="ap-northeast-1"
# export SQS_QUEUE_URL="https://sqs.ap-northeast-1.amazonaws.com/123456789012/YourQueue.fifo"

AWS_REGION = os.getenv("AWS_REGION_NAME", "ap-northeast-1")
QUEUE_URL = os.getenv("SQS_QUEUE_URL")


# -----------------------------
# SQS CLIENT
# -----------------------------
# Relying on environment variables avoids putting credentials in source code.
sqs = boto3.client("sqs", region_name=AWS_REGION)


# -----------------------------
# SEND MESSAGE FUNCTION
# -----------------------------
def send_to_queue(data: dict) -> None:
    """
    Pushes a JSON-serializable object to an AWS SQS FIFO queue.

    Args:
        data (dict): Payload to send.

    Raises:
        ValueError: If the queue URL is not configured.
    """

    if not QUEUE_URL:
        raise ValueError("SQS_QUEUE_URL env variable is not set")

    # Convert dict → JSON string
    message_body = json.dumps(data)

    # FIFO queues need both GroupId + DeduplicationId
    dedupe_id = uuid.uuid4().hex

    response = sqs.send_message(
        QueueUrl=QUEUE_URL,
        MessageBody=message_body,
        MessageGroupId="SocialMediaGroup",
        MessageDeduplicationId=dedupe_id,
    )

    print(f"Message sent! ID: {response.get('MessageId')}")


# -----------------------------
# EXAMPLE USAGE
# -----------------------------
if __name__ == "__main__":
    example_message = {
        "platform": "twitter",
        "content": "Hello from Michael",
        "metadata": {"tags": ["#HiImMichael", "#Michael"]},
    }

    send_to_queue(example_message)
