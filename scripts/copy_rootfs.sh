#!/bin/bash

MACHINE=beaglebone
REL_SRC_DIR=../../build/tmp/deploy/images/${MACHINE}

if [ "x${1}" = "x" ]; then
	echo -e "\nUsage: ${0} <block device> [ <image-type> [<hostname>] ]\n"
	exit 0
fi

if [ ! -d /media/card ]; then
	echo "Temporary mount point [/media/card] not found"
	exit 1
fi

if [ "x${2}" = "x" ]; then
        IMAGE=console
else
        IMAGE=${2}
fi

if [ -z "$OETMP" ]; then
	echo -e "\nWorking from local directory"
	SRCDIR=.
else
	echo -e "\nOETMP: $OETMP"

	if [ ! -d ${OETMP}/deploy/images/${MACHINE} ]; then
		echo "Directory not found: ${OETMP}/deploy/images/${MACHINE}"
		exit 1
	fi

	SRCDIR=${OETMP}/${REL_SRC_DIR}/deploy/images/${MACHINE}
fi 

echo "IMAGE: $IMAGE"

if [ "x${3}" = "x" ]; then
        TARGET_HOSTNAME=$MACHINE
else
        TARGET_HOSTNAME=${3}
fi

echo -e "HOSTNAME: $TARGET_HOSTNAME\n"


if [ ! -f "${SRCDIR}/${REL_SRC_DIR}/${IMAGE}-image-${MACHINE}.tar.xz" ]; then
        echo "File not found: ${SRCDIR}/${REL_SRC_DIR}/${IMAGE}-image-${MACHINE}.tar.xz"
        exit 1
fi

DEV=/dev/${1}2

if [ -b $DEV ]; then
	echo "Formatting $DEV as ext4"
	sudo mkfs.ext4 -q -L ROOT $DEV

	echo "Mounting $DEV"
	sudo mount $DEV /media/card

	echo "Extracting ${IMAGE}-image-${MACHINE}.tar.xz to /media/card"
	sudo tar -C /media/card -xJf ${SRCDIR}/${REL_SRC_DIR}/${IMAGE}-image-${MACHINE}.tar.xz

	echo "Writing hostname to /etc/hostname"
	export TARGET_HOSTNAME
	sudo -E bash -c 'echo ${TARGET_HOSTNAME} > /media/card/etc/hostname'        

	if [ -f ${SRCDIR}/interfaces ]; then
		echo "Writing interfaces to /media/card/etc/network/"
		sudo cp ${SRCDIR}/${REL_SRC_DIR}/interfaces /media/card/etc/network/interfaces
	fi

	if [ -f ${SRCDIR}/wpa_supplicant.conf ]; then
		echo "Writing wpa_supplicant.conf to /media/card/etc/"
		sudo cp ${SRCDIR}/${REL_SRC_DIR}/wpa_supplicant.conf /media/card/etc/wpa_supplicant.conf
	fi

	echo "Unmounting $DEV"
	sudo umount $DEV
else
	echo "Block device $DEV does not exist"
fi

echo "Done"

