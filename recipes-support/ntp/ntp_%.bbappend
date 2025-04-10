FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += " \
    file://ntpd.service \
    file://ntp.conf \
    "

SYSROOT_DESTDIR = "${D}"

inherit systemd

do_install:append() {
    install -d ${D}${systemd_unitdir}/system
    install -m 644 ${WORKDIR}/ntpd.service ${D}${systemd_unitdir}/system/ntpd.service

    install -d %{D}/etc
    install -m 0644 ${WORKDIR}/ntp.conf ${D}/etc/
}

FILES:${PN} += "/"

SYSTEMD_SERVICE:${PN} += "ntpd.service"

PACKAGES:remove = "ntp-tickadj"
RDEPENDS:${PN}:remove = "ntp-tickadj"
