#!/bin/bash
echo "####  ./mk2parts.sh $1"
sudo ./mk2parts.sh $1
echo "#### ./copy_boot.sh $1p"
./copy_boot.sh $1p
echo "#### ./copy_rootfs.sh $1"
./copy_rootfs.sh $1p $2
