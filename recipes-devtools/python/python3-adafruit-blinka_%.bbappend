SRCREV = "706e5f8abca75dc3939a4e3464e3f655de04af58"
LIC_FILES_CHKSUM = "file://LICENSE;md5=fccd531dce4b989c05173925f0bbb76c"

do_install:append() {
    # Remove precompiled binaries for other platforms
    find ${D}${PYTHON_SITEPACKAGES_DIR} -type f \( -name "libgpiod_pulsein" -o -name "libgpiod_pulsein64" \) -exec rm -f {} \;
}

RDEPENDS:${PN} += "glibc "
