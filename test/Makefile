KERNEL_HEADERS=/lib/modules/$(shell uname -r)/build
obj-m := test.o

all:
	make -C $(KERNEL_HEADERS) M=$(shell pwd) modules
clean:
	make -C $(KERNEL_HEADERS) M=$(shell pwd) clean