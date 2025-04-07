LICENSE = "CLOSED"

SRC_URI += " \
    file://PumpController.py \
    file://runtimeServer.py \
    "

S = "${WORKDIR}"

FILES:${PN} += "/"

do_install(){
    install -d ${D}/root
    install -m 0644 ${S}/PumpController.py ${D}/root
    install -m 0644 ${S}/runtimeServer.py ${D}/root
}
