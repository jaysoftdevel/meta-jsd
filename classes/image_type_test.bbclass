
# Define additional CMake env var to disable HW access for QEMU images
do_configure() {
	if [ ! -z `echo ${MACHINE}|grep "qemu"` ]
	then
		echo "## ${EXTRA_OECMAKE} #"
		cmake -DCMAKE_PREFIX_PATH=${STAGING_DIR_HOST}/usr ${EXTRA_OECMAKE} -DBUILD_FOR_QEMU:STRING=\"${MACHINE}\" ${CONFIGUREOPTS} ${S}
		echo "## ${EXTRA_OECMAKE} #"
	fi
}
