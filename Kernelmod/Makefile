obj-m += testmodule.o

KDIR=/usr/src/linux-headers-5.15.0-47-generic

all:
	 $(MAKE) -C $(KDIR) M=$(shell pwd) modules

clean:
	$(MAKE) -C $(KDIR) M=$(shell pwd) clean
	rm -f *.o
