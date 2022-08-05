inherit kernel-devicetree

FILESEXTRAPATHS_prepend := "${THISDIR}/files/dts:${THISDIR}/${PN}:${THISDIR}/${PN}/ti33x:"

LINUX_VERSION_EXTENSION = "-jsd"

# Make custom kernel with PRU enabled, only list blobs, not overlays!
# no need to add defconfig as its already part of SRC_URI
SRC_URI += " \
    file://am335x-boneblack-rootbot.dts;subdir=git/arch/${ARCH}/boot/dts \
"

KERNEL_DEVICETREE = " \
   am335x-boneblack-rootbot.dtb \
"

# not yet working, to be fixed!
KERNEL_MODULE_AUTOLOAD += " \
	st7565 \
	pru-rproc \
	irq-pruss-intc \
	pruss \
"

DISTRO_FEATURES += " \
	kernel-module-st7565 \
	kernel-module-pru-rproc \
	kernel-module-irq-pruss-intc \
	kernel-module-pruss \
"
