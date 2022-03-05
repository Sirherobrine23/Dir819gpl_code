EXTRA_CFLAGS=  -I../lib -I${BUILDDIR}/apps/include -I../../../ssap/msg \
              -I../../../ssap/lib -I${BUILDDIR}/include/ -I$(TMPDISTDIR)/include -I${BUILDDIR}/ -Wall -Os

EXTRA_LDFLAGS=-lutil -lssap -L$(BUILDDIR)/apps/ssap/lib -L$(TMPDISTDIR)/lib -lscew -lexpat -lz

#scb+ 2012-12-5
ifeq ("$(CONFIG_APPS_LOGIC_NEW3G)","y")
EXTRA_LDFLAGS +=  -l3g-util -L${BUILDDIR}/apps/logic/new3g/3g-mngr/lib
endif

ifeq (${PRODUCT}, UML)
	EXTRA_CFLAGS += -DLOGGER_UML
endif

E_TARGET = hotplug 
E_SHELL  = kill_proc.sh

obj-y = hotplug.o hotplug_storage.o
obj-y += hotplug_usb_lp.o
obj-y += hotplug_usb_modem.o

include $(ROOTDIR)/Rules.make

installme::
	$(Q)cp $(E_TARGET) $(FSROOT)/sbin/
	$(Q)$(STRIP) $(FSROOT)/sbin/$(E_TARGET)
	$(Q)cp $(E_SHELL) $(FSROOT)/sbin/

