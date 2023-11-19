SUMMARY = "A console development image with some C/C++ dev tools"
LICENSE = "MIT"

#IMAGE_FEATURES += "package-management"
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
	${DEV_EXTRAS} \
	${EXTRA_TOOLS_INSTALL} \
	${EXTRA_TOOLS_INSTALL_PLUS} \
"


CORE_OS = " \
    rootbot \
    tester \
    tester-stepper \
"
#boot-state \
#

# set to local.conf
#DISTRO_FEATURES_BACKFILL_CONSIDERED += "sysvinit"
#VIRTUAL-RUNTIME_init_manager = "systemd"
#VIRTUAL-RUNTIME_initscripts = "systemd-compat-units"

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
    wpa-supplicant \
"
#dhcp-client \
#    wireless-tools \
#

DEV_INSTALL = " \
    binutils \
    binutils-symlinks \
    coreutils \
    cpp \
    cpp-symlinks \
    g++ \
    g++-symlinks \
    gdb \
    gdbserver \
    gcc \
    gcc-symlinks \
    ldd \
    libstdc++ \
    libstdc++-dev \
    libtool \
    openssh \
    openssh-keygen \
     "

DEV_EXTRAS = " \
    gettext \
    git \
    diffutils \
    file \
    make \
    perl-modules \
    pkgconfig \
    ntp \
    ntp-tickadj \
    zeromq \
    zeromq-dev \
 "

EXTRA_TOOLS_INSTALL = " \
    ethtool \
    findutils \
    htop \
    less \
    procps \
    rsync \
    sysfsutils \
    util-linux \
    vim \
 "

EXTRA_TOOLS_INSTALL_PLUS = " \
    acpid \
    bc \
    bzip2 \
    devmem2 \
    dosfstools \
    i2c-tools \
    iftop \
    memtester \
    nano \
    netcat \
    tcpdump \
    unzip \
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

IMAGE_INSTALL:remove = "packagegroup-base-extended"

#CORE_IMAGE_EXTRA_INSTALL += " kernel-modules"
#packagegroup-base-wifi 
#DISTRO_FEATURES:append = " wifi"

# To be placed into local.conf!
#DISTRO_FEATURES:remove = "3g"
#DISTRO_FEATURES:remove = "alsa"
#DISTRO_FEATURES:remove = "alsa-lib"
#DISTRO_FEATURES:remove = "alsa-state"
#DISTRO_FEATURES:remove = "alsa-utils"
#DISTRO_FEATURES:remove = "bluetooth"
#DISTRO_FEATURES:remove = "bluez"
#DISTRO_FEATURES:remove = "ext2"
#DISTRO_FEATURES:remove = "gobject-introspection"
#DISTRO_FEATURES:remove = "gobject-introspection-data"
#DISTRO_FEATURES:remove = "nfc"
##DISTRO_FEATURES:remove = "nfs"
#DISTRO_FEATURES:remove = "opengl"
#DISTRO_FEATURES:remove = "pulseaudio"
#DISTRO_FEATURES:remove = "wayland"
#DISTRO_FEATURES:remove = "x11"

# To be placed into MACHINE.conf!
#MACHINE_FEATUES:remove = "alsa"
#MACHINE_FEATUES:remove = "alsa-lib"
#MACHINE_FEATUES:remove = "alsa-state"
#MACHINE_FEATUES:remove = "alsa-utils"
#MACHINE_FEATUES:remove = "apm"
#MACHINE_FEATUES:remove = "gpu"
#MACHINE_FEATUES:remove = "qemu-user-mode"

