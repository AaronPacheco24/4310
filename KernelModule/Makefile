obj-m += test_mod00.o

KDIR=/usr/src/linux-headers-5.15.0-52-generic

CFLAGS = -D__KERNEL__ -DMODULE = I$(KDIR)/include -Wall

all:
	 $(MAKE) -C $(KDIR) M=$(shell pwd) $(KCONFIG) modules

clean:
	$(MAKE) -C $(KDIR) M=$(shell pwd) clean
	rm -f *.o