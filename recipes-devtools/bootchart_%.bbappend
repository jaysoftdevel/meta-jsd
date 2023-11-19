inherit systemd

ACTIVE_SYSTEMD_SUPPORT = "1"
SYSTEMD_PACKAGES = "${PN}"
SYSTEMD_AUTO_ENABLE = "enable"
#SYSTEMD_SERVICE:${PN} = "wifi.service"
