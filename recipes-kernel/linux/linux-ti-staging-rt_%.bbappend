inherit kernel-devicetree

FILESEXTRAPATHS:prepend := "${THISDIR}/files/dts:${THISDIR}/${PN}:${THISDIR}/${PN}/ti33x:"

LINUX_VERSION_EXTENSION = "-jsd"

SRC_URI += " \
    file://defconfig \
    file://am335x-boneblack-rootbot.dts;subdir=git/arch/${ARCH}/boot/dts \
"

KERNEL_DEVICETREE = " \
   am335x-boneblack-rootbot.dtb \
"

KERNEL_FEATURES:append = "small"
