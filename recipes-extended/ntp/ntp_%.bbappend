SRC_URI += "file://ntpd.service"
SYSROOT_DESTDIR = "${D}"

inherit systemd

do_install:append() {
    install -d ${D}${systemd_unitdir}/system
    install -m 644 ${WORKDIR}/ntpd.service ${D}${systemd_unitdir}/system/ntpd.service
}

SYSTEMD_SERVICE:${PN} += "ntpd.service"
