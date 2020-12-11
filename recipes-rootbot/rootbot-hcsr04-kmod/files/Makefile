obj-m := hcsr04-kmod.o
hcsr04-kmod-objs := hcsr04.o libprussdrv.a

SRC := $(shell pwd)
PRU_ASM=pasm
# import from rootbot-hcsr04 recipe
IPASM_PATH=$(PASM_PATH)

all:
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC)

modules_install: hcsr04_FL.bin hcsr04_FC.bin hcsr04_FR.bin hcsr04_RL.bin hcsr04_RR.bin
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC) modules_install

hcsr04_FL.bin: hcsr04_FL.p
	@echo ">> Generating PRU binary FL"
	$(IPASM_PATH)$(PRU_ASM) -b hcsr04_FL.p

hcsr04_FC.bin: hcsr04_FC.p
	@echo ">> Generating PRU binary FC"
	$(IPASM_PATH)$(PRU_ASM) -b hcsr04_FC.p
	
hcsr04_FR.bin: hcsr04_FR.p
	@echo ">> Generating PRU binary FR"
	$(IPASM_PATH)$(PRU_ASM) -b hcsr04_FR.p
	
hcsr04_RL.bin: hcsr04_RL.p
	@echo ">> Generating PRU binary RL"
	$(IPASM_PATH)$(PRU_ASM) -b hcsr04_RL.p
	
hcsr04_RR.bin: hcsr04_RR.p
	@echo ">> Generating PRU binary RR"
	$(IPASM_PATH)$(PRU_ASM) -b hcsr04_RR.p
	
#hcsr04: hcsr04.c
#	@echo ">> Compiling HC-SR04 binary"
#	$(MAKE) $(CFLAGS) -C -o hcsr04.o hcsr04.c
#	$(MAKE) -lpthread -o hcsr04 hcsr04.o -lprussdrv -L.

clean:
	rm -rf hcsr04 hcsr04.o hcsr04_FL.bin hcsr04_FC.bin hcsr04_FR.bin hcsr04_RL.bin hcsr04_RR.bin
