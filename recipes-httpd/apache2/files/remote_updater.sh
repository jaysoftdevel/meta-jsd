#!/bin/bash
while true
do
	scp -Oq moist_log.csv root@192.168.10.20:/var/www/html/
	sleep 10
done
