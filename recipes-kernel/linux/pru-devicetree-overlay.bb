# build dtbo target outside of kernel since overlays cannot be built by the kernel but need kernel context
inherit devicetree

FILESEXTRAPATHS:prepend := "${THISDIR}/files/dts:"

SRC_URI = " \
    file://AM335X-PRU-UIO-00A0.dts;subdir=git/overlays \
"

S = "${WORKDIR}/git/overlays"

COMPATIBLE_MACHINE = ".*(ti33x|beaglebone).*"
