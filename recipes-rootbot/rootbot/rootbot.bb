inherit externalsrc
inherit cmake

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

inherit systemd

ACTIVE_SYSTEMD_SUPPORT = "1"
SYSTEMD_PACKAGES = "${PN}"
SYSTEMD_AUTO_ENABLE = "enable"
SYSTEMD_SERVICE_${PN} = "${PN}.service"

#SRC_URI = " \
#	file://CMakeLists.txt \
#	file://rootbot.cpp \
#	file://rootbot.hpp \
#	file://rootbot.service \
#"

EXTERNALSRC = "${THISDIR}/${PN}"
EXTERNALSRC_BUILD = "${EXTERNALSRC}/build"

EXTRA_OECMAKE += " -DDEBUG=ON"

S = "${WORKDIR}/git"

DEPENDS += "rootbot-gpio nlohmann-json"

do_install_append () {
	install -d ${D}${systemd_unitdir}/system/
	install -m 0644 ${S}/${PN}.service ${D}${systemd_unitdir}/system
}


FILES_${PN} += " \
	/ \
"

BBCLASSEXTEND = "native nativesdk"
