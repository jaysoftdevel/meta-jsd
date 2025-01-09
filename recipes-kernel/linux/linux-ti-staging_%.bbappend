FILES:${PN} += " \
    /boot \
    /boot/dtb \
    / \
    "
INSANE_SKIP:${PN} += "installed-vs-shipped"

inherit kernel-devicetree

FILESEXTRAPATHS:prepend := "${THISDIR}/files/dts:${THISDIR}/${PN}:${THISDIR}/${PN}/ti33x:"

#LINUX_VERSION_EXTENSION = "-jsd"

#KERNEL_GIT_URI = "git://git.ti.com/ti-linux-kernel/ti-linux-kernel.git"

#SRC_URI:remove = "file://defconfig"
SRC_URI += " \
    file://am335x-boneblack-rootbot.dts;subdir=git/arch/${ARCH}/boot/dts \
"
#    file://.config \
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

#do_kernel_configme[noexec] = "1"
#do_configure:prepend() {
#    cp ${WORKDIR}/.config ${B}/.config
#}
