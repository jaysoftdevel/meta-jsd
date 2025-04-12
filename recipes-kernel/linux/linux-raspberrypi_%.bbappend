inherit kernel-devicetree

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += " \ 
    file://uvc.cfg \
    "

KERNEL_MODULES += "uvcvideo rtl8192cu"
KERNEL_EXTRA_INSTALL += "uvcvideo rtl8192cu"
KERNEL_MODULE_AUTOLOAD += "uvcvideo rtl8192cu"

do_configure:append() {
    cat ${WORKDIR}/uvc.cfg >> ${WORKDIR}/defconfig
}
