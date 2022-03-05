#include $(KERNEL_FULL_DIR)/.config
PRODUCT_CONFIG_MAKE = ../../configs/product_config.make
ifeq ($(wildcard $(PRODUCT_CONFIG_MAKE)),$(PRODUCT_CONFIG_MAKE))
include $(PRODUCT_CONFIG_MAKE)
endif

#CC = $(CROSS)gcc
#CXX = $(CROSS)g++
#AR = $(CROSS)ar
#LD = $(CROSS)ld
#RANLIB = $(CROSS)ranlib
DIR= $(shell pwd)

EXTRA_CFLAGS += -DCONFIG_DEBUG
#EXTRA_CFLAGS += -DLITTLE_ENDIAN

obj-m:= utm_nat_nf_module.o
utm_nat_nf_module-objs += utm_nat_nf.o
EXTRA_CFLAGS +=-DHAS_UTM_NAT_NF_MODULE=1

###################
#  CFLAGS
##################

ifeq ($(CONFIG_MIPS),y)
EXTRA_CFLAGS += -I$(KERNEL_FULL_DIR)/include/asm/mach-mips/
EXTRA_CFLAGS += -I$(KERNEL_FULL_DIR)/include/asm/mach-generic/
endif
EXTRA_CFLAGS += -I$(PWD)/ -I$(KERNEL_FULL_DIR)/include/ -I../../configs/h/ -I$(PWD)/include

##############################################

all: clean build

clean:
	$(RM) *.o *.ko *mod.c *~ Module.symvers .*.o.cmd .*.ko.cmd *.order

build:
	$(MAKE) -C $(KERNEL_FULL_DIR) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS) M=$(DIR) modules

install:
	mkdir -p $(PREFIX)/lib;\
	cp utm_nat_module_nf.ko $(PREFIX)/lib
