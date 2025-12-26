import os
from openai import OpenAI

# Best practice: set your API key in an environment variable
# Example: export OPENAI_API_KEY="your_api_key_here"
client = OpenAI(api_key=os.getenv("OPENAI_API_KEY"))

latency_data = """
    Login: 668 ms
    DocGet: 259 ms
    DocSearch: 719 ms
    Total: 1646 ms
"""

resp = client.chat.completions.create(
    model="gpt-4o-mini",
    temperature=0.2,  # keeps wording crisp & repeatable
    messages=[
        {
            "role": "system",
            "content": (
                "You are a senior performance‑engineer. "
                "Return answers in plain‑text, no extra formatting."
            )
        },
        {
            "role": "user",
            "content": (
                "You're analyzing latency test results from a law firm's iManage document system, provided by an external vendor. "
                "Summarize the performance clearly and briefly for non-technical stakeholders. "
                "Return the result in this clean, readable format:\n\n"
                "Login: <avg>ms | DocGet: <avg>ms | DocSearch: <avg>ms | Total: <avg>ms\n"
                "Slowest Step: <op> (<avg>ms, <pct_of_total>% of total time)\n"
                "Insight: <plain-language observation about where most of the delay occurs and what it means for users>\n\n"
                "Keep the tone clear and professional, like you're giving an internal performance update. No jargon. Just one paragraph.\n\n"
                f"Latency data:\n{latency_data}"
            )
        }
    ],
    max_tokens=600
)

print()
print(resp.choices[0].message.content)

# ── cost breakdown
usage = resp.usage
prompt_tokens = usage.prompt_tokens
completion_tokens = usage.completion_tokens
total_tokens = usage.total_tokens

# GPT‑4o mini prices (July 2025):
# • $0.00000015 per input token  (15¢ per 1M) 
# • $0.00000060 per output token (60¢ per 1M)
USD_INPUT = prompt_tokens * 0.00000015
USD_OUTPUT = completion_tokens * 0.00000060
USD_TOTAL = USD_INPUT + USD_OUTPUT

print(f"\n--- Usage --------------------------------")
print(f"Total tokens:      {total_tokens}")
print(f"Cost  (${USD_TOTAL:0.6f})")
