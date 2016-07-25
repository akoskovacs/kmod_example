MOD_DIR  := $(shell pwd)
MOD_NAME := hello.ko
SUDO     := sudo
obj-m += hello.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=${MOD_DIR} modules

insert: all remove
	${SUDO} insmod ${MOD_NAME}

remove: all
	${SUDO} rmmod ${MOD_NAME}

clean:
	make -C /lib/modules/$(shell uname -r)/build M=${MOD_DIR} clean

