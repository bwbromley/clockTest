CPP = g++ -c -g  -std=c++11 
LINK = g++ -g 

%.o : %.cpp
	$(CPP) $< -o $@

SOURCES = $(wildcard *.cpp)

OBJS = $(patsubst %.cpp, %.o, $(SOURCES))
		
all: $(OBJS)
	$(LINK) -o test *.o -pthread
	
clean:
	rm -f *.o
