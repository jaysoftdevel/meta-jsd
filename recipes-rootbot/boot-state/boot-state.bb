LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

inherit systemd

SRC_URI = " \
	file://boot-state.service \
	file://boot-state.sh \
"

RDEPENDS_${PN} += "bash"

FILES_${PN} += " \
	${systemd_system_unitdir}/boot-state.service \
	${libexecdir}/boot-state.sh \
	"

SYSTEMD_AUTO_ENABLE = "enable"
SYSTEMD_SERVICE_${PN} = "boot-state.service"

do_install() {
  install -d ${D}${systemd_system_unitdir}
  install -m 0644 ${WORKDIR}/boot-state.service ${D}${systemd_system_unitdir}
  install -d ${D}${libexecdir}
  install -m 0755 ${WORKDIR}/boot-state.sh ${D}${libexecdir}
}

BBCLASSEXTEND = "native nativesdk"
