# uncomment wifi interface done by meta-bbb/meta-jumpnow
do_setup_wifi(){
	sed -i 's/#auto/auto/g' ${D}/etc/network/interfaces
}
addtask setup_wifi after do_install before do_populate_sysroot
