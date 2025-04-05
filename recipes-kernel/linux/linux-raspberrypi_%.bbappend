
FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
SRC_URI += " \ 
    file://uvc.cfg \
    "

KERNEL_MODULES += "uvcvideo"
KERNEL_EXTRA_INSTALL += "uvcvideo"
KERNEL_MODULE_AUTOLOAD += "uvcvideo"

do_configure:append() {
    #cat ${WORKDIR}/uvc.cfg >> ${S}/.config
    cat ${WORKDIR}/uvc.cfg >> ${WORKDIR}/defconfig
}
