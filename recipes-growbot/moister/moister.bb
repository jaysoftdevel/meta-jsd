LICENSE = "CLOSED"

SRC_URI += " \
    file://moist_log.csv \
    file://moist_logger.py \
    file://moister.service \
    "

inherit systemd

# Make sure systemd service is enabled
SYSTEMD_SERVICE:${PN} = "moister.service"

S = "${WORKDIR}"

FILES:${PN} += "/"

do_install(){
    install -d ${D}/var/www/html
    install -m 0644 ${S}/moist_logger.py ${D}/var/www/html
    #install -m 0644 ${S}/moist_log.csv ${D}/var/www/html

    # Install the systemd service
    install -d ${D}${systemd_unitdir}/system
    install -m 0644 ${WORKDIR}/moister.service ${D}${systemd_unitdir}/system/moister.service
}
