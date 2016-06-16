all: neopixel libSerial alsa clock

clean: neopixelClean libSerialClean alsaClean clockClean

alsaClean:
	$(MAKE) -C Alsa -f Makefile clean

clockClean:
	$(MAKE) -C Clock -f Makefile clean

libSerialClean:
	$(MAKE) -C LibSerial -f Makefile clean

neopixelClean:
	$(MAKE) -C Neopixel -f Makefile clean

alsa:
	$(MAKE) -C Alsa -f Makefile all

clock:
	$(MAKE) -C Clock -f Makefile all

libSerial:
	$(MAKE) -C LibSerial -f Makefile all

neopixel:
	$(MAKE) -C Neopixel -f Makefile all

