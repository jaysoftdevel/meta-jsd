SUMMARY = "Adafruit DHT Sensor Library for CircuitPython"
DESCRIPTION = "Library for DHT11, DHT22, and AM2302 temperature and humidity sensors."
HOMEPAGE = "https://github.com/adafruit/Adafruit_CircuitPython_DHT"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE;md5=1a1448fedfbea080fbee2538674706d5"

SRC_URI = "https://github.com/adafruit/Adafruit_CircuitPython_DHT/archive/refs/tags/4.0.7.tar.gz;downloadfilename=Adafruit_CircuitPython_DHT-4.0.7.tar.gz"
PYPI_SRC_URI = "https://github.com/adafruit/Adafruit_CircuitPython_DHT/archive/refs/tags/4.0.7.tar.gz;downloadfilename=Adafruit_CircuitPython_DHT-4.0.7.tar.gz"
SRC_URI[sha256sum] = "e4aace0cc3a778101c8208c5e79c35c01fa173a787c0bb6c90f5daade8688b96"

S = "${WORKDIR}/Adafruit_CircuitPython_DHT-4.0.7"

inherit python3-dir

do_install() {
    install -d ${D}${PYTHON_SITEPACKAGES_DIR}/adafruit_dht
    cp -r ${S}/adafruit_dht*.py ${D}${PYTHON_SITEPACKAGES_DIR}/
}

FILES:${PN} += " / "

RDEPENDS:${PN} += " \
    python3-core \
    python3-adafruit-blinka \
    python3-adafruit-circuitpython-busdevice \
    python3-adafruit-circuitpython-register \
    python3-adafruit-platformdetect \
"
