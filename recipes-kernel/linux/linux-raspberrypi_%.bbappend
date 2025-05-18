inherit kernel-devicetree

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += " \ 
    file://uvc.cfg \
    "

KERNEL_MODULES += "uvcvideo rtl8822 i2c-dev"
KERNEL_EXTRA_INSTALL += "uvcvideo rtl8822 i2c-dev"
KERNEL_MODULE_AUTOLOAD += "uvcvideo rtl8822 i2c-dev"

do_configure:append() {
    cat ${WORKDIR}/uvc.cfg >> ${WORKDIR}/defconfig
}
