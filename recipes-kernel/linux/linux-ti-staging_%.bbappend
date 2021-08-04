inherit kernel-devicetree

FILESEXTRAPATHS_prepend := "${THISDIR}/files/dts:${THISDIR}/${PN}:"

LINUX_VERSION_EXTENSION = "-jsd"

# Make custom kernel with PRU enabled
# no need to add defconfig as its already part of SRC_URI
SRC_URI += " \
    file://bbb-pru-minimal.dts;subdir=git/arch/${ARCH}/boot/dts \
"

KERNEL_DEVICETREE = " \
   bbb-pru-minimal.dtb \
"

KERNEL_MODULE_AUTOLOAD += "uio uio-pruss"
