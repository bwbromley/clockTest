CPP = g++ -c -g  -std=c++11 -I../Neopixel -I../LibSerial -I../Alsa
LINK = g++ -g

%.o : %.cpp
	$(CPP) $< -o $@

SOURCES = $(wildcard *.cpp)

OBJS = $(patsubst %.cpp, %.o, $(SOURCES))
		
all: $(OBJS)
	$(LINK) -o clock Clock.o PixelRing.o ClockPart.o SerialReader.o \
		../Neopixel/libws2811.a ../LibSerial/libSerial.a TimedSound.o \
		AudioPlayer.o ../Alsa/Player.o -lasound -pthread
	
clean:
	rm -f *.o
