SUMMARY = "A console development image with some C/C++ dev tools"
LICENSE = "MIT"

IMAGE_FEATURES += "package-management"
IMAGE_LINGUAS = "en-us"

inherit core-image
#inherit populate_sdk


IMAGE_INSTALL += " \
    ${CORE_OS} \
    ${DEV_SDK_INSTALL} \
    ${DEV_EXTRAS} \
    ${EXTRA_TOOLS_INSTALL} \
    ${KERNEL_EXTRA_INSTALL} \
    ${WIFI_SUPPORT} \
    ${PRU_SUPPORT} \
"

CORE_OS = " \
    openssh \
    openssh-keygen \
    openssh-sftp-server \
    psplash \
    tzdata \
    rootbot-hcsr04-app \
 "

KERNEL_EXTRA_INSTALL = " \
    kernel-modules \
    hello-mod \
    rootbot-lcd-kmod \
    rootbot-stepper-kmod \
    rootbot-hcsr04-kmod \
    "
    
#    beaglescope \
#

PRU_SUPPORT = " \
    pru-icss \
    pruss-lld \
    ti-cgt-pru \
    pru-LED0-sample \
  "   
# UIO drivers are no longer supported by TI
#uio-test-pruss \
#uio-module-drv \
#libuio \
#

WIFI_SUPPORT = " \
    crda \
    iw \
    linux-firmware-ath9k \
    linux-firmware-ralink \
    linux-firmware-rtl8192ce \
    linux-firmware-rtl8192cu \
    linux-firmware-rtl8192su \
    wireless-tools \
    wpa-supplicant \
 "                                                                                                                                               

DEV_SDK_INSTALL = " \
    binutils \
    binutils-symlinks \
    coreutils \
    cpp \
    cpp-symlinks \
    diffutils \
    file \
    g++ \
    g++-symlinks \
    gdb \
    gdbserver \
    gcc \
    gcc-symlinks \
    gettext \
    git \
    ldd \
    libstdc++ \
    libstdc++-dev \
    libtool \
    make \
    perl-modules \
    pkgconfig \
    python-modules \
 "

DEV_EXTRAS = " \
    ntp \
    ntp-tickadj \
    zeromq \
    zeromq-dev \
 "

EXTRA_TOOLS_INSTALL = " \
    \
    opkg \
    devmem2 \
    \
    acpid \
    bc \
    bzip2 \
    devmem2 \
    dosfstools \
    ethtool \
    findutils \
    i2c-tools \
    iftop \
    htop \
    less \
    memtester \
    nano \
    netcat \
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

export IMAGE_BASENAME = "jsd-lrb-image"

