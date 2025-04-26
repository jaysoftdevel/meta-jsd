LICENSE = "CLOSED"

SRC_URI += " \
    file://PumpController.py \
    file://runtimeServer.py \
    file://runtimeServer.service \
    file://streamHandler.py \
    "

inherit systemd

# Make sure systemd service is enabled
SYSTEMD_SERVICE:${PN} = "runtimeServer.service"

S = "${WORKDIR}"

FILES:${PN} += "/"

do_install(){
    install -d ${D}/var/www/html
    install -m 0644 ${S}/PumpController.py ${D}/var/www/html
    install -m 0644 ${S}/runtimeServer.py ${D}/var/www/html
    install -m 0644 ${S}/streamHandler.py ${D}/var/www/html

    # Install the systemd service
    install -d ${D}${systemd_unitdir}/system
    install -m 0644 ${WORKDIR}/runtimeServer.service ${D}${systemd_unitdir}/system/runtimeServer.service
}
