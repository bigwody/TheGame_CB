
ifeq ("$(shell whoami)", "malloy")
  CXX = clang++
else
  CXX = g++
endif
CXX_LINK = g++

# Warnings frequently signal eventual errors:
CXXFLAGS=`sdl-config --cflags` -g -W -Wall -Weffc++ -Wextra -pedantic -O0

ifeq ("$(shell uname)", "Darwin")
  LDFLAGS =
else
  ifeq ("$(shell uname)", "Linux")
  LDFLAGS = `sdl-config --libs` -lSDL_ttf -lSDL_image -lSDL_mixer -lexpat
  endif
endif

OBJS = \
	main.o \
	manager.o \
	gamedata.o \
	parseXML.o \
	clock.o \
	vector2f.o \
	viewport.o \
	frame.o \
	ioManager.o \
	sprite.o \
    explosion.o \
	explodingsprite.o \
	animatedsprite.o \
	explodableanimatedsprite.o \
	smartsprite.o \
	scenerysprite.o \
	playersprite.o \
	spritemanager.o \
	playerweapon.o \
	enemysprite.o \
	bosssprite.o \
	spritefactory.o \
	animationfactory.o \
	explosionfactory.o \
	collisionstrategy.o \
	aaline.o \
	sound.o \

EXEC = run

# $< refers to the first dependency
%.o: %.cpp
	$(CXX_LINK) $(CXXFLAGS) -c $< -o $@

# $@ refers to the target
$(EXEC): $(OBJS)
	g++ $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

main.o: main.cpp
manager.o: manager.cpp manager.h clock.h world.h hud.h menu.h playersprite.h scenerysprite.h enemysprite.h bosssprite.h collisionstrategy.h
parseXML.o: parseXML.cpp parseXML.h
gamedata.o: gamedata.cpp gamedata.h parseXML.h
clock.o: clock.cpp clock.h
vector2f.o: vector2f.cpp vector2f.h
viewport.o: viewport.cpp viewport.h sprite.h
frame.o: frame.cpp frame.h ioManager.h
ioManager.o: ioManager.cpp ioManager.h
sprite.o: sprite.cpp sprite.h drawable.h frame.h ioManager.h gamedata.h
explosion.o: explosion.cpp explosion.h sprite.h gamedata.h
explodingsprite.o: explodingsprite.cpp explodingsprite.h sprite.h \
	ioManager.h explosion.h
animatedsprite.o: animatedsprite.cpp animatedsprite.h sprite.h 
explodableanimatedsprite.o: explodableanimatedsprite.cpp explodableanimatedsprite.h
smartsprite.o: smartsprite.cpp smartsprite.h animatedsprite.h 
scenerysprite.o: scenerysprite.cpp scenerysprite.h viewport.h sprite.h
playersprite.o: playersprite.cpp playersprite.h animationfactory.h viewport.h sprite.h
spritemanager.o: spritemanager.cpp spritemanager.h animatedsprite.h
playerweapon.o: playerweapon.cpp playerweapon.h
enemysprite.o: enemysprite.cpp enemysprite.h smartsprite.h
bosssprite.o: bosssprite.cpp bosssprite.h smartsprite.h spritemanager.h
spritefactory.o: spritefactory.cpp spritefactory.h abstractfactory.h
animationfactory.o: animationfactory.cpp animationfactory.h abstractfactory.h
explosionfactory.o: explosionfactory.cpp explosionfactory.h abstractfactory.h frame.h
collisionstrategy.o: collisionstrategy.cpp collisionstrategy.h sprite.h
aaline.o: aaline.cpp aaline.h
sound.o: sound.cpp sound.h 

clean:
	rm -rf $(OBJS)
	rm -rf $(EXEC)
new:
	make clean
	make 
	
