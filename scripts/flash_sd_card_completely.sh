#!/bin/bash
# Usage:   ./flash_sd_card_completely.sh [ROOT_DEV] [IMAGE]
# Example: ./flash_sd_card_completely.sh sda jsd-lrb
echo "####  ./mk2parts.sh $1"
sudo ./mk2parts.sh ${1##*/}
if [[ ${1##*/} == *"mmcblk"* ]]
then
	echo "#### ./copy_boot.sh $1p"
	./copy_boot.sh ${1##*/}p
	sync
	echo "#### ./copy_rootfs.sh $1"
	./copy_rootfs.sh ${1##*/}p $2
	sync
else
	echo "#### ./copy_boot.sh $1"
	./copy_boot.sh ${1##*/}
	sync
	echo "#### ./copy_rootfs.sh $1"
	./copy_rootfs.sh ${1##*/} $2
	sync
fi
