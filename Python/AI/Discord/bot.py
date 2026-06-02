import discord
import asyncio
import random
import sys
import json
import os
import time
import re
import anthropic
from openai import OpenAI
from google import genai as google_genai
from config import BOTS, CHANNEL_ID, ANTHROPIC_API_KEY, OPENAI_API_KEY, GEMINI_API_KEY, CONTEXT_WINDOW

BOT_KEY = sys.argv[1]
BOT_CONFIG = BOTS[BOT_KEY]
NAME = BOT_CONFIG["name"]
TOKEN = BOT_CONFIG["token"]
API = BOT_CONFIG["api"]
PERSONALITY = BOT_CONFIG["personality"]
# HISTORY_FILE = os.path.join(os.path.dirname(__file__), "history.json")
# LOCK_FILE = os.path.join(os.path.dirname(__file__), "responding.lock")
HISTORY_FILE = "/home/ubuntu/ai-friends/history.json"
LOCK_FILE = "/home/ubuntu/ai-friends/responding.lock"
START_TIME = time.time()
KNOWN_NAMES = ["Michael"] + [b["name"] for b in BOTS.values()]

# Probability decays each bot exchange — resets when User speaks
bot_exchange_prob = 0.7

def load_history():
    if os.path.exists(HISTORY_FILE):
        with open(HISTORY_FILE, "r") as f:
            history = json.load(f)
        # Anthropic requires history to end with a user message
        while history and history[-1]["role"] == "assistant":
            history.pop()
        return history
    return []

def save_history(history):
    with open(HISTORY_FILE, "w") as f:
        json.dump(history[-CONTEXT_WINDOW:], f)

def append_message(role, text):
    for name in KNOWN_NAMES:
        if name != NAME:
            text = re.sub(rf"(?m)^{name}:.*$", "", text).strip()
    if not text:
        return
    history = load_history()
    history.append({"role": role, "content": text})
    save_history(history)

def acquire_lock():
    if os.path.exists(LOCK_FILE):
        age = time.time() - os.path.getmtime(LOCK_FILE)
        if age < 20:
            return False
    with open(LOCK_FILE, "w") as f:
        f.write(NAME)
    return True

def release_lock():
    if os.path.exists(LOCK_FILE):
        try:
            os.remove(LOCK_FILE)
        except:
            pass

def clean_reply(reply):
    for line in reply.strip().split("\n"):
        line = line.strip()
        if not line:
            continue
        for prefix in [NAME + ":", NAME + " :"]:
            if line.startswith(prefix):
                line = line[len(prefix):].strip()
        return line
    return reply.strip()

def has_impersonation(text):
    for name in KNOWN_NAMES:
        if name != NAME and (text.startswith(name + ":") or ("\n" + name + ":") in text):
            return True
    return False

def get_ai_response_raw(instruction):
    history = load_history()
    if not history:
        history = [{"role": "user", "content": "Michael: hey"}]
    system = (
        PERSONALITY +
        "\n\nCRITICAL RULES:\n"
        "1. ONE sentence only.\n"
        "2. Never write Michael: or pretend to be Michael.\n"
        "3. Never write any other person's name followed by a colon.\n"
        "4. You are " + NAME + " only.\n"
        "\n" + instruction
    )
    if API == "anthropic":
        ac = anthropic.Anthropic(api_key=ANTHROPIC_API_KEY)
        response = ac.messages.create(
            model="claude-sonnet-4-6",
            max_tokens=80,
            system=system,
            messages=history,
        )
        return clean_reply(response.content[0].text)
    elif API == "openai":
        oc = OpenAI(api_key=OPENAI_API_KEY)
        response = oc.chat.completions.create(
            model="gpt-4o-mini",
            max_tokens=80,
            messages=[{"role": "system", "content": system}] + history,
        )
        return clean_reply(response.choices[0].message.content)
    elif API == "gemini":
        gc = google_genai.Client(api_key=GEMINI_API_KEY)
        prompt = system + "\n\n" + "\n".join(m["content"] for m in history)
        response = gc.models.generate_content(model="gemini-2.5-flash", contents=prompt)
        return clean_reply(response.text)

def safe_reply(instruction):
    reply = get_ai_response_raw(instruction)
    if has_impersonation(reply):
        reply = get_ai_response_raw(instruction + " Only speak as " + NAME + ". No name: prefixes.")
    if has_impersonation(reply):
        lines = [l.strip() for l in reply.split("\n") if l.strip()]
        for line in lines:
            if not any(line.startswith(n + ":") for n in KNOWN_NAMES if n != NAME):
                return line
        return "..."
    return reply

intents = discord.Intents.default()
intents.message_content = True
intents.messages = True
client = discord.Client(intents=intents)

@client.event
async def on_ready():
    print(f"[{NAME}] Online as {client.user}")

@client.event
async def on_message(message):
    global bot_exchange_prob
    if message.author.id == client.user.id:
        return
    if message.channel.id != CHANNEL_ID:
        return

    is_bot = message.author.bot
    author = message.author.display_name
    print(f"[{NAME}] received message from {author}: {message.content[:50]}")
    append_message("user", author + ": " + message.content)

    if is_bot:
        if random.random() < bot_exchange_prob:
            await asyncio.sleep(random.uniform(8, 16))
            if not acquire_lock():
                return
            try:
                async with message.channel.typing():
                    reply = safe_reply("Your friend " + author + " just said something in Michael's group chat. One short natural reaction as " + NAME + ".")
                    append_message("user", NAME + ": " + reply)
                    bot_exchange_prob *= 0.55  # decay — each exchange less likely to continue
                    await message.channel.send(reply)
            finally:
                release_lock()
        return

    # Michael spoke — reset probability
    bot_exchange_prob = 0.7
    name_delay = {"Alex": 1, "Jordan": 3, "Autumn": 5}
    base_delay = name_delay.get(NAME, 2)
    await asyncio.sleep(base_delay + random.uniform(0, 2))
    if not acquire_lock():
        await asyncio.sleep(random.uniform(4, 8))
        if not acquire_lock():
            return
    try:
        async with message.channel.typing():
            reply = safe_reply("Michael just said: '" + message.content + "'. Respond directly to what Michael said as " + NAME + ". Stay on topic.")
            append_message("user", NAME + ": " + reply)
            await message.channel.send(reply)
    finally:
        release_lock()

client.run(TOKEN)
