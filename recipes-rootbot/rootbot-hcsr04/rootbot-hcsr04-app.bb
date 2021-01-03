# STUFF TO BE PLACED HERE ... #

inherit externalsrc

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS = "	\
	rootbot-src \
	rootbot-gpio \
	pasm-compiler \
	"
	
PATH_PREFIX = "${WORKDIR}/../../rootbot-src/${PV}-r0/git"
EXTERNALSRC := "${PATH_PREFIX}/hcsr04"
 
S = "${WORKDIR}/git"

APPLICATION = "hcsr04"
DEST_PATH = "${ROOT_HOME}"

TARGET_CC_ARCH += "${LDFLAGS}"

PACKAGES = "${PN}-dbg ${PN}-dev ${PN}"

FILES_${PN} += " \
	${DEST_PATH} \
	${DEST_PATH}/${APPLICATION}	\
"

do_compile(){
	export PASM_PATH="`pwd`/../../../pasm-compiler/1.0-r0/git/pru_sw/utils/"
	cd ${EXTERNALSRC} 
	make
}

do_install() {
	install -d ${D}${DEST_PATH}
	install -m 0755 ${EXTERNALSRC}/${APPLICATION} ${D}${DEST_PATH}
}

 
