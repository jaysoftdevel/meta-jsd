SUMMARY = "SSD1306 OLED driver for CircuitPython"
HOMEPAGE = "https://github.com/adafruit/Adafruit_CircuitPython_SSD1306"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE;md5=df3400dd14c520e98b9192195e8b82bb"

SRC_URI = "https://github.com/adafruit/Adafruit_CircuitPython_SSD1306/archive/refs/tags/2.12.20.tar.gz;downloadfilename=adafruit-circuitpython-ssd1306-2.12.20.tar.gz"
SRC_URI[sha256sum] = "88eafea547ad65b8cccee589586100d73220706d9bcfd42d918eb58108848505"

S = "${WORKDIR}/Adafruit_CircuitPython_SSD1306-2.12.20"

inherit python_setuptools_build_meta

PEP517_BACKEND = ""

do_configure:prepend() {
    # Remove pyproject.toml to avoid setuptools-scm requirement
    rm -f ${S}/pyproject.toml

    # Inject a valid setup.py and setup.cfg
    cat > ${S}/setup.py <<EOF
from setuptools import setup
setup()
EOF

    cat > ${S}/setup.cfg <<EOF
[metadata]
name = adafruit-circuitpython-ssd1306
version = 2.12.20
description = CircuitPython driver for SSD1306 displays
license = MIT
author = Adafruit
[options]
packages = find:
install_requires =
    Adafruit-Blinka
    Adafruit-GPIO
    Adafruit-PureIO
    Pillow
EOF
}


# Required runtime dependencies
RDEPENDS:${PN} += "\
    python3-pillow \
"

# Silence QA warnings about autodetected but not declared deps (if needed)
INSANE_SKIP:${PN} += "missing-deps"
