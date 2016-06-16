all: threadTest neopixel linuxUtilities libSerial alsa clock

clean: threadTestClean neopixelClean linuxUtilitiesClean \
	libSerialClean alsaClean clockClean

alsaClean:
	$(MAKE) -C Alsa -f Makefile clean

clockClean:
	$(MAKE) -C Clock -f Makefile clean

libSerialClean:
	$(MAKE) -C LibSerial -f Makefile clean

linuxUtilitiesClean:
	$(MAKE) -C LinuxUtilities -f Makefile clean

neopixelClean:
	$(MAKE) -C Neopixel -f Makefile clean

threadTestClean:
	$(MAKE) -C ThreadTest -f Makefile clean

alsa:
	$(MAKE) -C Alsa -f Makefile all

clock:
	$(MAKE) -C Clock -f Makefile all

libSerial:
	$(MAKE) -C LibSerial -f Makefile all

linuxUtilities:
	$(MAKE) -C LinuxUtilities -f Makefile all

neopixel:
	$(MAKE) -C Neopixel -f Makefile all

threadTest:
	$(MAKE) -C ThreadTest -f Makefile all
