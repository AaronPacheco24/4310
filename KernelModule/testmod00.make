obj-m += test_mod00.o

KDIR=/usr/src/linux-headers-5.11.0-38-generic

CFLAGS = -D__KERNEL__ -DMODULE = I$(KDIR)/include -Wall

all:
    $(make) -C $(KDIR) M=$(shell pwd) $(KCONFIG) modules

clean:
    $(make) -C $(KDIR) M=$(shell pwd) clean
    rm -f *.o