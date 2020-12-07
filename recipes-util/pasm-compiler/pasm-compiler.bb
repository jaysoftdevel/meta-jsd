# STUFF TO BE PLACED HERE ... #

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRCREV = "${AUTOREV}"
SRC_URI = "git://github.com/beagleboard/am335x_pru_package.git;protocol=git;branch=master"

#PACKAGES ?= "${PN}-dbg ${PN} ${PN}-dev"

inherit pkgconfig

S = "${WORKDIR}/git"

do_configure(){
	# pasm compiler
	# buld locally
	cd pru_sw/utils/pasm_source
	./linuxbuild
	cd ..
	# export var to another recipe (hcsr04) does not work somehow...
	export PASM_PATH="${S}/"
}

do_compile[noexec] = "1"
do_install[noexec] = "1" 
do_package[noexec] = "1" 
do_packagedata[noexec] = "1"
do_package_write_rpm[noexec] = "1"
do_package_write_deb[noexec] = "1"
do_package_write_ipk[noexec] = "1"
do_populate[noexec] = "1" 
