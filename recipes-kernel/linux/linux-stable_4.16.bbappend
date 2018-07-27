EXTERNALSRC := "${THISDIR}/arch2/arm/boot/dts/hcsr04"
#SRC_URI += "file://hcsr04.dts"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}/dts:"

KERNEL_DEVICETREE_beaglebone += " \
    am335x-boneblack.dtb \
    am335x-boneblack-wireless.dtb \
    am335x-bonegreen.dtb \
    am335x-bonegreen-wireless.dtb \
    hcsr04.dtb \
"
