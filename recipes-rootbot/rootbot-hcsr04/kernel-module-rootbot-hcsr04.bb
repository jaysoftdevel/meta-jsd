SUMMARY = "Example of how to build an external Linux kernel module"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

inherit module kernel-module-split

SRC_URI = "file://Makefile \
           file://hcsr04.c \
           file://hcsr04.h \
           file://COPYING \
          "

S = "${WORKDIR}"

RPROVIDES_${PN} += "kernel-module-rootbot-hcsr04"
