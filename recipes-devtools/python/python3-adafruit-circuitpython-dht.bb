SUMMARY = "Adafruit DHT Sensor Library for CircuitPython"
HOMEPAGE = "https://github.com/adafruit/Adafruit_CircuitPython_DHT"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE;md5=<put-correct-md5-here>"

inherit pypi setuptools3

PYPI_PACKAGE = "adafruit-circuitpython-dht"

RDEPENDS:${PN} += " \
    python3-core \
    python3-adafruit-circuitpython-busdevice \
    python3-adafruit-blinka \
    python3-adafruit-circuitpython-register \
"
