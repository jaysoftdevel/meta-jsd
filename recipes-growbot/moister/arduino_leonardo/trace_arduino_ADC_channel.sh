#!/bin/sh
cat /dev/ttyACM0 | awk '{print $0","; system("")}' | tee -a ./moist_log.csv
