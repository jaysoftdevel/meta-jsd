inherit kernel-devicetree

FILESEXTRAPATHS:prepend := "${THISDIR}/files/dts:${THISDIR}/${PN}:${THISDIR}/${PN}/ti33x:"

LINUX_VERSION_EXTENSION = "-jsd"

SRC_URI += " \
    file://.config \
    file://am335x-boneblack-rootbot.dts;subdir=git/arch/${ARCH}/boot/dts \
"

# test if the whole file can be removed due to machine config file defintions
KERNEL_DEVICETREE = " \
   am335x-boneblack-rootbot.dtb \
"

#do_set_uEnv(){
#	cp -v ${THISDIR}/../../../../meta-jsd/scripts/uEnv_sdcard.txt ${DEPLOY_DIR_IMAGE}/uEnv.txt
#}
#addtask set_uEnv after do_deploy before do_package_qa
