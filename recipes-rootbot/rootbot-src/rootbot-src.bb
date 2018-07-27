SUMMARY = "little rootbot"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRCREV = "${AUTOREV}"
SRC_URI = "git://github.com/jaysoftdevel/BBB_LRB_src.git;protocol=git;branch=master"          

S = "${WORKDIR}/git"

# disable additional tasks
do_configure[noexec] = "1"
do_compile[noexec] = "1"
do_install[noexec] = "1"
