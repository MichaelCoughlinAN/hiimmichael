import os
import requests


def send_message_to_slack(webhook_url: str, message: str) -> None:
    """
    Send a message to Slack through an incoming webhook.

    Args:
        webhook_url (str): The Slack webhook URL (should be stored securely).
        message (str): The text message to send.
    """
    if not webhook_url:
        raise ValueError("Slack webhook URL is missing.")

    payload = {"text": message}

    try:
        response = requests.post(webhook_url, json=payload, timeout=5)

        if response.status_code == 200:
            print("Message sent to Slack successfully.")
        else:
            print(f"Slack returned status {response.status_code}: {response.text}")

    except requests.RequestException as e:
        print(f"Failed to send Slack message: {e}")


if __name__ == "__main__":
    # Recommended: set this via environment variable
    # export SLACK_WEBHOOK_URL="https://hooks.slack.com/services/..."
    webhook_url = os.getenv("SLACK_WEBHOOK_URL")
    message = "Hello World"

    send_message_to_slack(webhook_url, message)
