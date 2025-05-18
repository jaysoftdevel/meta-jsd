LICENSE = "CLOSED"

SRC_URI += " \
    file://PumpController.py \
    file://runtimeServer.py \
    file://runtimeServer.service \
    file://streamHandler.py \
    file://temperatureMeasure.py \
    file://take-photo.sh \
    file://webcam-capture.service \
    file://webcam-capture.timer \
    file://add-timestamp.py \
    "

inherit systemd

# Make sure systemd service is enabled
SYSTEMD_SERVICE:${PN} += "runtimeServer.service webcam-capture.timer"

S = "${WORKDIR}"

FILES:${PN} += "/"

do_install(){
    install -d ${D}/var/www/html
    install -d ${D}/var/www/html/webcam_photos
    install -m 0644 ${S}/PumpController.py ${D}/var/www/html
    install -m 0644 ${S}/runtimeServer.py ${D}/var/www/html
    install -m 0644 ${S}/streamHandler.py ${D}/var/www/html
    install -m 0644 ${S}/temperatureMeasure.py ${D}/var/www/html
    install -m 0755 ${S}/take-photo.sh ${D}/var/www/html
    install -m 0644 ${S}/add-timestamp.py ${D}/var/www/html

    # Install the systemd service
    install -d ${D}${systemd_unitdir}/system
    install -m 0644 ${S}/runtimeServer.service ${D}${systemd_unitdir}/system/runtimeServer.service
    install -m 0644 ${S}/webcam-capture.service ${D}${systemd_system_unitdir}/webcam-capture.service
    install -m 0644 ${S}/webcam-capture.timer ${D}${systemd_system_unitdir}/webcam-capture.timer
}
