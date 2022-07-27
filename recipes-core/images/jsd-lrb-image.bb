SUMMARY = "A console development image with some C/C++ dev tools"
LICENSE = "MIT"

IMAGE_FEATURES += "package-management"
IMAGE_LINGUAS = "en-us"

inherit core-image

# minimize amount of outputs during development
IMAGE_FSTYPES = "tar.xz"

DISTRO_FEATURES = " \
    nfs \
    ipv4 \
    largefile \
    wifi \
"

IMAGE_INSTALL += " \
    ${CORE_OS} \
    ${KERNEL_EXTRA_INSTALL} \
    ${PRU_SUPPORT} \
    ${DEV_SDK_INSTALL} \
    ${DEV_EXTRAS} \
    ${WIFI_SUPPORT} \
"
#    ${EXTRA_TOOLS_INSTALL} \
#

CORE_OS = " \
    openssh \
    openssh-keygen \
    hcsr04-gpio \
"
#    psplash \
#    openssh-sftp-server \
#    tzdata \
#    rootbot-hcsr04 \
#    hcsr04-rpmsg \
#

KERNEL_EXTRA_INSTALL = " \
    kernel-modules \
    rootbot-lcd-kmod \
    rootbot-stepper-kmod \
    hcsr04-gpio-kmod \
    "
# hcsr04 cannot work as kernel module since it uses user space features (e.g. file access)!!!
#    rootbot-hcsr04-kmod \
#

# Check wheather PRU modules are required at all, since its enabled in kernel already!
# FYI, pruss-lld depends on the osal extensions (uncommitted yet)
PRU_SUPPORT = " \
    pruss-lld \
    pru-icss \
  "
# TI Code generation tool
#    ti-cgt-pru \
#

# to be checked!
WIFI_SUPPORT = " \
    crda \
    iw \
    linux-firmware-ath9k \
    linux-firmware-ralink \
    linux-firmware-rtl8192ce \
    linux-firmware-rtl8192cu \
    linux-firmware-rtl8192su \
    wpa-supplicant \
"
#    wireless-tools \
#

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

KERNEL_IMAGETYPE = "zImage"

export IMAGE_BASENAME = "jsd-lrb-image"

