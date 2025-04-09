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
    ntp \
    tzdata \
    "

do_set_timezone() {
    # Ensure the /etc directory exists in the root filesystem
    install -d ${IMAGE_ROOTFS}/etc

    # Set DNS servers in resolv.conf
    echo 'nameserver 8.8.8.8' > ${IMAGE_ROOTFS}/etc/resolv.conf
    touch ${IMAGE_ROOTFS}/etc/ntpd.conf

    # Set the default servers for ntpd by modifying ntpd.conf
    sed -i -z 's@restrict -6 default notrap nomodify nopeer noquery\n\nrestrict 127.0.0.1    # allow local host@restrict -6 default notrap nomodify nopeer noquery\nserver 0.pool.ntp.org\nserver 1.pool.ntp.org\nserver 2.pool.ntp.org\n\nrestrict 127.0.0.1    # allow local host@g' ${IMAGE_ROOTFS}/etc/ntpd.conf

    # Install the correct timezone and set localtime
    install -m 0644 ${IMAGE_ROOTFS}/usr/share/zoneinfo/Europe/Berlin ${IMAGE_ROOTFS}/etc/localtime
    echo 'Europe/Berlin' > ${IMAGE_ROOTFS}/etc/timezone
}

# Add the task to run after do_rootfs and before do_image_complete
addtask set_timezone after do_rootfs before do_image_complete

TIMEZONE = "Europe/Berlin"
