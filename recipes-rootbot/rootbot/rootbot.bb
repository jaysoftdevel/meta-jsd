inherit externalsrc
inherit cmake

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = " \
	file://CMakeLists.txt \
	file://tester.cpp \
	file://test_client.cpp \
	file://rootbot.cpp \
	file://rootbot.h \
"

S = "${WORKDIR}"

EXTRA_OECMAKE += "-DDEBUG=ON"

DEPENDS += "rootbot-gpio nlohmann-json"

OECMAKE_GENERATOR = "Unix Makefiles"

FILES_${PN} += " \
	/ \
"

BBCLASSEXTEND = "native nativesdk"
