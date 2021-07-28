SUMMARY = "A console development image with some C/C++ dev tools"
LICENSE = "MIT"

IMAGE_FEATURES += "package-management"
IMAGE_LINGUAS = "en-us"

inherit core-image
#inherit populate_sdk

# minimize amount of outputs during development
IMAGE_FSTYPES = "tar.xz"

IMAGE_INSTALL += " \
    ${CORE_OS} \
    ${EXTRA_TOOLS_INSTALL} \
    ${MINER_TOOLS} \
    ${WIFI_SUPPORT} \
"
    
MINER_TOOLS = " \
    kernel-modules \
    packagegroup-miners \
    cgminer-jsd \
"

CORE_OS = " \
    openssh \
    openssh-keygen \
    openssh-sftp-server \
    psplash \
    tzdata \
 "

# to be checked!
WIFI_SUPPORT = " \
    crda \
    iw \
    linux-firmware-rtl8192cu \
    wireless-tools \
    wpa-supplicant \
 "                                                                                                                                               
#    linux-firmware-rtl8192ce \
#    linux-firmware-rtl8192su \
#    linux-firmware-ath9k \
#    linux-firmware-ralink \
#

EXTRA_TOOLS_INSTALL = " \
    \
    opkg \
    devmem2 \
    \
    acpid \
    bc \
    devmem2 \
    dosfstools \
    ethtool \
    findutils \
    iftop \
    htop \
    less \
    memtester \
    nano \
    procps \
    rsync \
    sysfsutils \
    tcpdump \
    unzip \
    util-linux \
    vim \
    wget \
    zip \
 "

set_local_timezone() {
    ln -sf /usr/share/zoneinfo/EST5EDT ${IMAGE_ROOTFS}/etc/localtime
}

disable_bootlogd() {
    echo BOOTLOGD_ENABLE=no > ${IMAGE_ROOTFS}/etc/default/bootlogd
}

ROOTFS_POSTPROCESS_COMMAND += " \
    set_local_timezone ; \
 "

export IMAGE_BASENAME = "jsd-miner-image"

