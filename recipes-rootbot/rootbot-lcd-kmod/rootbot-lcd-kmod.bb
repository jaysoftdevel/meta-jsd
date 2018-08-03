# STUFF TO BE PLACED HERE ... #
SUMMARY = "Example of how to build an external Linux kernel module"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=12f884d2ae1ff87c09e5b7ccc2c4ca7e"

inherit module

SRC_URI =   "file://st7565.c \
			file://font.h \
			file://lcd.h \
			file://Makefile \
			file://COPYING \
			"

PR = "r0"
S = "${WORKDIR}"

##############################################################################################
# The following section was originally created to build the kernel module user mode/context. #
# Build fails when inheriting module. Build works as standalone based on its Makefile but    #
# currently only for the host machine. Switch to target cross compiling fails....            #
##############################################################################################
#inherit externalsrc

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

 
