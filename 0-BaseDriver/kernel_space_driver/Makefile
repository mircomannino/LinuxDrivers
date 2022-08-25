
LINUX_SOURCES=/usr/src/linux-headers-$(shell uname -r)
obj-m := base_driver.o

all:
	make -C $(LINUX_SOURCES) M=$(shell pwd) modules
clean:
	make -C $(LINUX_SOURCES) M=$(shell pwd) clean