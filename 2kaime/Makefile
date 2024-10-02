CFILES = myDeviceDriver.c
KERNEL_HEADERS=/lib/modules/$(shell uname -r)/build

obj-m := MyDeviceModule.o
MyDeviceModule-objs := $(CFILES:.c=.o)

ccflags-y += -std=gnu99 -Wall -Wno-declaration-after-statement

all:
	make -C $(KERNEL_HEADERS) M=$(shell pwd) modules
clean:
	make -C $(KERNEL_HEADERS) M=$(shell pwd) clean