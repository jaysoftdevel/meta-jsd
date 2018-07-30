# STUFF TO BE PLACED HERE ... #

inherit module externalsrc

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI =   "file://st7565.c \
			file://Makefile \
			file://COPYING \
			"

S = "${WORKDIR}"

FILES_${PN} = " \
	/lib \
	/lib/modules \
"

##############################################################################################
# The following section was originally created to build the kernel module user mode/context. #
# Build fails when inheriting module. Build works as standalone based on its Makefile but    #
# currently only for the host machine. Switch to target cross compiling fails....            #
##############################################################################################

#DEPENDS = "	\
#	rootbot-src \
#	"
	
#PATH_PREFIX = "${WORKDIR}/../../rootbot-src/${PV}-r0/git"
#EXTERNALSRC := "${PATH_PREFIX}/lcd_kernel_module"
 
#S = "${WORKDIR}/git"

#APPLICATION = "st7565.ko"
#INSTALL_PREFIX = "/opt"
#DEST_PATH = "${INSTALL_PREFIX}"

#TARGET_CC_ARCH += "${LDFLAGS}"

#PACKAGES = "${PN}-dbg ${PN} ${PN}-dev"

#FILES_${PN} += " \
#	${DEST_PATH} \
#	${DEST_PATH}/${APPLICATION}	\
#"

#do_compile() {
#	# use local source
#	echo "##### compile"
#	export LCDKMOD_PATH="${EXTERNALSRC}"
#	echo "##### $LCDKMOD_PATH"
#	cd ${EXTERNALSRC} 
#	make       
#}

#do_install() {
#	install -d ${D}${DEST_PATH}/lib
#	echo "##### install"
#	install -m 0755 ${EXTERNALSRC}/${APPLICATION} ${D}${DEST_PATH}
#}

 
