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
INSTALL_PREFIX = "/opt"
DEST_PATH = "${INSTALL_PREFIX}"

PACKAGES = "${PN}-dbg ${PN} ${PN}-dev"

FILES_${PN} += " \
	${DEST_PATH} \
	${DEST_PATH}/*	\
"

#do_configure(){
#	# use local source
	
#	make        
#}

do_compile(){
	export PASM_PATH="`pwd`/../../../pasm-compiler/1.0-r0/git/pru_sw/utils"
	cd ${EXTERNALSRC} 
	echo "**** ${EXTERNALSRC}"
	make
}

# no need to install the static lib, will just be linked against
do_install() {
	install -d ${D}${DEST_PATH}
	install -m 0755 ${EXTERNALSRC}/${APPLICATION} ${D}${DEST_PATH}
}

 
