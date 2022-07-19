# build dtbo target outside of kernel since overlays cannot be built by the kernel but need kernel context
inherit devicetree

FILESEXTRAPATHS_prepend := "${THISDIR}/files/dts:"

# only list overlays, not blobs!
SRC_URI = " \
    file://am335x-boneblack-PRU-P8-11-15.dts;subdir=git/overlays \
"

#file://BB-GPIO-HCSR04.dts;subdir=git/overlays \
#

S = "${WORKDIR}/git/overlays"

COMPATIBLE_MACHINE = ".*(ti33x|beaglebone).*"
