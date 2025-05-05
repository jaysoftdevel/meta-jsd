SUMMARY = "myweb"
SECTION = "test"
LICENSE = "CLOSED"

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += " \
    file://index.html \
    file://httpd.conf \
    file://init-htpasswd.sh \
    file://htpasswd.service \
    "

# Only install into target, not native*
do_install:append:class-target() {
    install -d ${D}/var/www/html
    install -m 0644 ${WORKDIR}/index.html ${D}/var/www/html/

    # Generate self-signed SSL certificate if they don't exist
    install -d ${D}/etc/ssl/certs ${D}/etc/ssl/private
    openssl req -new -x509 -nodes -days 365 -newkey rsa:2048 \
        -keyout ${D}/etc/ssl/private/growbot.jsd.key \
        -out ${D}/etc/ssl/certs/growbot.jsd.crt \
        -subj "/C=US/ST=State/L=City/O=GrowBot/OU=IT/CN=growbot.jsd"

    install -m 0644 ${WORKDIR}/httpd.conf ${D}${sysconfdir}/apache2/
    install -m 0755 ${WORKDIR}/init-htpasswd.sh ${D}${sysconfdir}/apache2/

    # Install the systemd service
    install -d ${D}${systemd_unitdir}/system
    install -m 0644 ${WORKDIR}/htpasswd.service ${D}${systemd_unitdir}/system/
}


SYSTEMD_SERVICE:${PN} += "htpasswd.service"

FILES:${PN} += "/"
