SUMMARY = "Platform detection for use by libraries like Adafruit-Blinka."
HOMEPAGE = "https://github.com/adafruit/Adafruit_Python_PlatformDetect"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE;md5=fccd531dce4b989c05173925f0bbb76c"

SRC_URI = "https://github.com/adafruit/Adafruit_Python_PlatformDetect/archive/refs/tags/3.77.0.tar.gz;downloadfilename=Adafruit_Python_PlatformDetect-3.77.0.tar.gz"
PYPI_SRC_URI = "https://github.com/adafruit/Adafruit_Python_PlatformDetect/archive/refs/tags/3.77.0.tar.gz;downloadfilename=Adafruit_Python_PlatformDetect-3.77.0.tar.gz"
SRC_URI[sha256sum] = "b71c818ed7b3a2629447a5ed527de1325958bc0d07a8a3b72019edaff1c0809e"

S = "${WORKDIR}/Adafruit_Python_PlatformDetect-3.77.0"

#inherit setuptools3
inherit pypi

#DEPENDS += "python3-setuptools-scm-native"

#RDEPENDS:${PN} += "python3-core"
