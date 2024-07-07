inherit kernel-devicetree

FILESEXTRAPATHS:prepend := "${THISDIR}/files/dts:${THISDIR}/${PN}:${THISDIR}/${PN}/ti33x:"

LINUX_VERSION_EXTENSION = "-jsd"

#SRC_URI += " \
#    file://am335x-boneblack-rootbot.dts;subdir=git/arch/${ARCH}/boot/dts \
#    file://rootbot-beagleboneblack.dts;subdir=git/arch/${ARCH}/boot/dts \
#"
#file://defconfig_mini_kernel \
#

# Does not work, needs to be placed in machine config rootbot-bbb.conf
#KERNEL_DEVICETREE = " \
#   am335x-boneblack-rootbot.dtb \
#   rootbot-beagleboneblack.dtb \
#   am335x-boneblack.dtb \
#"

#KERNEL_FEATURES:append = "small"

#do_configure:prepend() {
#    cp ${WORKDIR}/defconfig_mini_kernel ${S}/.config
#}