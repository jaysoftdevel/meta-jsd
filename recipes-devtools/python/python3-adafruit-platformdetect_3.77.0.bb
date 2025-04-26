SUMMARY = "Platform detection for use by libraries like Adafruit-Blinka."
HOMEPAGE = "https://github.com/adafruit/Adafruit_Python_PlatformDetect"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE;md5=fccd531dce4b989c05173925f0bbb76c"

FILESEXTRAPATHS:prepend= "${S}/Adafruit_Python_PlatformDetect-3.77.0:"

SRC_URI = "git://github.com/adafruit/Adafruit_Python_PlatformDetect.git;branch=main;protocol=https;subdir=adafruit-platformdetect-3.77.0"
PYPI_SRC_URI = "git://github.com/adafruit/Adafruit_Python_PlatformDetect.git;branch=main;protocol=https;subdir=adafruit-platformdetect-3.77.0"
SRCREV = "${AUTOREV}"
SRC_URI[sha256sum] = "b71c818ed7b3a2629447a5ed527de1325958bc0d07a8a3b72019edaff1c0809e"

S = "${WORKDIR}/adafruit-platformdetect-3.77.0"

inherit pypi python3-dir

#INSANE_SKIP:${PN} += "license-checksum"

#DEPENDS += "python3-setuptools-scm-native"

RDEPENDS:${PN} += "python3-core"

do_install() {
    install -d ${D}${PYTHON_SITEPACKAGES_DIR}/adafruit_platformdetect
    cp -r ${S}/adafruit_platformdetect/* ${D}${PYTHON_SITEPACKAGES_DIR}/adafruit_platformdetect/
    
    # Install executable scripts from /bin
    install -d ${D}${bindir}
    install -m 0755 ${S}/bin/*.py ${D}${bindir}
}

FILES:${PN} += "/"
