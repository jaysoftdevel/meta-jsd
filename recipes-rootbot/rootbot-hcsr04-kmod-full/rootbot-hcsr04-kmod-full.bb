SUMMARY = "Example of how to build an external Linux kernel module"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

inherit module 

#DEPENDS = "	\
#	pasm-compiler \
#"

DISTRO_EXTRA_RDEPENDS ?= "pasm-compiler"


SRC_URI = "file://Makefile \
           file://hcsr04.c \
           file://hcsr04.h \
           file://hcsr04_FL.p \
           file://hcsr04_FC.p \
           file://hcsr04_FR.p \
           file://hcsr04_RL.p \
           file://hcsr04_RR.p \
           file://prussdrv.h \
           file://prussdrv.c \
           file://pruss_intc_mapping.h \
           file://__prussdrv.h \
          "

S = "${WORKDIR}"
export PASM_PATH = "${S}/../../../cortexa8hf-neon-poky-linux-gnueabi/pasm-compiler/1.0-r0/git/pru_sw/utils/"

#FILES_${PN} += " \
#	/lib/modules/hcsr04_FR.bin	\
#	/lib/modules/hcsr04_FC.bin	\
#	/lib/modules/hcsr04_FL.bin	\
#	/lib/modules/hcsr04_RR.bin	\
#	/lib/modules/hcsr04_RL.bin	\
#"

#do_install_append() {
#        install -m 0644 hcsr04_FR.bin ${D}/lib/modules/hcsr04_FR.bin
#        install -m 0644 hcsr04_FC.bin ${D}/lib/modules/hcsr04_FC.bin
#        install -m 0644 hcsr04_FL.bin ${D}/lib/modules/hcsr04_FL.bin
#        install -m 0644 hcsr04_RR.bin ${D}/lib/modules/hcsr04_RR.bin
#        install -m 0644 hcsr04_RL.bin ${D}/lib/modules/hcsr04_RL.bin
#}

#do_install_append() {
#    install -d ${D}${bindir}
#    install -m 0755 ${S}/hcsr04_FR.bin ${D}/lib/modules
#}

#do_install() {
#    install -m 0644 hcsr04_FR.bin ${S}/lib/modules
#}

# The inherit of module.bbclass will automatically name module packages with
# "kernel-module-" prefix as required by the oe-core build environment.
