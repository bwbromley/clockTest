#from https://github.com/richardghirst/rpi_ws281x
# neopixel control from raspberry pi 2

CXX = gcc -c -g -Wall
LINK = gcc -g

%.o : %.c
	$(CXX) $< -o $@

SOURCES = $(wildcard *.c)

OBJS = $(patsubst %.c, %.o, $(SOURCES))

makeLibrary:
	rm -rf libws2811.a
	ar -qcs libws2811.a ws2811.o pwm.o dma.o board_info.o mailbox.o
	ranlib libws2811.a
	
makeTest:
	gcc -o test main.o libws2811.a
	
makeClock:
	gcc -o clock Clock.o libws2811.a
	
all: $(OBJS) makeLibrary makeTest makeClock

clean:
	rm -f *.a
	rm -f *.o
	rm -f test
	rm -f clock