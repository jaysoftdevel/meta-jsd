SRC_URI += "file://bbb-jsd-lrb.dts;subdir=git/arch/arm/boot/dts"

COMPATIBLE_MACHINE += "|beaglebone"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}-${LINUX_VERSION}:"

LINUX_VERSION_EXTENSION = "-jsd"

PACKAGE_ARCH = "beaglebone"

KERNEL_DEVICETREE ?= " \
    bbb-jsd-lrb.dtb \
"

