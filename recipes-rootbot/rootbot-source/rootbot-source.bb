SUMMARY = "little rootbot source"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRCREV = "${AUTOREV}"
SRC_URI = "git://github.com/jaysoftdevel/BBB_LRB_src.git;protocol=https;branch=master"

S = "${WORKDIR}/git"

# disable additional tasks
do_compile[noexec] = "1"
do_install[noexec] = "1" 
do_package[noexec] = "1" 
do_packagedata[noexec] = "1"
do_package_write_rpm[noexec] = "1"
do_populate[noexec] = "1"

deltask do_compile
deltask do_install
deltask do_package
deltask do_packagedata
deltask do_package_write_rpm
deltask do_package_write_deb
deltask do_package_write_ipk
deltask do_package_write_tar
deltask do_populate

BBCLASSEXTEND = "native nativesdk" 
