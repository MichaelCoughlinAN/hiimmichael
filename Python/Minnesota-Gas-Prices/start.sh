#!bin/sh

DIR=$(cd "$(dirname "$0")"; pwd) 

(trap 'kill 0' SIGINT; python3 $DIR/caseys.py & python3 $DIR/kwiktrip.py)

echo Terminated!
