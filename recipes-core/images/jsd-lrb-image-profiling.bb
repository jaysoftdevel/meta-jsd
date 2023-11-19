require jsd-lrb-image-devel.bb

DISTRO_FEATURES += " \
    largefile \
"

IMAGE_INSTALL += " \
	perf \
	systemd-bootchart \
"
#	bootchart2 \
#

export IMAGE_BASENAME = "${PN}"
