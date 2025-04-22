DESCRIPTION = "MJPG-Streamer - Live webcam streaming for embedded Linux"
HOMEPAGE = "https://github.com/jacksonliam/mjpg-streamer"
LICENSE = "CLOSED"

SRC_URI = " \
    git://github.com/jacksonliam/mjpg-streamer.git;subpath=${PN}-experimental/;branch=master \
    file://mjpg-streamer.service \
    "

SRCREV = "${AUTOREV}"

# Deploy service file
SYSTEMD_SERVICE:${PN} = "mjpg-streamer.service"
# dont autostart, only on demand!
SYSTEMD_AUTO_ENABLE:${PN} = "disable"

S = "${WORKDIR}/${PN}-experimental"

DEPENDS = "libjpeg-turbo"

inherit cmake systemd

EXTRA_OECMAKE = "-DENABLE_HTTPD=ON"

EXTRA_OECONF:append = " INPUT_PLUGINS='input_uvc.so' OUTPUT_PLUGINS='output_http.so'"

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${B}/mjpg_streamer ${D}${bindir}/mjpg_streamer

    install -d ${D}${libdir}/mjpg-streamer
    install -m 0755 ${B}/plugins/input_uvc/input_uvc.so ${D}${libdir}/mjpg-streamer/
    install -m 0755 ${B}/plugins/output_http/output_http.so ${D}${libdir}/mjpg-streamer/

    # Install web UI
    install -d ${D}${datadir}/mjpg-streamer/www
    cp -r ${S}/www/* ${D}${datadir}/mjpg-streamer/www/

    # Install systemd service
    install -D -m 0644 ${WORKDIR}/mjpg-streamer.service ${D}${systemd_unitdir}/system/mjpg-streamer.service
}

INSANE_SKIP += "license-checksum"

FILES:${PN} = "/"
