# STUFF TO BE PLACED HERE ... #

inherit externalsrc

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS = "	\
	rootbot-src \
	"
	
PATH_PREFIX = "${WORKDIR}/../../rootbot-src/${PV}-r0/git"
EXTERNALSRC := "${PATH_PREFIX}/gpio"
 
S = "${WORKDIR}/git"

APPLICATION = "libiofunc.a"
INSTALL_PREFIX = "/usr/lib"
DEST_PATH = "${INSTALL_PREFIX}"

PACKAGES = "${PN}-dbg ${PN} ${PN}-dev ${PN}-staticdev"

FILES_${PN} += " \
	 ${DEST_PATH}/lib/*.a	\
"

do_configure(){
	# use local source
	cd ${EXTERNALSRC} 
	make
}

# no need to install the static lib, will just be linked against
do_install() {
	install -d ${D}${DEST_PATH}
	install -m 0755 ${EXTERNALSRC}/${APPLICATION} ${D}${DEST_PATH}
}

 
