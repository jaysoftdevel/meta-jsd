inherit kernel-devicetree

FILESEXTRAPATHS_prepend := "${THISDIR}/files/dts:${THISDIR}/files/beaglebone:"

LINUX_VERSION_EXTENSION = "-jsd"

SRC_URI += " \
    file://bbb-pru-minimal.dts;subdir=git/arch/${ARCH}/boot/dts \
    file://am33xx.dtsi \
    file://defconfig \
"

#    
#    \
#    file://bbb-jsd-lrb.dts;subdir=git/arch/${ARCH}/boot/dts \
#    \
#    file://pru-P8-11-P8-12.dtsi;subdir=git/arch/${ARCH}/boot/dts \
#    file://bb-gpio-hcsr04.dtsi;subdir=git/arch/${ARCH}/boot/dts \
#    file://hcsr04.dtsi;subdir=git/arch/${ARCH}/boot/dts \
#

KERNEL_DEVICETREE = " \
   bbb-pru-minimal.dtb \
"
