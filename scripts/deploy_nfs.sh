#!/bin/bash
BUILD_LOCATION="../../build/tmp/deploy/images/beaglebone/"
IMAGE_NAME="jsd-lrb-image-beaglebone.tar.xz"
KERNEL_NAME="zImage"
DTB_NAME="am335x-boneblack-rootbot.dtb"

NFS_DIR="/opt/nfs"
TFTP_DIR="/opt/tftp/tftpboot"

# clean old installs
sudo rm -rf ${NFS_DIR}/*
sudo rm -rf ${TFTP_DIR}/*

# extract new image
sudo tar -xvf ${BUILD_LOCATION}/${IMAGE_NAME} -C ${NFS_DIR}

# copy kernel and dtb
sudo cp ${BUILD_LOCATION}/${KERNEL_NAME} ${TFTP_DIR}
sudo cp ${BUILD_LOCATION}/${DTB_NAME} ${TFTP_DIR}

# set permissions
sudo chmod 777 -R ${NFS_DIR}
sudo chmod 777 -R ${TFTP_DIR}

# ?? restart servcies ??
