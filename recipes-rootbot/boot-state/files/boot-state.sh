#!/bin/bash

while $(sleep 2); do
  echo "waiting for systemd to finish booting..."
  if systemctl is-system-running | grep -qE "running|degraded"; then
    break
  fi
done

echo "  ready, waiting..." > /dev/st7565
slepp 2

/home/root/tester
echo "  prepare rootbot main..." > /dev/st7565
sleep 2
/home/root/rootbot
