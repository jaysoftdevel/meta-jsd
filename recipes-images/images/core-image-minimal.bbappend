IMAGE_FSTYPES = "wic"

IMAGE_INSTALL += " \
    apache2 \
    dropbear \
    vim \
    gstreamer1.0 \
    gstreamer1.0-plugins-base \
    gstreamer1.0-plugins-good \
    gstreamer1.0-plugins-bad \
    gstreamer1.0-plugins-ugly \
    gstreamer1.0-libav \
    gst-player \
    ffmpeg \
    v4l-utils \
    gstreamer1.0-vaapi \
    python3 \
    python3-flask \
    python3-pyserial \
    python3-gpiod \
    python3-ntplib \
    python3-pip \
    libgpiod \
    mjpg-streamer \
    kernel-modules \
    water-control \
    tzdata \
    ntp \
    moister \
    usbutils \
    pciutils \
"

# Adafruit libs, not fully working yet!
#python3-adafruit-blinka \
#python3-adafruit-circuitpython-dht \
#python3-adafruit-platformdetect \
#

# WIFI!!
#wpa-supplicant \
#connman \
#dhcpcd \
#linux-firmware-rtl8822 \
#

ROOTFS_POSTPROCESS_COMMAND += " set_timezone ; "

set_timezone() {
    # Ensure the /etc directory exists in the root filesystem
    install -d ${IMAGE_ROOTFS}/etc

    # Install the correct timezone and set localtime
    install -m 0644 ${IMAGE_ROOTFS}/usr/share/zoneinfo/Europe/Berlin ${IMAGE_ROOTFS}/etc/localtime
    echo 'Europe/Berlin' > ${IMAGE_ROOTFS}/etc/timezone
}

