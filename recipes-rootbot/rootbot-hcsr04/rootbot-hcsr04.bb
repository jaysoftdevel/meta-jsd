# STUFF TO BE PLACED HERE ... #

#require recipes-kernel/linux/linux-yocto.inc

#COMPATIBLE_MACHINE = "beaglebone|qemux86"

#RDEPENDS_kernel-base += "kernel-devicetree"


###############################################
# THIS RECIPE HAS NO USE AT THE MOMENT!!!!!!! #
###############################################

#inherit module externalsrc

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

#DEPENDS = "	\
#	rootbot-src \
#	"
	
#PATH_PREFIX = "${WORKDIR}/../../rootbot-src/${PV}-r0/git"
#EXTERNALSRC := "${PATH_PREFIX}/hcsr04"
#SRC_URI = "${PATH_PREFIX}/hcrs04/hcsr04.dts"
 
#S = "${WORKDIR}/git"

#APPLICATION = "st7565.ko"
#INSTALL_PREFIX = "/opt"
#DEST_PATH = "${INSTALL_PREFIX}"

#PACKAGES = "${PN}-dbg ${PN} ${PN}-dev"

#FILES_${PN} += " \
#	 ${DEST_PATH}/lib/*.a	\
#"

#do_configure(){
#	# use local source
#	echo "** ${EXTERNALSRC} ** and ${PWD}"
#	cd ${EXTERNALSRC} 
#	make        
#}

# no need to install the static lib, will just be linked against
#do_install() {
#	#install -d ${D}${DEST_PATH}/lib
#	#cp ${PATH_PREFIX}/files/MANIFEST.json ${D}${DEST_PATH}/etc/MANIFEST.json	
#	echo "** ${EXTERNALSRC} ** and ${PWD}"
#	#install -m 0755 ${EXTERNALSRC}/${APPLICATION} ${D}${DEST_PATH}/lib/
#}

 
