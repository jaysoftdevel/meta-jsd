# STUFF TO BE PLACED HERE ... #

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRCREV = "${AUTOREV}"
SRC_URI = "git://github.com/beagleboard/am335x_pru_package.git;protocol=https;branch=master"

# to prevent dependency build issues
DEPENDS += "rootbot-src"

S = "${WORKDIR}/git"

do_configure(){
	# pasm compiler
	# buld locally
	cd pru_sw/utils/pasm_source
	echo "### Here: $PWD"
	./linuxbuild 2&>1 > pasm-build.log
	echo "### done..."
	cd ..
	# export var to another recipe (hcsr04) does not work somehow...
	export PASM_PATH="${S}/"
}

deltask do_compile
deltask do_install
#deltask do_package
deltask do_packagedata
deltask do_package_write_rpm
deltask do_package_write_deb
deltask do_package_write_ipk
deltask do_package_write_tar
deltask do_populate

BBCLASSEXTEND = "native nativesdk"
