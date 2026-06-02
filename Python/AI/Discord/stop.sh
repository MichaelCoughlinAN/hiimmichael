#!/bin/bash
cd /home/ubuntu/ai-friends
for bot in friend1 friend2 friend3; do
    if [ -f pids/$bot.pid ]; then
        PID=$(cat pids/$bot.pid)
        kill $PID 2>/dev/null && echo "Stopped $bot (PID $PID)" || echo "$bot not running"
        rm -f /home/ubuntu/ai-friends/pids/$bot.pid
    fi
done
