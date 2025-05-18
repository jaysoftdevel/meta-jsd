SUMMARY = "Simple OLED Display Example using SSD1306 on RPi"
DESCRIPTION = "Displays 'Hello, RPi5!' using a 0.91in SSD1306 OLED over I2C"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/files/common-licenses/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://oled_display.py"

S = "${WORKDIR}"

DEPENDS += "python3"
RDEPENDS:${PN} += " \
    python3-core \
    python3-pillow \
"

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${S}/oled_display.py ${D}/var/www/html/oled_display.py
}
