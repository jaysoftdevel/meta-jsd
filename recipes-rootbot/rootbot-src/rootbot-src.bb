SUMMARY = "little root bot"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRCREV = "${AUTOREV}"
SRC_URI = "git://github.com/jaysoftdevel/BBB_LRB_src.git;protocol=git"          

S = "${WORKDIR}/git"

do_install() {
    #install -d ${D}${bindir}
    #install -m 0755 StepperMotor_Control ${D}${bindir}
    echo "skip install for now"
}

FILES_${PN} = "${bindir}"
