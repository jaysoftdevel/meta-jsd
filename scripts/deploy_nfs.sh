#!/bin/bash

#IMAGE_NAME="jsd-lrb-image-devel-rootbot-bbb.tar.xz"
#IMAGE_NAME="jsd-lrb-image-minimal-rootbot-bbb.tar.xz"
IMAGE_NAME="jsd-lrb-profiling-image-rootbot-bbb.tar.xz"

BUILD_LOCATION="../../build/tmp/deploy/images/rootbot-bbb/"
KERNEL_NAME="zImage"
DTB_NAME="am335x-boneblack-rootbot.dtb"
INTERFACE="enx000ec6d96a80"
HOST_IP="192.168.5.1"

NFS_DIR="/opt/nfs"
TFTP_DIR="/opt/tftp/tftpboot"

# restart to free access to nfs folder
sudo /etc/init.d/tftpd-hpa stop
sudo /etc/init.d/nfs-kernel-server stop

if [ $# -eq 1 ] && [ $1 == "service" ]
then
	echo "### only restarted service"
	exit
fi

# get desired image
if [ ! -e ${BUILD_LOCATION}/${IMAGE_NAME} ]
then
	echo "### image ${BUILD_LOCATION}/${IMAGE_NAME} not found!"
	exit
fi

# clean old installs
echo "## cleanup"
sudo rm -rvf ${TFTP_DIR}/*
sudo rm -rvf ${NFS_DIR}/*
sync
echo "## cleanup done.."

# extract new image
echo "## extracting image"
sudo tar -xvf ${BUILD_LOCATION}/${IMAGE_NAME} -C ${NFS_DIR}
echo "## extracting image done..."

# copy kernel and dtb
echo "## deploy kernel"
sudo cp ${BUILD_LOCATION}/${KERNEL_NAME} ${TFTP_DIR}/
sudo cp ${BUILD_LOCATION}/${DTB_NAME} ${TFTP_DIR}/
echo "## deploy kernel done..."

# set permissions
echo "## set permissions"
sudo chmod 777 -R ${NFS_DIR}
sudo chown nobody:nogroup -R ${NFS_DIR}
sudo chmod 777 -R ${TFTP_DIR}
echo "## set permissions done..."

echo "## ${INTERFACE}: assign ip address and restart nfs and tftp services"
sync
sudo ifconfig ${INTERFACE} ${HOST_IP}
sudo /etc/init.d/tftpd-hpa start
sudo /etc/init.d/nfs-kernel-server start
