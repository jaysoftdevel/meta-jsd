inherit kernel-devicetree

FILESEXTRAPATHS_prepend := "${THISDIR}/files/dts:${THISDIR}/${PN}:${THISDIR}/${PN}/ti33x:"

LINUX_VERSION_EXTENSION = "-jsd"

# Make custom kernel with PRU enabled
# no need to add defconfig as its already part of SRC_URI
SRC_URI += " \
    file://bbb-pru-minimal.dts;subdir=git/arch/${ARCH}/boot/dts \
    file://am335x-boneblack-pruadc.dts;subdir=git/arch/${ARCH}/boot/dts \
    file://am335x-boneblack-pruswuart.dts;subdir=git/arch/${ARCH}/boot/dts \
"
#    file://AM335X-PRU-RPROC-00A0.dts;subdir=git/arch/${ARCH}/boot/dts \
#    file://hcsr04.dts;subdir=git/arch/${ARCH}/boot/dts \
#

KERNEL_DEVICETREE = " \
   bbb-pru-minimal.dtb \
   am335x-boneblack-pruadc.dtb \
   am335x-boneblack-pruswuart.dtb \
"
#   AM335X-PRU-RPROC-00A0.dtbo \
#   hcsr04.dtb \
#

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
