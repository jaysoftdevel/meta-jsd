# JSD specific extenstions...
COMPATIBLE_MACHINE_prepend = "beaglebone|rootbot-bbb|"

PLATFORM_beaglebone = "beaglebone"

PACKAGES_prepend = " \
  ${PN}-ADC-onChip \
  ${PN}-RPMsg-LED0 \
"

RDEPENDS_${PN}_append = " \
  ${PN}-ADC-onChip \
  ${PN}-RPMsg-LED0 \
"

FILES_${PN} += " \
  /usr/lib \
  "

FILES_${PN}-ADC-onChip = " \
  /lib/firmware/pru/PRU_ADC_onChip* \
"

FILES_${PN}-RPMsg-LED0 = " \
  /lib/firmware/pru/PRU_RPMsg_LED0* \
"

do_install_append_beaglebone() {
    install -m 644 ${S}/examples/am335x/PRU_Halt/gen/PRU_Halt.out \
                   ${D}/lib/firmware/pru
    install -m 644 ${S}/examples/am335x/PRU_ADC_onChip/gen/PRU_ADC_onChip.out \
                   ${D}/lib/firmware/pru      
    install -m 644 ${S}/labs/lab_6/solution/PRU_RPMsg_LED0/gen/PRU_RPMsg_LED0.out \
                   ${D}/lib/firmware/pru      
    for i in 0 1
    do
        install -m 0644 ${S}/examples/am335x/PRU_RPMsg_Echo_Interrupt${i}/gen/PRU_RPMsg_Echo_Interrupt${i}.out \
                        ${D}/lib/firmware/pru
    done
    
    install -d ${D}${libdir}
    install -m 644 ${S}/lib/rpmsg_lib.lib ${D}${libdir}
}


PRU_ICSS_ALTERNATIVES_beaglebone    = "am335x-pru0-fw am335x-pru1-fw"

#ALTERNATIVE_LINK_NAME[am335x-pru0-fw] = "/lib/firmware/am335x-pru0-fw"
#ALTERNATIVE_LINK_NAME[am335x-pru1-fw] = "/lib/firmware/am335x-pru1-fw"

#ALTERNATIVE_TARGET_pru-icss-halt[am335x-pru0-fw] = "/lib/firmware/pru/PRU_Halt.out"
#ALTERNATIVE_TARGET_pru-icss-halt[am335x-pru1-fw] = "/lib/firmware/pru/PRU_Halt.out"
#ALTERNATIVE_TARGET_pru-icss-rpmsg-echo[am335x-pru1-fw] = "/lib/firmware/pru/PRU_RPMsg_Echo_Interrupt1.out"

ALTERNATIVE_TARGET_pru-icss-rpmsg-echo[am335x-pru0-fw] = "/lib/firmware/pru/PRU_ADC_onChip.out"
ALTERNATIVE_TARGET_pru-icss-rpmsg-echo[am335x-pru1-fw] = "/lib/firmware/pru/PRU_RPMsg_LED0.out"

INSANE_SKIP_${PN}-ADC-onChip = "arch"
INSANE_SKIP_${PN}-RPMsg-LED0 = "arch"
