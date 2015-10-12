CC= g++
CXXFLAGS= -std=c++11 -Wall -g -I/home/chrisoft/devel/BulletLabRemixIII/include -I/usr/include/freetype2
LINK= -L../smelt/sdl -L../extensions -lsmeltext -lsmelt -lCxImage -lSDL2 -lvorbis -lvorbisfile -lopenal -ljpeg -lpng -lfreetype -lm -lz -ldl -pthread

all: main

main: main.o scenemgr.o intro.o menuclass.o resources.o mainmenu.o bullet.o gamescene.o player.o vmrunner.o
	$(CC) main.o scenemgr.o intro.o menuclass.o mainmenu.o resources.o bullet.o gamescene.o player.o vmrunner.o $(LINK) -o BLR3

main.o: main.cpp
	$(CC) $(CXXFLAGS) -c main.cpp

scenemgr.o: master/scenemgr.cpp
	$(CC) $(CXXFLAGS) -c master/scenemgr.cpp

resources.o: master/resources.cpp
	$(CC) $(CXXFLAGS) -c master/resources.cpp

intro.o: master/intro.cpp
	$(CC) $(CXXFLAGS) -c master/intro.cpp

menuclass.o: ui/menuframework/menuclass.cpp
	$(CC) $(CXXFLAGS) -c ui/menuframework/menuclass.cpp

mainmenu.o: ui/mainmenu.cpp
	$(CC) $(CXXFLAGS) -c ui/mainmenu.cpp

bullet.o: core/bullet.cpp
	$(CC) $(CXXFLAGS) -c core/bullet.cpp

gamescene.o: core/gamescene.cpp
	$(CC) $(CXXFLAGS) -c core/gamescene.cpp

player.o: core/player.cpp
	$(CC) $(CXXFLAGS) -c core/player.cpp

vmrunner.o: core/vmrunner.cpp
	$(CC) $(CXXFLAGS) -c core/vmrunner.cpp

clean:
	rm *.o BLR3