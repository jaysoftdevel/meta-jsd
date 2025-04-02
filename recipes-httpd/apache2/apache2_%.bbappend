SUMMARY = "myweb"
SECTION = "test"
LICENSE = "CLOSED"

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += " \
    file://index.html \
    file://httpd.conf \
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

    #sed -z -i 's@</VirtualHost>\n\n<VirtualHost *:443>@</VirtualHost>\n\nLoadModule rewrite_module /usr/libexec/apache2/modules/mod_rewrite.so\nLoadModule ssl_module /usr/libexec/apache2/modules/mod_ssl.so\n\n<VirtualHost *:443>@g' ${D}${sysconfdir}/apache2/httpd.conf

    # Install custom SSL-enabled VirtualHost configuration
    install -d ${D}${sysconfdir}/apache2/sites-available
    install -m 0644 ${WORKDIR}/default-ssl.conf ${D}${sysconfdir}/apache2/sites-available/default-ssl.conf

    # Ensure site is enabled
    install -d ${D}${sysconfdir}/apache2/sites-enabled
    ln -sf ../sites-available/default-ssl.conf ${D}${sysconfdir}/apache2/sites-enabled/default-ssl.conf

    #do_install:append:class-target() {
    install -m 0644 ${WORKDIR}/httpd.conf ${D}${sysconfdir}/apache2/httpd.conf

#    install -d ${D}${sysconfdir}/apache2/conf-enabled
#    ln -sf ${sysconfdir}/apache2/mods-available/rewrite.load ${D}${sysconfdir}/apache2/mods-enabled/rewrite.load
#    ln -sf ${sysconfdir}/apache2/mods-available/ssl.load ${D}${sysconfdir}/apache2/mods-enabled/ssl.load

#    # Install custom VirtualHost configuration for HTTPS redirection
#    install -d ${D}${sysconfdir}/apache2/sites-available
#    install -m 0644 ${WORKDIR}/myconfig.conf ${D}${sysconfdir}/apache2/sites-available/myconfig.conf
#    ln -sf ${sysconfdir}/apache2/sites-available/myconfig.conf ${D}${sysconfdir}/apache2/sites-enabled/000-default.conf

#    install -d ${D}/etc/apache2/sites-available/
#    cp ${S}/myconfig.conf ${D}/etc/apache2/sites-available/myconfig.conf
}

FILES:${PN} += "/var/*"
