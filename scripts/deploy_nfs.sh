#!/bin/bash
BUILD_LOCATION="../../build/tmp/deploy/images/beaglebone/"
IMAGE_NAME="jsd-lrb-image-beaglebone.tar.xz"
KERNEL_NAME="zImage"
DTB_NAME="am335x-boneblack-rootbot.dtb"
INTERFACE="enx000ec6d96a80"
HOST_IP="192.168.5.1"

NFS_DIR="/opt/nfs"
TFTP_DIR="/opt/tftp/tftpboot"

# restart to free access to nfs folder
sudo /etc/init.d/tftpd-hpa restart
sudo /etc/init.d/nfs-kernel-server restart

# clean old installs
echo "## cleanup"
sudo rm -rvf ${TFTP_DIR}/*
sudo rm -rvf ${NFS_DIR}/*
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

echo "## assign ip addrtess and restart nfs and tftp services"
sync
sudo ifconfig ${INTERFACE} ${HOST_IP}
sudo /etc/init.d/tftpd-hpa restart
sudo /etc/init.d/nfs-kernel-server restart
