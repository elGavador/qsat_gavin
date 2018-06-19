#@configure_input@

package = @PACKAGE_NAME@
version = @PACKAGE_VERSION@
tarname = @PACKAGE_TARNAME@
distdir = $(tarname)-$(version)

prefix		= @prefix@
exec_prefix	= @exec_prefix@
libdir		= @libdir@

CXX            = g++

INCPATH		  = -Iinclude/ -Iinclude/spectrometer/AvaSpec -Iinclude/spectrometer -I/usr/local/include/libusb-1.0 -Ithread/  -I/usr/local/include/libavs -L/usr/local/lib


CFLAGS        = -Wall
TESTSRC       = src/main.cc src/payload1/Spectrometer.cc src/payload1/avaspec-config.cc src/log.cc
TESTAPP       = bin/main 
TESTOBJ       = main.o 

all:
	$(CXX) $(CFLAGS) $(INCPATH) -L. $(TESTSRC) -o $(TESTAPP) -lpthread -lavs

clean:
	-rm $(TESTOBJ)


.PHONY: all clean
