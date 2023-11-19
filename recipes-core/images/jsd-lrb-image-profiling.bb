require jsd-lrb-image-devel.bb

DISTRO_FEATURES += " \
    largefile \
"

IMAGE_INSTALL += " \
	perf \
	bootchart2 \
	systemd-bootchart \
"

export IMAGE_BASENAME = "${PN}"
