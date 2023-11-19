FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

inherit systemd

# ACTIVE_SYSTEMD_SUPPORT = "1"
SYSTEMD_PACKAGES = "${PN}"
# SYSTEMD_AUTO_ENABLE = "enable"
SYSTEMD_SERVICE_${PN} = "wifi.service"

SRC_URI += " \
	file://wifi.sh \
	file://wifi.service \
"
do_install_append () {
	echo "## appending..."
	install -d ${D}${libexecdir}
	install -m 0755 ${WORKDIR}/wifi.sh ${D}${libexecdir}/

	install -d ${D}${systemd_unitdir}/system/
	install -m 0644 ${WORKDIR}/wifi.service ${D}${systemd_unitdir}/system
}

FILES_${PN} += " \
	${ROOT_HOME}/wifi.sh \
"
