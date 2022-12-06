LICENSE = "MIT"

DISTRO_FEATURES += " \
    largefile \
"

IMAGE_INSTALL += " \
    ${CORE_OS} \
    ${KERNEL_EXTRA_INSTALL} \
    ${DEV_SDK_INSTALL} \
    ${DEV_EXTRAS} \
    ${PROFILING} \
"
#    ${EXTRA_TOOLS_INSTALL} \
#

KERNEL_EXTRA_INSTALL = " \
    kernel-modules \
    rootbot-lcd-kmod \
    rootbot-stepper-kmod \
    hcsr04-gpio-kmod \
    "

PROFILING = " \
	perf \
	bootchart \
"

export IMAGE_BASENAME = "${PN}"

DISTRO_FEATURES_remove = "bluetooth"
DISTRO_FEATURES_remove = "3g"
DISTRO_FEATURES_remove = "opengl"
DISTRO_FEATURES_remove = "wayland"
DISTRO_FEATURES_remove = "x11"
DISTRO_FEATURES_remove = "nfc"
#DISTRO_FEATURES_remove = "nfs"
DISTRO_FEATURES_remove = "ext2"
