CXX = g++ -c -g
LINK = g++

%.o : %.cpp
	$(CXX) $< -o $@

SOURCES = $(wildcard *.cpp)

OBJS = $(patsubst %.cpp, %.o, $(SOURCES))

all: $(OBJS)
	rm -rf libSerial.a
	ar -qcs libSerial.a PosixSignalDispatcher.o SerialPort.o SerialStream.o \
		SerialStreamBuf.o 
	$(LINK) -o readPort readPort.o -L./ -lSerial 
	
clean:
	rm -f readPort
	rm -f *.o
	rm -f *.a
