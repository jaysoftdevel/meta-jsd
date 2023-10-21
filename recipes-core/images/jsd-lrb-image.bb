SUMMARY = "A console development image with some C/C++ dev tools"
LICENSE = "MIT"

IMAGE_FEATURES += "package-management"
IMAGE_LINGUAS = "en-us"

inherit core-image

# minimize amount of outputs during development
#IMAGE_FSTYPES = "tar.xz wic ext4"
SDCARD_ROOTFS_rootbot-bbb = "ext4"
IMAGE_OVERHEAD_FACTOR = "1.1"
#IMAGE_ROOTFS_EXTRA_SPACE = "100000"

IMAGE_INSTALL += " \
    ${CORE_OS} \
    ${KERNEL_EXTRA_INSTALL} \
    ${WIFI_SUPPORT} \
    ${DEV_INSTALL} \
    ${EXTRA_TOOLS_INSTALL} \
"
# ${DEV_EXTRAS} \
# ${EXTRA_TOOLS_INSTALL} \
#

CORE_OS = " \
    rootbot \
    tester \
    tester-client \
    tester-stepper \
    openssh \
    openssh-keygen \
"
#boot-state \
#

# set to local.conf
#DISTRO_FEATURES_BACKFILL_CONSIDERED += "sysvinit"
#VIRTUAL-RUNTIME_init_manager = "systemd"
#VIRTUAL-RUNTIME_initscripts = "systemd-compat-units"

#DISTRO_FEATURES = " \
#    nfs \
#    ipv4 \
#    wifi \
#    systemd \
#"
#    kernel-module-st7565 \
#    kernel-module-hcsr04-gpio \
#    kernel-module-stepperL \
#    kernel-module-stepperR \
#    largefile \
#

# doublecheck naming!
KERNEL_EXTRA_INSTALL = " \
    kernel-modules \
    kernel-module-rootbot-lcd \
    kernel-module-rootbot-stepper \
    kernel-module-rootbot-hcsr04 \
    "

# to be checked!
WIFI_SUPPORT = " \
    crda \
    iw \
    linux-firmware-rtl8192cu \
    dhcp-client \
    wpa-supplicant \
"
#    wireless-tools \
#

DEV_INSTALL = " \
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

TOOLCHAIN_TARGET_TASK += " \
	kernel-devsrc \
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

export IMAGE_BASENAME = "${PN}"

#CORE_IMAGE_EXTRA_INSTALL += " kernel-modules"
#packagegroup-base-wifi 
#DISTRO_FEATURES_append = " wifi"

# To be placed into local.conf!
#DISTRO_FEATURES_remove = "3g"
#DISTRO_FEATURES_remove = "alsa"
#DISTRO_FEATURES_remove = "alsa-lib"
#DISTRO_FEATURES_remove = "alsa-state"
#DISTRO_FEATURES_remove = "alsa-utils"
#DISTRO_FEATURES_remove = "bluetooth"
#DISTRO_FEATURES_remove = "bluez"
#DISTRO_FEATURES_remove = "ext2"
#DISTRO_FEATURES_remove = "gobject-introspection"
#DISTRO_FEATURES_remove = "gobject-introspection-data"
#DISTRO_FEATURES_remove = "nfc"
##DISTRO_FEATURES_remove = "nfs"
#DISTRO_FEATURES_remove = "opengl"
#DISTRO_FEATURES_remove = "pulseaudio"
#DISTRO_FEATURES_remove = "wayland"
#DISTRO_FEATURES_remove = "x11"
#
## To be placed into MACHINE.conf!
#MACHINE_FEATUES_remove = "alsa"
#MACHINE_FEATUES_remove = "alsa-lib"
#MACHINE_FEATUES_remove = "alsa-state"
#MACHINE_FEATUES_remove = "alsa-utils"
#MACHINE_FEATUES_remove = "apm"
#MACHINE_FEATUES_remove = "gpu"
#MACHINE_FEATUES_remove = "qemu-user-mode"


