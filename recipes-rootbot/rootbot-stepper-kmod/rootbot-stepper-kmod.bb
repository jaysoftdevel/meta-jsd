SUMMARY = "Example of how to build an external Linux kernel module"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

# Inherit module.bbclass will automatically name module packages with
# "kernel-module-" prefix as required by the oe-core build environment.
inherit module kernel-module-split

#EXTRA_OEMAKE += "DEBUG=1"

SRC_URI = "file://Makefile \
           file://stepperL.c \
           file://stepperL.h \
           file://stepperR.c \
           file://stepperR.h \
           file://COPYING \
          "

S = "${WORKDIR}"

RPROVIDES_${PN} += "kernel-module-${PN}"

PKG_${PN} = "kernel-module-${PN}"

KERNEL_MODULE_AUTOLOAD += "${PN}"
