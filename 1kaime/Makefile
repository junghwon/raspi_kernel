CFILES = myDeviceDriver.c
KERNEL_HEADERS=/lib/modules/$(shell uname -r)/build

obj-m := MyDeviceModule.o
MyDeviceModule-objs := $(CFILES:.c=.o)

all:
	make -C $(KERNEL_HEADERS) M=$(shell pwd) modules
clean:
	make -C $(KERNEL_HEADERS) M=$(shell pwd) clean