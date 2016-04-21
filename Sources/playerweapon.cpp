#include "playerweapon.h"

PlayerWeapon::PlayerWeapon(const string& name) :
    sprites(),
    name(name),
    gdata(Gamedata::getInstance()),
    max_sprites(gdata.getXmlInt(name + "CountTotal")),
    index(gdata.getXmlInt(name + "CountInitial")),
    current(index)
{   
    sprites.reserve(max_sprites);
    loadSprites();
}
void PlayerWeapon::loadNext(){ 
    int maxx = gdata.getXmlInt(name + "MaxXSpeed");
    int maxy = gdata.getXmlInt(name + "MaxYSpeed");
    int x = 0;
    int y = rand() % 480 + 10;
    int xs = rand() % maxx + 10;
    int ys = rand() % maxy + 10;

    sprites[current%=max_sprites]->X(x); 
    sprites[current%=max_sprites]->Y(y); 
    sprites[current%=max_sprites]->velocityX(xs); 
    sprites[current%=max_sprites]->velocityY(ys); 
    ++current;
    if(index<max_sprites)
        index++;
}
void PlayerWeapon::loadNext(float x, float y, float xspeed, float yspeed) {
    sprites[current%max_sprites]->X(x); 
    sprites[current%max_sprites]->Y(y); 
    sprites[current%max_sprites]->velocityX(xspeed);
    sprites[current%max_sprites]->velocityY(yspeed);
    ++current;
    if(index<max_sprites)
        index++;
}
