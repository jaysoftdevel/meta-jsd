inherit kernel-devicetree
inherit devicetree

FILESEXTRAPATHS_prepend := "${THISDIR}/files/dts:${THISDIR}/files/beaglebone:${THISDIR}/files:"

LINUX_VERSION_EXTENSION = "-jsd"

# Make custom kernel with PRU enabled
SRC_URI += " \
    file://bbb-pru-minimal.dts;subdir=git/arch/${ARCH}/boot/dts \
    file://defconfig \
    file://AM335X-PRU-UIO-00A0.dts;subdir=git/arch/${ARCH}/boot/dts/overlays \
    file://0001-add-UIO-dtbo.patch \
"

KERNEL_DEVICETREE = " \
   AM335X-PRU-UIO-00A0.dtbo \
   bbb-pru-minimal.dtb \
"

#KERNEL_MODULE_AUTOLOAD += ""
