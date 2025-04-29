SUMMARY = "Overlay to init GPIO as LOW at boot"
LICENSE = "MIT"
FILESEXTRAPATHS:prepend = "${THISDIR}/files:"

SRC_URI = "file://rpi5-gpio-init.dts"

inherit kernel-devicetree

DT_OVERLAY = "gpio-init"
