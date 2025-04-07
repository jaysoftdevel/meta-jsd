LICENSE = "CLOSED"

SRC_URI += " \
    file://PumpController.py \
    file://runtimeServer.py \
    file://runtimeServer.service \
    "

S = "${WORKDIR}"

FILES:${PN} += "/"

do_install(){
    install -d ${D}/root
    install -m 0644 ${S}/PumpController.py ${D}/root
    install -m 0644 ${S}/runtimeServer.py ${D}/

    # Install the systemd service
    install -d ${D}${systemd_unitdir}/system
    install -m 0644 ${WORKDIR}/runtimeServer.service ${D}${systemd_unitdir}/system/
}

# Make sure systemd service is enabled
SYSTEMD_SERVICE:${PN} = "runtimeServer.service"
