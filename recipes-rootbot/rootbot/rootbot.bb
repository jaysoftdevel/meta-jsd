SUMMARY = "little root bot"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

# TBD seperate modules into standalone recipes
SRC_URI = "file://${THISDIR}/external_rootbot/gpio/iofunc \
           file://${THISDIR}/external_rootbot/hcsr04 \
           file://${THISDIR}/external_rootbot/stepperL \
           file://${THISDIR}/external_rootbot/stepperR \
           file://${THISDIR}/external_rootbot/lcd_kernel_module \
           file://${THISDIR}/external_rootbot/testdriver \
          "

PR = "0"

S = "${WORKDIR}"

do_install() {
    #install -d ${D}${bindir}
    #install -m 0755 cursor-on ${D}${bindir}
    echo "skip install for now"
}

FILES_${PN} = "${bindir}"
