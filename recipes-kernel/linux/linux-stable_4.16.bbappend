FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}-${PV}/:"

SRC_URI += "file://git/arch/arm/boot/dts/hcsr04.dtsi"

COMPATIBLE_MACHINE += "|rootbot-bbb|beaglebone"

# !!! check if dtb is required or rather dts/dtsi
#KERNEL_DEVICETREE += " \
#    hcsr04.dtb \
#"

