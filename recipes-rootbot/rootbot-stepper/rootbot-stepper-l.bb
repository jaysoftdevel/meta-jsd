# STUFF TO BE PLACED HERE ... #

inherit externalsrc

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS = "	\
	rootbot-gpio \
	"
	
PATH_PREFIX = "${WORKDIR}/../../rootbot-src/${PV}-r0/git"
EXTERNALSRC := "${PATH_PREFIX}/stepperL"
 
S = "${WORKDIR}/git"

APPLICATION = "stepperL"
INSTALL_PREFIX = "/opt"
DEST_PATH = "${INSTALL_PREFIX}"

PACKAGES = "${PN}-dbg ${PN} ${PN}-dev"

FILES_${PN} += " \
	 ${DEST_PATH}/lib/*.a	\
"

do_configure(){
	# use local source
	echo "** ${EXTERNALSRC} ** and ${PWD}"
	cd ${EXTERNALSRC} 
	make        
}

# no need to install the static lib, will just be linked against
#do_install() {
#	#install -d ${D}${DEST_PATH}/lib
#	#cp ${PATH_PREFIX}/files/MANIFEST.json ${D}${DEST_PATH}/etc/MANIFEST.json	
#	#echo "** ${EXTERNALSRC} ** and ${PWD}"
#	#install -m 0755 ${EXTERNALSRC}/${APPLICATION} ${D}${DEST_PATH}/lib/
#}

 
