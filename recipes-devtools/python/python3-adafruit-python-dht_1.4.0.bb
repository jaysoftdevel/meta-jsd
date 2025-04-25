SUMMARY = "Python library for DHT11/DHT22 temperature/humidity sensors"
HOMEPAGE = "https://github.com/adafruit/Adafruit_Python_DHT"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE;md5=bda1c9cc018bbe5da02d845724b71d55"

SRC_URI = " \
    git://github.com/adafruit/Adafruit_Python_DHT.git;branch=master \
    "

SRCREV = "${AUTOREV}"
S = "${WORKDIR}/git"

do_compile() {
        cd ${SETUPTOOLS_SETUP_PATH}
        NO_FETCH_BUILD=1 \
        STAGING_INCDIR=${STAGING_INCDIR} \
        STAGING_LIBDIR=${STAGING_LIBDIR} \
        ${STAGING_BINDIR_NATIVE}/python3-native/python3 setup.py \
        bdist_wheel --force-pi --verbose --dist-dir ${PEP517_WHEEL_PATH} ${SETUPTOOLS_BUILD_ARGS} || \
        bbfatal_log "'python3 setup.py bdist_wheel ${SETUPTOOLS_BUILD_ARGS}' execution failed."
}

inherit setuptools3

RDEPENDS:${PN} += "python3"

# Ensure it uses Python 3
PYTHON_TARGET_VERSION = "3"
