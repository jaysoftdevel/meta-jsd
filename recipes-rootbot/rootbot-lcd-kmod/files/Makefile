obj-m += st7565.o
SRC := $(shell pwd)

#all: 
#	make -C /usr/src/linux-${shell uname -r}/ SUBDIRS=${shell pwd} modules
#	make -C /usr/src/linux-headers-${shell uname -r}/ SUBDIRS=${shell pwd} modules
clean:
#	make -C /usr/src/linux-${shell uname -r}/ SUBDIRS=${shell pwd} clean
#	make -C /usr/src/linux-headers-${shell uname -r}/ SUBDIRS=${shell pwd} clean
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC) clean

all:
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC) modules

modules_install:
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC) modules_install
