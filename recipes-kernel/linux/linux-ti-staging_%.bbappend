inherit kernel-devicetree

FILESEXTRAPATHS_prepend := "${THISDIR}/files/dts:${THISDIR}/files/beaglebone:"

LINUX_VERSION_EXTENSION = "-jsd"

DEPENDS += "u-boot-mkimage-native dtc-native"

# Make custom kernel with PRU enabled
SRC_URI += " \
    file://bbb-pru-minimal.dts;subdir=git/arch/${ARCH}/boot/dts \
    file://am33xx.dtsi \
    file://defconfig \
"

# Add the UIO overlay to the kernel build
# NOTE: the "-overlay" suffix, paths and target is required to build .dtbo files as the
# kernel build will fail otherwise
SRC_URI += " \
    file://AM335X-PRU-UIO-00A0-overlay.dts;subdir=git/arch/${ARCH}/boot/dts/overlays \
    file://Makefile;subdir=git/arch/${ARCH}/boot/dts/overlays \
"

KERNEL_DEVICETREE = " \
   AM335X-PRU-UIO-00A0.dtbo \
   bbb-pru-minimal.dtb \
"
