# STUFF TO BE PLACED HERE ... #
SUMMARY = "Example of how to build an external Linux kernel module"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

inherit module kernel-module-split

EXTRA_OEMAKE += " DEBUG=ON"

SRC_URI = "	file://st7565.c \
			file://st7565.h \
			file://font.h \
			file://Makefile \
			file://COPYING \
			"

S = "${WORKDIR}"

RPROVIDES_${PN} += "kernel-module-st7565"
