CC= g++
CXXFLAGS= -c -std=c++11 -Wall -I/usr/include/SDL/ -I../include -D_LINUX

all: objects archive clean

objects:
	$(CC) *.cpp $(CXXFLAGS)
archive:
	$(AR) rcs libsmelt.a *.o
clean:
	if ( test gfx_sdl.o ); then rm *.o; fi
clean-all: clean
	rm *.a