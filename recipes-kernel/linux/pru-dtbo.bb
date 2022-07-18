# build dtbo target outside of kernel since overlays cannot be built by the kernel but need kernel context
inherit devicetree

FILESEXTRAPATHS_prepend := "${THISDIR}/files/dts:"

#SRC_URI = " \
#    file://am335x-boneblack-pruadc.dts;subdir=git/overlays \
#    file://am335x-boneblack-pruswuart.dts;subdir=git/overlays \
#    file://AM335X-PRU-RPROC-00A0.dts;subdir=git/overlays \
#"

#file://BB-GPIO-HCSR04.dts;subdir=git/overlays \
#

S = "${WORKDIR}/git/overlays"

COMPATIBLE_MACHINE = ".*(ti33x|beaglebone).*"
