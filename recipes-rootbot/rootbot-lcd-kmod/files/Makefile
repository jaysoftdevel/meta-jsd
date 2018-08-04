obj-m += st7565.o
SRC := $(shell pwd)

all:
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC)
#	make -C /usr/src/linux-${shell uname -r}/ SUBDIRS=${shell pwd} modules
#	make -C /usr/src/linux-headers-${shell uname -r}/ SUBDIRS=${shell pwd} modules

modules_install:
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC) modules_install

clean:
	rm -f *.o *~ core .depend .*.cmd *.ko *.mod.c
	rm -f Module.markers Module.symvers modules.order
	rm -rf .tmp_versions Modules.symvers
#	make -C /usr/src/linux-${shell uname -r}/ SUBDIRS=${shell pwd} clean
#	make -C /usr/src/linux-headers-${shell uname -r}/ SUBDIRS=${shell pwd} clean



