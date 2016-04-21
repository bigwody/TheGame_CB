#ifndef SPRITEMANAGER__H
#define SPRITEMANAGER__H
#include <iostream>
#include "animatedsprite.h"
#include <list>
using std::list;

class SpriteManager{
public:
    SpriteManager(const string& name);
    ~ SpriteManager(){ list<Sprite*>::iterator i;  for(i=sprites.begin(); i != sprites.end(); ++i) delete(*i); }
    void update();
    void draw() { list<Sprite*>::iterator i;  for(i=sprites.begin(); i != sprites.end(); ++i) (*i)->draw(); }
    void loadAll();
    void loadSprites();
    const list<Sprite*> getList() { return sprites; }
    void loadNext(float, float, float, float);
    void loadNext();
private:
    list<Sprite*> sprites;
    bool animated;
    string name;
    unsigned int max_sprites;
    unsigned int index;
    SpriteManager(const SpriteManager&);
    SpriteManager& operator=(const SpriteManager&);
};
#endif
