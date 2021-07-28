include cgminer.inc

SUMMARY = "cgminer for the compac/2pac mining sticks"

FILES_EXTRA_PATHS_prepend = ":${THISDIR}"

RDEPENDS_${PN} += "bash"

SRC_URI = " \
	git://github.com/vthoang/cgminer.git;protocol=https;branch=master \
	file://cgminer.sh \
"

SRCREV = "495461ca3b905212f0082c2dad622f9ac7d35360"
PV = "4.9+gitr${SRCPV}_JSD"

PACKAGECONFIG_append 	= " gekko"

FILES_${PN} += " \
	${ROOT_HOME} \
"

# rename to gekko specific cgminer binary, so we can co-exist multiple versions
do_install_append() {
	install -d ${D}${ROOT_HOME}
	install ${WORKDIR}/cgminer.sh ${D}${ROOT_HOME}
	install -d ${D}${sysconfdir}/init.d/
	install ${WORKDIR}/cgminer.sh ${D}${sysconfdir}/init.d/cgminer.sh
	install -d ${D}${sysconfdir}/rc5.d/
	ln -sfr ${D}${sysconfdir}/init.d/cgminer.sh ${D}${sysconfdir}/rc5.d/S99cgminer.sh
}
