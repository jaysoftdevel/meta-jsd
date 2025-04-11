do_configure:prepend() {
    echo "dtoverlay=uart1-pi5" >> ${S}/config.txt
}
