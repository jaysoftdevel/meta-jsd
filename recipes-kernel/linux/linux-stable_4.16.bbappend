FILESEXTRAPATHS_prepend := "${THISDIR}:"

SRC_URI += " \
    file://hcsr04.dtsi;subdir=git/arch/${ARCH}/boot/dts \
    file://bbb-jsd-lrb.dts;subdir=git/arch/${ARCH}/boot/dts \
    file://AM335X-PRU-UIO-00A0.dts;subdir=git/arch/${ARCH}/boot/dts \
    "

RDEPENDS_kernel-base += "kernel-devicetree"
