FILESEXTRAPATHS_append := ":${THISDIR}/${PN}-4.16"

SRC_URI += "file://hcsr04.dts"

KERNEL_DEVICETREE_beaglebone += " \
    hcsr04.dtb \
"
