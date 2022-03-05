# RAM version
#TEXT_BASE =  0x80f80000
#TEXT_BASE =  0x81f80000
TEXT_BASE =  0x81C00000
#TEXT_BASE =  0x83F00000

v=$(shell \
$(AS) --version|grep "GNU assembler"|awk -F . '{print $$2}')
MIPSFLAGS=$(shell \
if [ "$v" -lt "14" ]; then \
	echo "-mcpu=4kc"; \
else \
	echo "-march=4kc -mtune=4kc"; \
fi)

MIPSFLAGS += -mel
LDFLAGS += -EL

MIPSFLAGS += -mabicalls
PLATFORM_CPPFLAGS += $(MIPSFLAGS)
