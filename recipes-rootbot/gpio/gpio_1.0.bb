# STUFF TO BE PLACED HERE ... #

inherit externalsrc

#SECTION = "devel"
#SCENARIO = "testScenario"
#INSTANCE = "gpio"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS = "	\	
	rootbot-src \
	"
#PATH_PREFIX = ../../
#EXTERNALSRC := "${WORKDIR}/rootbot-src/1.0-0/git/gpio/iofunc"

#PACKAGES = "${PN}-dbg ${PN} ${PN}-dev"

#APPLICAITON = "gpio"
#INSTALL_PREFIX = "/opt"
#export DEST_PATH = "${INSTALL_PREFIX}/${APPLICAITON}"

#FILES_${PN} += " \
#	 ${DEST_PATH}/*	\
#"

#FILES_${PN}-dbg += "\
#	${DEST_PATH}/bin/.debug \
#"



#do_configure(){
#	# use local source
#	echo "** ${EXTERNALSRC } **"
#	make
#}

#do_install() {
#	install -d ${D}${DEST_PATH}/bin
#	cp ${PATH_PREFIX}/files/MANIFEST.json ${D}${DEST_PATH}/etc/MANIFEST.json	
#	install -m 0755 gladosService ${D}${DEST_PATH}/bin/
#}

 
