FILES:${PN} += " \
    /boot \
    /boot/dtb \
    / \
    "
INSANE_SKIP:${PN} += "installed-vs-shipped"

inherit kernel-devicetree

FILESEXTRAPATHS:prepend := "${THISDIR}/files/dts:${THISDIR}/${PN}:${THISDIR}/${PN}/ti33x:"

LINUX_VERSION_EXTENSION = "-jsd"

SRC_URI += " \
    file://am335x-boneblack-rootbot.dts;subdir=git/arch/${ARCH}/boot/dts \
"
#    file://defconfig \
#    file://rootbot-beagleboneblack.dts;subdir=git/arch/${ARCH}/boot/dts \
#	
#

KERNEL_DEVICETREE = " \
    am335x-boneblack-rootbot.dtb \
"
#    rootbot-beagleboneblack.dtb \
#    am335x-boneblack.dtb \ 
#

#KERNEL_FEATURES:append = "small"

#do_configure:append() {
#    cp ${WORKDIR}/.config ${B}/defconfig
#}
