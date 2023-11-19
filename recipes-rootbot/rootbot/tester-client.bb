inherit externalsrc
inherit cmake

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"


S = "${WORKDIR}/git"

EXTERNALSRC = "${THISDIR}/${PN}"
EXTERNALSRC_BUILD = "${EXTERNALSRC}/build"

EXTRA_OECMAKE += " -DDEBUG=ON"

DEPENDS += "rootbot"

OECMAKE_GENERATOR = "Unix Makefiles"

FILES:${PN} += " \
	/ \
"

BBCLASSEXTEND = "native nativesdk"
