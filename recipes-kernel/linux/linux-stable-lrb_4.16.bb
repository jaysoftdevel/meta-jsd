require recipes-kernel/linux/linux-yocto.inc

inherit kernel

COMPATIBLE_MACHINE = "beaglebone|qemux86|rootbot-bbb"

PROVIDES += "virtual/kernel"

RDEPENDS_kernel-base += "kernel-devicetree"

PACKAGE_ARCH = "${MACHINE_ARCH}"

LINUX_VERSION = "4.16"
LINUX_VERSION_EXTENSION = "-jsd"

# Not yet tested...
#LINUX_KERNEL_TYPE = "preempt-rt"

FILESEXTRAPATHS_prepend := "${THISDIR}/beaglebone:"

S = "${WORKDIR}/git"

PV = "4.16.8"
SRCREV = "dec316ea18281d2892324a4bfeb4d5a8a6605e69"
SRC_URI += " \
    git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git;branch=linux-${LINUX_VERSION}.y \
    file://defconfig \
    file://hcsr04.dtsi;subdir=git/arch/${ARCH}/boot/dts \
    file://bbb-jsd-lrb.dts;subdir=git/arch/${ARCH}/boot/dts \
"


