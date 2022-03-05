# ROM version
TEXT_BASE_BOOTSTART = 0xbc000000
# RAM version
#TEXT_BASE_BOOTSTART =  0x80600000

v=$(shell \
$(AS) --version|grep "GNU assembler"|awk -F . '{print $$2}')
MIPSFLAGS=$(shell \
if [ "$v" -lt "14" ]; then \
	echo "-mcpu=4kc"; \
else \
	echo "-march=4kc -mtune=4kc"; \
fi)

MIPSFLAGS += -mel
LDFLAGS_BOOTSTART += -EL

MIPSFLAGS += -mabicalls -I$(TOPDIR)/cpu/$(CPU)/ 
PLATFORM_CPPFLAGS += $(MIPSFLAGS)


