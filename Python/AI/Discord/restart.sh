#!/bin/bash
cd /home/ubuntu/ai-friends
echo "Restarting AI Friends..."
bash /home/ubuntu/ai-friends/stop.sh
rm -f /home/ubuntu/ai-friends/history.json
sleep 2
bash /home/ubuntu/ai-friends/start.sh
