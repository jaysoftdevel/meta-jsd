# JSD specific extenstions...
COMPATIBLE_MACHINE_prepend = "beaglebone|rootbot-bbb|"

PLATFORM_beaglebone = "beaglebone"

do_install_append_beaglebone() {
    install -m 644 ${S}/examples/am335x/PRU_Halt/gen/PRU_Halt.out \
                   ${D}/lib/firmware/pru
    for i in 0 1
    do
        install -m 0644 ${S}/examples/am335x/PRU_RPMsg_Echo_Interrupt${i}/gen/PRU_RPMsg_Echo_Interrupt${i}.out \
                        ${D}/lib/firmware/pru
    done
}

FILES_${PN} += " \
    /lib/firmware/pru \
"

PRU_ICSS_ALTERNATIVES_beaglebone    = "beaglebone-pru0-fw beaglebone-pru1-fw"

ALTERNATIVE_LINK_NAME[beaglebone-pru0-fw] = "/lib/firmware/beaglebone-pru0-fw"
ALTERNATIVE_LINK_NAME[beaglebone-pru1-fw] = "/lib/firmware/beaglebone-pru1-fw"

ALTERNATIVE_TARGET_pru-icss-halt[beaglebone-pru0-fw] = "/lib/firmware/pru/PRU_Halt.out"
ALTERNATIVE_TARGET_pru-icss-halt[beaglebone-pru1-fw] = "/lib/firmware/pru/PRU_Halt.out"

ALTERNATIVE_TARGET_pru-icss-rpmsg-echo[beaglebone-pru0-fw] = "/lib/firmware/pru/PRU_RPMsg_Echo_Interrupt0.out"
ALTERNATIVE_TARGET_pru-icss-rpmsg-echo[beaglebone-pru1-fw] = "/lib/firmware/pru/PRU_RPMsg_Echo_Interrupt1.out"
