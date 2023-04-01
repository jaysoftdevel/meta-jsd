#!/bin/sh
# auto start wlan0 connection to local network

# check if ssid and PW had already been set
if [ ! -e /etc/wpa_supplicant.conf ]
then
	wpa_passphrase "-|-SPAM-|-" "HubSchrauberPilot" > /etc/wpa_supplicant.conf
	update-rc.d wifi.sh start 99 2 3 4 5 .
fi

wpa_supplicant -B -i wlan0 -c /etc/wpa_supplicant.conf
dhclient

