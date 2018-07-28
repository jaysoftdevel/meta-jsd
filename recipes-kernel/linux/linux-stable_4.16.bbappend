FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}-4.16/:"

SRC_URI += "file://git/arch/arm/boot/dts/hcsr04.dts"

KERNEL_DEVICETREE += " \
    hcsr04.dtb \
"

