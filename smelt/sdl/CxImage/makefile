CC= g++
CXXFLAGS= -c -Os -D_LINUX
AR= ar

all: objects archive clean

objects:
	$(CC) *.cpp $(CXXFLAGS)
archive:
	$(AR) rcs libCxImage.a *.o
clean:
	rm *.o && mv libCxImage.a ../
