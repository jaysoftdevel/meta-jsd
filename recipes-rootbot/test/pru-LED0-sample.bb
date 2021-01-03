inherit update-alternatives
inherit externalsrc

EXTERNALSRC := "${THISDIR}/${PN}"
LICENSE="CLOSED"
LIC_FILES_CHKSUM=""

COMPATIBLE_MACHINE = "beaglebone|ti33x|am335x"
PACKAGE_ARCH = "${MACHINE_ARCH}"

require recipes-ti/includes/ti-paths.inc

DEPENDS += "ti-cgt-pru-native pru-icss"

export PRU_CGT = "${TI_CGT_PRU_INSTALL_DIR}"

FILES_${PN} += " \
  /lib/firmware \
"

do_compile(){
   echo "### making application ${PN} in folder ${S} with lib path: ${STAGING_LIBDIR}/rpmsg_lib.lib #"
   make -C ${S} INCLUDE="--include_path=${S}/include --include_path=${S}/include/am335x --define=FW_RSC_ADDR_ANY=(-1)" LIBS="--library=${STAGING_LIBDIR}/rpmsg_lib.lib" 
   echo "### done ..."
}

do_install_append(){
   echo "### installing files.."
   install -d ${D}/lib/firmware/my_pru
   install -m 0644 ${S}/gen/pru-LED0-sample.out ${D}/lib/firmware/my_pru
   echo "### done ..."
}

INSANE_SKIP_${PN} = "arch"
