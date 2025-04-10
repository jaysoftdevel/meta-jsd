LICENSE = "CLOSED"

SRC_URI += " \
    file://PumpController.py \
    file://runtimeServer.py \
    file://runtimeServer.service \
    file://moist_log.csv \
    file://moist_logger.py \
    "

inherit systemd

# Make sure systemd service is enabled
SYSTEMD_SERVICE:${PN} = "runtimeServer.service"

S = "${WORKDIR}"

FILES:${PN} += "/"

do_install(){
    install -d ${D}/root
    install -m 0644 ${S}/PumpController.py ${D}/root
    install -m 0644 ${S}/runtimeServer.py ${D}/root
    install -m 0644 ${S}/moist_logger.py ${D}/root
    install -m 0644 ${S}/moist_log.csv ${D}/root

    # Install the systemd service
    install -d ${D}${systemd_unitdir}/system
    install -m 0644 ${WORKDIR}/runtimeServer.service ${D}${systemd_unitdir}/system/runtimeServer.service
}
