SUMMARY = "Example of how to build an external Linux kernel module"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

inherit module

EXTRA_OEMAKE += "DEBUG=1"

SRC_URI = "file://Makefile \
           file://hcsr04-gpio.c \
           file://hcsr04-gpio.h \
           file://COPYING \
          "

S = "${WORKDIR}"
