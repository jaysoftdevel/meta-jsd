#!/bin/bash

TGT_DEV="/dev/sda"
# works with static paths to ../../build/tmp/deploy/images/rootbot/*
if [ $# -eq 1 ]
then
	if [ "$1" == "devel" ] || [ "$1" == "minimal" ]
	then
		sudo umount /media/junske/boot
		sudo umount /media/junske/root
		echo "### flashing jsd-lrb-image-${1}-rootbot-bbb.wic to ${TGT_DEV}"
		sudo dd if=../../build/tmp/deploy/images/rootbot-bbb/jsd-lrb-image-${1}-rootbot-bbb.wic of=${TGT_DEV} iflag=fullblock oflag=direct bs=1M conv=fsync status=progress
		sync
	else
		echo "### only \"devel\" or \"minimal\" are supported up to now"
	fi
else
	echo "### no image type specified: minmal or devel"
fi
