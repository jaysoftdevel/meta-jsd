do_configure:prepend() {
    sed -z -i 's/##\n#dtoverlay=act-led,activelow=off/##\ndtoverlay=uart1-pi5\ndtoverlay=disable-wifi-pi5\ndtoverlay=disable-bt-pi5\ndtoverlay=gpio-init\n#dtoverlay=act-led,activelow=off/g' ${S}/config.txt
    sed -i 's/#dtparam=i2c_arm=off/dtparam=i2c_arm=on\ndtoverlay=i2c1/g' ${S}/config.txt
}
