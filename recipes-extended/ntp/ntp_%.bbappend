SRC_URI += "file://ntpd.service"
SYSROOT_DESTDIR = "${D}"
do_install_append() {
    install -m 644 ${WORKDIR}/ntpd.service ${D}${sysconfdir}/systemd/system/ntpd.service
}
