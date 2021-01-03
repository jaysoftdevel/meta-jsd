FILESEXTRAPATHS_prepend := "${THISDIR}/beaglebone:"

#require  recipes-kernel/linux/ti-uio.inc
FILESEXTRAPATHS_prepend := "${THISDIR}/../../recipes-rootbot/test/bbb-pru-blinky/:"


SRC_URI += " \
    file://bbb-jsd-lrb.dts;subdir=git/arch/${ARCH}/boot/dts \
    file://AM335X-PRU-UIO-00A0.dts;subdir=git/arch/${ARCH}/boot/dts \  
    file://AM335X-PRU-RPROC-4-14-TI-00A0.dts;subdir=git/arch/${ARCH}/boot/dts \
    file://defconfig \
    file://pru.dts;subdir=git/arch/${ARCH}/boot/dts \
"

#    file://hcsr04.dtsi;subdir=git/arch/${ARCH}/boot/dts \
#    file://am335x-pru-uio.dtsi;subdir=git/arch/${ARCH}/boot/dts \
#
