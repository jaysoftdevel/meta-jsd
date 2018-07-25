# STUFF TO BE PLACED HERE ... #

inherit externalsrc

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS = "	\
	rootbot-src \
	"
	
PATH_PREFIX = "${WORKDIR}/../../rootbot-src/${PV}-r0/git"
EXTERNALSRC := "${PATH_PREFIX}/rootbot-gpio"
 
S = "${WORKDIR}/git"

PACKAGES = "${PN}-dbg ${PN} ${PN}-dev"

APPLICATION = "rootbot-gpio"
INSTALL_PREFIX = "/opt"
export DEST_PATH = "${INSTALL_PREFIX}/${APPLICATION}"

FILES_${PN} += " \
	 ${DEST_PATH}/*	\
"

FILES_${PN}-dbg += "\
	${DEST_PATH}/bin/.debug \
"



#do_configure(){
#	# use local source
#	echo "** ${EXTERNALSRC} ** and ${PWD}"
#	#cd ${EXTERNALSRC} 
#	#make
#}

do_install() {
	install -d ${D}${DEST_PATH}/bin
	#cp ${PATH_PREFIX}/files/MANIFEST.json ${D}${DEST_PATH}/etc/MANIFEST.json	
	install -m 0755 ${APPLICATION} ${D}${DEST_PATH}/bin/
}

 
