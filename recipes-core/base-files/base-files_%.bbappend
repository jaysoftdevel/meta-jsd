FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += "file://modules.conf"

# Changing hostname did not work out with FritzBox
#export hostname = "growbot"

do_install:append() {
    install -d ${D}/etc/modules-load.d/
    install -m 0644 ${WORKDIR}/modules.conf ${D}/etc/modules-load.d/uvcvideo.conf
}
