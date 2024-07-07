FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

#SRC_URI += " \
#	file://am335x-boneblack-rootbot.dts \
#	file://rootbot-beagleboneblack.dts \
#"

#KBUILD_DEFCONFIG = "am335x-boneblack.dts"
#U_BOOT_DTBO = "am335x-boneblack.dts"

UBOOT_EXTLINUX_BOOT_FILES="extlinux/extlinux.conf     zImage         am335x-boneblack.dtb"
UBOOT_EXTLINUX_CONFIG="${WORKDIR}/extlinux.conf"
UBOOT_EXTLINUX_CONF_NAME="extlinux.conf"
UBOOT_EXTLINUX_FDT="/am335x-boneblack.dtb"
UBOOT_EXTLINUX_INSTALL_DIR="/boot/extlinux"
UBOOT_EXTLINUX_KERNEL_ARGS="rootwait rw earlycon"
UBOOT_EXTLINUX_KERNEL_IMAGE="/zImage"
UBOOT_EXTLINUX_MENU_DESCRIPTION:linux="JSD-LRB based on Poky (Yocto)"

# boot from sd card
UBOOT_EXTLINUX_ROOT="root=/dev/mmcblk0p2"

# boot via nfs/tftp
#UBOOT_EXTLINUX_ROOT="root=/dev/nfs nfsroot=192.168.5.1:/opt/nfs,vers=4 ip=192.168.5.10"
