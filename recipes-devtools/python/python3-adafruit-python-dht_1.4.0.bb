#do_compile() {
#        cd ${SETUPTOOLS_SETUP_PATH}
#        NO_FETCH_BUILD=1 \
#        STAGING_INCDIR=${STAGING_INCDIR} \
#        STAGING_LIBDIR=${STAGING_LIBDIR} \
#        ${STAGING_BINDIR_NATIVE}/python3-native/python3 setup.py \
#        bdist_wheel --force-pi --verbose --dist-dir ${PEP517_WHEEL_PATH} ${SETUPTOOLS_BUILD_ARGS} || \
#        bbfatal_log "'python3 setup.py bdist_wheel ${SETUPTOOLS_BUILD_ARGS}' execution failed."
#}


SUMMARY = "Adafruit DHT Sensor Library"
HOMEPAGE = "https://github.com/adafruit/Adafruit_CircuitPython_DHT"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE;md5=1a1448fedfbea080fbee2538674706d5"

SRC_URI = " \
    git://github.com/adafruit/Adafruit_CircuitPython_DHT.git;branch=main \
    "
SRCREV = "${AUTOREV}"

S = "${WORKDIR}/git"

inherit python3-dir

do_install() {
    install -d ${D}${PYTHON_SITEPACKAGES_DIR}/adafruit_dht
    install -m 0644 ${S}/adafruit_dht.py ${D}${PYTHON_SITEPACKAGES_DIR}/adafruit_dht/
}

RDEPENDS:${PN} += " \
    python3-core \
    python3-adafruit-circuitpython-busdevice \
    python3-adafruit-blinka \
    python3-adafruit-circuitpython-register \
"

FILES:${PN} += "/"

DEPENDS += "python3-adafruit-circuitpython-busdevice python3-adafruit-blinka python3-adafruit-circuitpython-register"
