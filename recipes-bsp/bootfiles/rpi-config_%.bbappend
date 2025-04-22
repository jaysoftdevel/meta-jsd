do_configure:prepend() {
    echo "dtoverlay=uart1-pi5" >> ${S}/config.txt
    echo "dtoverlay=disable-wifi-pi5" >> ${S}/config.txt
    echo "dtoverlay=disable-bt-pi5" >> ${S}/config.txt
}
