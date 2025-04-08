IMAGE_FSTYPES = "wic"

RPI_EXTRA_CONFIG += "dtoverlay=set-pump-pins"
RPI_EXTRA_CONFIG += "enable_uart=1"

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
    libgpiod \
    mjpg-streamer \
    kernel-modules \
    water-control \
    "

IMAGE_INSTALL:append = " tzdata"

ROOTFS_POSTPROCESS_COMMAND:append = " set_timezone_germany; "

set_timezone_germany() {
    ln -sf /usr/share/zoneinfo/Europe/Berlin ${IMAGE_ROOTFS}/etc/localtime
    echo 'Europe/Berlin' > ${IMAGE_ROOTFS}/etc/timezone
}
