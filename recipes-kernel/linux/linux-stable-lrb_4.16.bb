require recipes-kernel/linux/linux-yocto.inc

inherit kernel

COMPATIBLE_MACHINE = "beaglebone"

PROVIDES += "virtual/kernel"

RDEPENDS_kernel-base += "kernel-devicetree"

PACKAGE_ARCH = "${MACHINE_ARCH}"

KERNEL_DEVICETREE ?= " \
    am335x-boneblack.dtb \
    am335x-boneblack-wireless.dtb \
    bbb-jsd-lrb.dtb \
"
LINUX_VERSION = "4.16"
LINUX_VERSION_EXTENSION = "-jsd"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}-${LINUX_VERSION}:"

S = "${WORKDIR}/git"

PV = "4.16.8"
SRCREV = "dec316ea18281d2892324a4bfeb4d5a8a6605e69"
SRC_URI += " \
    git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git;branch=linux-${LINUX_VERSION}.y \
    file://defconfig \
    file://bbb-jsd-lrb.dts;subdir=git/arch/${ARCH}/boot/dts \
    file://hcsr04.dtsi;subdir=git/arch/${ARCH}/boot/dts \
"
