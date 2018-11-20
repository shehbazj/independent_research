# Makefile for dm-trace

obj-m +=dm-trace.o
all: dmtrace

dmtrace:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules_install
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) install

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean
