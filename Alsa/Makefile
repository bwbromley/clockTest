CPP = g++ -c -g
LINK = g++ -g

%.o : %.cpp
	$(CPP) $< -o $@

SOURCES = $(wildcard *.cpp)

OBJS = $(patsubst %.cpp, %.o, $(SOURCES))
		
all: $(OBJS)
	#$(LINK) -o play Player.o -lasound
	
clean:
	rm -f *.o
	rm -f play
		