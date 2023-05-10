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
    kernel-module-rootbot-lcd \
    kernel-module-rootbot-stepper \
    kernel-module-hcsr04 \
    "

PROFILING = " \
	perf \
	bootchart \
"

export IMAGE_BASENAME = "${PN}"

# To be placed into local.conf!
DISTRO_FEATURES_remove = "3g"
DISTRO_FEATURES_remove = "alsa"
DISTRO_FEATURES_remove = "alsa-lib"
DISTRO_FEATURES_remove = "alsa-state"
DISTRO_FEATURES_remove = "alsa-utils"
DISTRO_FEATURES_remove = "bluetooth"
DISTRO_FEATURES_remove = "bluez"
DISTRO_FEATURES_remove = "ext2"
DISTRO_FEATURES_remove = "gobject-introspection"
DISTRO_FEATURES_remove = "gobject-introspection-data"
DISTRO_FEATURES_remove = "nfc"
#DISTRO_FEATURES_remove = "nfs"
DISTRO_FEATURES_remove = "opengl"
DISTRO_FEATURES_remove = "pulseaudio"
DISTRO_FEATURES_remove = "wayland"
DISTRO_FEATURES_remove = "x11"

MACHINE_FEATUES_remove = "alsa"
MACHINE_FEATUES_remove = "alsa-lib"
MACHINE_FEATUES_remove = "alsa-state"
MACHINE_FEATUES_remove = "alsa-utils"
MACHINE_FEATUES_remove = "apm"
MACHINE_FEATUES_remove = "gpu"
MACHINE_FEATUES_remove = "qemu-user-mode"
