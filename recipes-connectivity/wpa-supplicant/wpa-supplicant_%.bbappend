FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI += " \
	file://wifi.sh \
"
do_install_append () {
	install -d ${D}${sysconfdir}/init.d
	install -m 0755    ${WORKDIR}/wifi.sh     ${D}${sysconfdir}/init.d/
}

MASKED_SCRIPTS = " \
	wifi \
"

#FILES_${PN} += " \
#	/etc/init.d/wifi.sh \
#"
