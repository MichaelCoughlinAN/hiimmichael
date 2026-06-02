#!/bin/bash
cd /home/ubuntu/ai-friends
echo "Starting Jordan (Anthropic)..."
nohup sudo -u ubuntu python3 bot.py friend1 > /home/ubuntu/ai-friends/logs/friend1.log 2>&1 &
echo $! > /home/ubuntu/ai-friends/pids/friend1.pid
echo "Jordan started (PID $!)"
sleep 2
echo "Starting Alex (OpenAI)..."
nohup sudo -u ubuntu python3 bot.py friend2 > /home/ubuntu/ai-friends/logs/friend2.log 2>&1 &
echo $! > /home/ubuntu/ai-friends/pids/friend2.pid
echo "Alex started (PID $!)"
sleep 2
echo "Starting Autumn (Gemini)..."
nohup sudo -u ubuntu python3 bot.py friend3 > /home/ubuntu/ai-friends/logs/friend3.log 2>&1 &
echo $! > /home/ubuntu/ai-friends/pids/friend3.pid
echo "Autumn started (PID $!)"

echo ""
echo "Done! Logs: tail -f ~/ai-friends/logs/friend1.log"
