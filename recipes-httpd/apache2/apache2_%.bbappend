SUMMARY = "myweb"
SECTION = "test"
LICENSE = "CLOSED"

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += " \
    file://index.html \
    file://httpd.conf \
    file://output.mp4 \
    "
#
#

#S = "${WORKDIR}"

#DestPath = "/usr/share/apache2/default-site/htdocs/"
DestPath = "/var/www/html"

# Only install into target, not native*
do_install:append:class-target() {
    install -d ${D}${DestPath}
    install ${WORKDIR}/index.html ${D}${DestPath}
    install ${WORKDIR}/output.mp4 ${D}${DestPath}

    # Generate self-signed SSL certificate if they don't exist
    install -d ${D}/etc/ssl/certs ${D}/etc/ssl/private
    openssl req -new -x509 -nodes -days 365 -newkey rsa:2048 \
        -keyout ${D}/etc/ssl/private/growbot.jsd.key \
        -out ${D}/etc/ssl/certs/growbot.jsd.crt \
        -subj "/C=US/ST=State/L=City/O=GrowBot/OU=IT/CN=growbot.jsd"

    install -m 0644 ${WORKDIR}/httpd.conf ${D}${sysconfdir}/apache2/httpd.conf
}

FILES:${PN} += "/*"
