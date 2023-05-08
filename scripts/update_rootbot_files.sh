#!/bin/bash
WORKDIR="${PWD}/../../build/tmp/work/cortexa8t2hf-neon-poky-linux-gnueabi"
KWORKDIR="${PWD}/../../build/tmp/work/rootbot_bbb-poky-linux-gnueabi"
IPADDR="192.168.10.39"
scp ${WORKDIR}/tester/1.0-r0/build/tester root@${IPADDR}:/home/root
scp ${KWORKDIR}/kernel-module-rootbot-hcsr04/1.0-r0/hcsr04.ko root@${IPADDR}:/lib/modules/5.10.120-g2176e1735b/extra/
scp ${KWORKDIR}/kernel-module-rootbot-lcd/1.0-r0/st7565.ko root@${IPADDR}:/lib/modules/5.10.120-g2176e1735b/extra/
scp ${KWORKDIR}/kernel-module-rootbot-stepper/1.0-r0/stepperL.ko root@${IPADDR}:/lib/modules/5.10.120-g2176e1735b/extra/
scp ${KWORKDIR}/kernel-module-rootbot-stepper/1.0-r0/stepperR.ko root@${IPADDR}:/lib/modules/5.10.120-g2176e1735b/extra/
ssh root@${IPADDR} "rmmod hcsr04 st7565 stepperL stepperR; modprobe hcsr04; modprobe st7565; modprobe stepperL; modprobe stepperR"

