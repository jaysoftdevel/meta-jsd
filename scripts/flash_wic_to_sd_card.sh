#!/bin/bash

TGT_DEV="/dev/sda"
IMG_FILE="jsd-lrb-image-${1}-rootbot-bbb.wic"
#IMG_FILE="core-image-minimal-rootbot-bbb.wic"
IMG_PATH="../../build/tmp/deploy/images/rootbot-bbb/${IMG_FILE}"
# works with static paths to ../../build/tmp/deploy/images/rootbot/*
if [ $# -eq 1 ]
then
	if [ "$1" == "devel" ] || [ "$1" == "minimal" ]
	then
		sudo umount /media/junske/boot
		sudo umount /media/junske/root
		echo "### flashing ${IMG_FILE} with a size of `realpath ${IMG_PATH}|xargs ls -lh|cut -d " " -f 5` to ${TGT_DEV}"
		sudo dd if=${IMG_PATH} of=${TGT_DEV} iflag=fullblock oflag=direct bs=1M conv=fsync status=progress
		sync
	else
		echo "### only \"devel\" or \"minimal\" are supported up to now"
	fi
else
	echo "### no image type specified: minmal or devel"
fi
