obj-m += lkm_example.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
test:
	ss -ltn
	sudo dmesg -C
	sudo insmod lkm_example.ko
	ss -ltn
	sudo rmmod lkm_example.ko
	dmesg

start: 
	sudo dmesg -C
	sudo insmod lkm_example.ko
	dmesg
