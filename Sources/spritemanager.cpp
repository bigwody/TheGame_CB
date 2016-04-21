#include "spritemanager.h"

SpriteManager::SpriteManager(const string& name) :
    sprites(),
    animated(Gamedata::getInstance().getXmlBool(name + "Animated")),
    name(name),
    max_sprites(Gamedata::getInstance().getXmlInt(name + "CountTotal")),
    index(Gamedata::getInstance().getXmlInt(name + "CountInitial"))
{   
    loadSprites();
}
void SpriteManager::loadSprites(){
    int frames = Gamedata::getInstance().getXmlInt(name + "FrameCount");
    if(frames > 1) {
        for(unsigned int i=0; i <index; ++i) {
            sprites.push_back(new AnimatedSprite(name));
            
        }
    }
    else {
        for(unsigned int i=0; i <index; ++i)
            sprites.push_back(new Sprite(name));
    }
}
void SpriteManager::update(){ 
    list<Sprite*>::iterator i;  
    for(i=sprites.begin(); i != sprites.end(); ++i){
            (*i)->update(); 
    }
}
void SpriteManager::loadAll(){ 
    if(animated){ 
        while(sprites.size() < max_sprites)
        sprites.push_back(new AnimatedSprite(name));
    }
    else{
        while(sprites.size() < max_sprites)
        sprites.push_back(new Sprite(name));
    }
}
void SpriteManager::loadNext(){ 
    if(sprites.size() < max_sprites) {
        if(animated) 
            sprites.push_back(new AnimatedSprite(name));
        else
            sprites.push_back(new Sprite(name));
    }
}
void SpriteManager::loadNext(float x, float y, float xspeed, float yspeed) {
    if(sprites.size() >= max_sprites) {
        sprites.remove(*sprites.end());
        sprites.pop_back();
    }
    if(animated) 
            sprites.push_front(new AnimatedSprite(name));
        else
            sprites.push_front(new Sprite(name));
    (*sprites.begin())->X(x); 
    (*sprites.begin())->Y(y); 
    (*sprites.begin())->velocityX(xspeed);
    (*sprites.begin())->velocityY(yspeed);
}
