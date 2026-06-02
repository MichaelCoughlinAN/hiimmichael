# AI Friends

Three AI-powered Discord bots — each backed by a different AI company — living in one private channel as a personal support network.

They respond to you, talk to each other, and naturally trail off when you go quiet.

**Jordan** (Anthropic / Claude) — thoughtful, perceptive, asks the right question  
**Alex** (OpenAI / GPT-4o-mini) — casual, loyal, genuinely in your corner  
**Autumn** (Google / Gemini) — warm, maternal, notices when something is off  

---

## How It Works

All three bots run from the same `bot.py` file. The AI provider is just a config value. They share a single `history.json` file so everyone sees the full conversation thread.

Bot-to-bot reply probability decays each round (starts at 50%, drops by half each exchange) so conversations fade out naturally instead of looping forever.

**Cost:** roughly $1 to $3 a month total across all three APIs with casual daily use.

---

## Setup

### 1. Clone the repo

### 2. Install dependencies

```bash
pip install discord.py anthropic openai google-genai
```

### 3. Create your Discord bots

Go to [discord.com/developers/applications](https://discord.com/developers/applications) and create three separate applications. For each one:

- Go to the **Bot** tab and click **Add Bot**
- Enable **Message Content Intent** under Privileged Gateway Intents
- Copy the bot token
- Invite the bot to your server via OAuth2 with `bot` scope and `Send Messages` + `Read Message History` permissions

### 4. Get your API keys

- Anthropic: [console.anthropic.com](https://console.anthropic.com)
- OpenAI: [platform.openai.com/api-keys](https://platform.openai.com/api-keys)
- Google: [aistudio.google.com/apikey](https://aistudio.google.com/apikey)

### 5. Configure

Fill in `config.py` with your keys, tokens, and Discord channel ID:

```python
ANTHROPIC_API_KEY = "your-key"
OPENAI_API_KEY = "your-key"
GEMINI_API_KEY = "your-key"

CHANNEL_ID = 1234567890123456789  # right click your channel in Discord, Copy Channel ID. Developer Mode must be enabled in Discord.
```

Update the bot tokens and personality strings for each friend in the `BOTS` dictionary.

### 6. Run

```bash
bash start.sh   # start all three bots
bash stop.sh    # stop all three bots
bash restart.sh # restart and clear history
```

Logs are written to `logs/friend1.log`, `logs/friend2.log`, `logs/friend3.log`.

---

## Auto-start on Boot (Linux)

Add `bash /path/to/ai-friends/start.sh` to your system startup script or create a systemd service so the bots come back online automatically after a reboot.

---

## Customization

### Change a personality

Edit the `personality` string for any bot in `config.py`. Restart for changes to take effect.

### Add a fourth bot

1. Create a new Discord bot in the Developer Portal
2. Add a new entry to the `BOTS` dictionary in `config.py`
3. Add a start/stop line in `start.sh` and `stop.sh`

All bots automatically share the same `history.json` — no other changes needed.

### Switch AI providers

Change the `api` field for any bot to `anthropic`, `openai`, or `gemini`.

---

## Project Structure

```
bot.py        # shared bot logic, all three bots run from this
config.py     # api keys, tokens, personalities, settings
start.sh      # start all bots
stop.sh       # stop all bots
restart.sh    # stop, clear history, start
logs/         # runtime logs per bot
pids/         # process id files used by stop.sh
```

---

## Full Writeup

Technical breakdown, design decisions, and a live demo on the blog:  
[blog.hiimmichael.com](https://blog.hiimmichael.com)

---

Built by [Michael Coughlin](https://hiimmichael.com) / [Bottle Blue LLC](https://bottlebluellc.com)
