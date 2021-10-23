#!/bin/bash

# Michael Coughlin
# hiimmichael.com
# 2019

while true; do 
	connection = netstat -anp | grep :80 | grep ESTABLISHED | wc -l
	if [ "$connection" = 1 ]
		echo "A client has connected on port 80"
		sleep 1
	fi
done
