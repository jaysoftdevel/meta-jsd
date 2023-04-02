#!/bin/sh
# auto start wlan0 connection to local network

# check if ssid and PW were already set
if [ ! `grep "SPAM" /etc/wpa_supplicant.conf` ]
then
	wpa_passphrase "-|-SPAM-|-" "HubSchrauberPilot" > /etc/wpa_supplicant.conf
fi

wpa_supplicant -B -i wlan0 -c /etc/wpa_supplicant.conf
dhclient

