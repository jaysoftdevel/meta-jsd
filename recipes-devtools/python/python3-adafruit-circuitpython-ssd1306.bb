SUMMARY = "SSD1306 OLED driver for CircuitPython"
HOMEPAGE = "https://github.com/adafruit/Adafruit_CircuitPython_SSD1306"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE;md5=df3400dd14c520e98b9192195e8b82bb"

inherit python_setuptools_build_meta

SRC_URI = "https://github.com/adafruit/Adafruit_CircuitPython_SSD1306/archive/refs/tags/2.12.20.tar.gz;downloadfilename=adafruit-circuitpython-ssd1306-2.12.20.tar.gz"
SRC_URI[sha256sum] = "88eafea547ad65b8cccee589586100d73220706d9bcfd42d918eb58108848505"

S = "${WORKDIR}/Adafruit_CircuitPython_SSD1306-2.12.20"

RDEPENDS:${PN} += "python3-pillow"

#do_configure:prepend() {
#    sed -i '/^use_scm_version/d' ${S}/setup.cfg
#    echo "version = 2.12.20" >> ${S}/setup.cfg
#}
