inherit kernel-devicetree

FILESEXTRAPATHS_prepend := "${THISDIR}/files/dts:${THISDIR}/files/beaglebone:"

LINUX_VERSION_EXTENSION = "-jsd"

# Make custom kernel with PRU enabled
SRC_URI += " \
    file://bbb-pru-minimal.dts;subdir=git/arch/${ARCH}/boot/dts \
    file://defconfig \
"

KERNEL_DEVICETREE = " \
   bbb-pru-minimal.dtb \
"

#KERNEL_MODULE_AUTOLOAD += ""
