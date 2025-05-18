LICENSE = "CLOSED"

SRC_URI += " \
    file://moist_logger.py \
    "

inherit systemd

S = "${WORKDIR}"

FILES:${PN} += "/"

do_install(){
    install -d ${D}/var/www/html
    install -m 0644 ${S}/moist_logger.py ${D}/var/www/html
}
