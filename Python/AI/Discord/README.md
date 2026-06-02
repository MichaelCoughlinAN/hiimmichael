in one private channel as a personal support network.
They respond to you, talk to each other, and naturally trail off when you go quiet.
**Jordan** (Anthropic / Claude) — thoughtful, perceptive, asks the right question  
**Alex** (OpenAI / GPT-4o-mini) — casual, loyal, genuinely in your corner  
**Autumn** (Google / Gemini) — warm, maternal, notices when something is off  
---
## How It Works
All three bots run from the same bot.py file. The AI provider is just a config value. They share a single history.json file so everyone sees the full conversation thread.
Bot-to-bot reply probability decays each round (starts at 50%, drops by half each exchange) so conversations fade out naturally instead of looping forever.
**Cost:** roughly $1 to $3 a month total across all three APIs with casual daily use.
---
## Setup
### 1. Clone the repo
### 2. Install dependencies
bash
pip install discord.py anthropic openai google-genai

### 3. Create your Discord bots
Go to [discord.com/developers/applications](https://discord.com/developers/applications) and create three separate applications. For each one:
- Go to the **Bot** tab and click **Add Bot**
- Enable **Message Content Intent** under Privileged Gateway Intents
- Copy the bot token
- Invite the bot to your server via OAuth2 with bot scope and Send Messages + Read Message History permissions
### 4. Get your API keys
- Anthropic: [console.anthropic.com](https://console.anthropic.com)
- OpenAI: [platform.openai.com/api-keys](https://platform.openai.com/api-keys)
- Google: [aistudio.google.com/apikey](https://aistudio.google.com/apikey)
### 5. Configure
Fill in config.py with your keys, tokens, and Discord channel ID:
python
ANTHROPIC_API_KEY = "your-key"
OPENAI_API_KEY = "your-key"
GEMINI_API_KEY = "your-key"
CHANNEL_ID = 1234567890123456789  # right click your channel in Discord, Copy Channel ID. Developer Mode must be enabled in Discord.

Update the bot tokens and personality strings for each friend in the BOTS dictionary.
### 6. Run
bash
bash start.sh   # start all three bots
bash stop.sh    # stop all three bots
bash restart.sh # restart and clear history

Logs are written to logs/friend1.log, logs/friend2.log, logs/friend3.log.
---
## Auto-start on Boot (Linux)
Add bash /path/to/ai-friends/start.sh to your system startup script or create a systemd service so the bots come back online automatically after a reboot.
---
## Customization
### Change a personality
Edit the personality string for any bot in config.py. Restart for changes to take effect.
### Add a fourth bot
1. Create a new Discord bot in the Developer Portal
2. Add a new entry to the BOTS dictionary in config.py
3. Add a start/stop line in start.sh and stop.sh
All bots automatically share the same history.json — no other changes needed.
### Switch AI providers
Change the api field for any bot to anthropic, openai, or gemini.
---
## Project Structure

bot.py        # shared bot logic, all three bots run from this
config.py     # api keys, tokens, personalities, settings
start.sh      # start all bots
stop.sh       # stop all bots
restart.sh    # stop, clear history, start
logs/         # runtime logs per bot
pids/         # process id files used by stop.sh

---
## Full Writeup
Technical breakdown on the blog:  
[blog.hiimmichael.com](https://blog.hiimmichael.com)
---
Built by [Michael Coughlin](https://hiimmichael.com)
4:39 PM
Working

markdown
# AI Friends

Claude, ChatGPT, and Gemini in the same Discord channel, each with their own personality. They respond to you, talk to each other, and go quiet when you stop.

**Jordan** (Anthropic / Claude) is the thoughtful one. Perceptive, asks the right question.  
**Alex** (OpenAI / GPT-4o-mini) is casual and loyal. Actually in your corner.  
**Autumn** (Google / Gemini) is warm and maternal. Notices when something is off.

Costs about $1 to $3 a month to run all three.

---

## How It Works

All three bots run from the same `bot.py` file. The AI provider is just a config value so swapping one out is a one-line change. They share a single `history.json` so they all see the same conversation thread.

When you stop talking, the bots don't loop forever. The chance of a bot-to-bot reply drops by half each round, so the conversation naturally fades out on its own.

---

## Setup

### 1. Clone the repo

```bash
git clone https://github.com/BottleBlueLLC/Bottle-Blue-AI-Friends.git
cd Bottle-Blue-AI-Friends
```

### 2. Install dependencies

```bash
pip install discord.py anthropic openai google-genai
```

### 3. Create your Discord bots

Go to [discord.com/developers/applications](https://discord.com/developers/applications) and create three separate applications. For each one:

- Go to the **Bot** tab and click **Add Bot**
- Enable **Message Content Intent** under Privileged Gateway Intents
- Copy the bot token
- Invite it to your server via OAuth2 with `bot` scope, `Send Messages`, and `Read Message History`

### 4. Get your API keys

- Anthropic: [console.anthropic.com](https://console.anthropic.com)
- OpenAI: [platform.openai.com/api-keys](https://platform.openai.com/api-keys)
- Google: [aistudio.google.com/apikey](https://aistudio.google.com/apikey)

### 5. Configure

Fill in `config.py` with your keys, tokens, and channel ID:

```python
ANTHROPIC_API_KEY = "your-key"
OPENAI_API_KEY = "your-key"
GEMINI_API_KEY = "your-key"

CHANNEL_ID = 1234567890123456789  # right click your channel, Copy Channel ID (requires Developer Mode in Discord settings)
```

Then update the bot tokens and personality strings in the `BOTS` dictionary.

### 6. Run

```bash
bash start.sh   # start all three bots
bash stop.sh    # stop all three bots
bash restart.sh # restart and clear history
```

Logs go to `logs/friend1.log`, `logs/friend2.log`, `logs/friend3.log`.

---

## Auto-start on Boot

If you're running this on a Linux server, add the start script to your system startup or drop it into a systemd service so the bots come back online automatically after a reboot.

---

## Customization

**Change a personality** by editing the `personality` string for any bot in `config.py`. Restart to apply.

**Add a fourth bot** by creating a new Discord app, adding a new entry to the `BOTS` dictionary, and adding a line to `start.sh` and `stop.sh`. Everything else is automatic.

**Switch AI providers** by changing the `api` field for any bot to `anthropic`, `openai`, or `gemini`.

---

## Project Structure

```
bot.py        # all three bots run from this
config.py     # keys, tokens, personalities, settings
start.sh      # start all bots
stop.sh       # stop all bots
restart.sh    # stop, clear history, restart
logs/         # runtime logs
pids/         # process ids used by stop.sh
```

---

## Full Writeup

Technical breakdown, design decisions, and how it was built:  
[blog.hiimmichael.com](https://blog.hiimmichael.com)

---

Built by [Michael Coughlin](https://hiimmichael.com)
