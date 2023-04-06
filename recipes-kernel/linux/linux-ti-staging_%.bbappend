inherit kernel-devicetree

FILESEXTRAPATHS_prepend := "${THISDIR}/files/dts:${THISDIR}/${PN}:${THISDIR}/${PN}/ti33x:"

LINUX_VERSION_EXTENSION = "-jsd"

# Make custom kernel with PRU enabled, only list blobs, not overlays!
# no need to add defconfig as its already part of SRC_URI
SRC_URI += " \
    file://am335x-boneblack-rootbot.dts;subdir=git/arch/${ARCH}/boot/dts \
"

KERNEL_DEVICETREE = " \
   am335x-boneblack-rootbot.dtb \
"

do_set_uEnv(){
	cp -v ${THISDIR}/../../../meta-jsd/scripts/uEnv_sdcard.txt ${DEPLOY_DIR_IMAGE}/uEnv.txt
}
addtask set_uEnv after do_deploy before do_package_qa
