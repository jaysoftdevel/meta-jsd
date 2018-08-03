# STUFF TO BE PLACED HERE ... #

inherit externalsrc

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS = "	\
	rootbot-gpio \
	"
	
PATH_PREFIX = "${WORKDIR}/../../rootbot-src/${PV}-r0/git"
EXTERNALSRC := "${PATH_PREFIX}/stepperR"
 
S = "${WORKDIR}/git"

APPLICATION = "stepperR"
INSTALL_PREFIX = "/opt"
DEST_PATH = "${INSTALL_PREFIX}"

TARGET_CC_ARCH += "${LDFLAGS}"

PACKAGES = "${PN}-dbg ${PN}-dev ${PN}"

FILES_${PN} += " \
	${DEST_PATH} \
	${DEST_PATH}/${APPLICATION}	\
"

do_compile(){
	# use local source
	cd ${EXTERNALSRC} 
	make        
}

do_install() {
	install -d ${D}${DEST_PATH}
	install -m 0755 ${EXTERNALSRC}/${APPLICATION} ${D}${DEST_PATH}
}

 
