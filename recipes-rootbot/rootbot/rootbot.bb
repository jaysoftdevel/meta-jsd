inherit externalsrc
inherit cmake

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = " \
	file://CMakeLists.txt \
	file://rootbot.cpp \
	file://rootbot.h \
"

S = "${WORKDIR}"

DEPENDS += "rootbot-gpio nlohmann-json"

FILES_${PN} += " \
	/ \
"

BBCLASSEXTEND = "native nativesdk"
