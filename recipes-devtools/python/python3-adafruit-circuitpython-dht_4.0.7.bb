SUMMARY = "Adafruit DHT Sensor Library for CircuitPython"
DESCRIPTION = "Library for DHT11, DHT22, and AM2302 temperature and humidity sensors."
HOMEPAGE = "https://github.com/adafruit/Adafruit_CircuitPython_DHT"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE;md5=0f658f5fc6fe8c31c8c33de38c94c843"

SRC_URI = "https://github.com/adafruit/Adafruit_CircuitPython_DHT/archive/refs/tags/4.0.7.tar.gz;downloadfilename=Adafruit_CircuitPython_DHT-4.0.7.tar.gz"
PYPI_SRC_URI = "https://github.com/adafruit/Adafruit_CircuitPython_DHT/archive/refs/tags/4.0.7.tar.gz;downloadfilename=Adafruit_CircuitPython_DHT-4.0.7.tar.gz"
SRC_URI[sha256sum] = "0a81d0b3e91c775f7ac98765f3707cb5b7c62448c33c3d3c812bf28f91b2e29d"

S = "${WORKDIR}/Adafruit_CircuitPython_DHT-4.0.7"

inherit setuptools3

RDEPENDS:${PN} += " \
    python3-core \
    python3-adafruit-blinka \
    python3-adafruit-circuitpython-busdevice \
    python3-adafruit-circuitpython-register \
"
