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
    glibc-localedata-i18n \
    tzdata \
    "

ROOTFS_POSTPROCESS_COMMAND:append = " set_locale_de; set_timezone_munich; "

set_locale_de() {
    echo 'LANG=de_DE.UTF-8' > ${IMAGE_ROOTFS}/etc/locale.conf
    echo 'LANGUAGE=de_DE:de' >> ${IMAGE_ROOTFS}/etc/locale.conf

    # Generate the locale (glibc)
    chroot ${IMAGE_ROOTFS} localedef -i de_DE -f UTF-8 de_DE.UTF-8 || true
}

set_timezone_munich() {
    ln -sf /usr/share/zoneinfo/Europe/Munich ${IMAGE_ROOTFS}/etc/localtime
    echo 'Europe/Munich' > ${IMAGE_ROOTFS}/etc/timezone
}