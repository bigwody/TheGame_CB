#include "scenerysprite.h"


ScenerySprite::ScenerySprite(const string& n) :
    Sprite(n),
    increment(Gamedata::getInstance().getXmlInt(n+"Increment"))
{   
}
void ScenerySprite::update() { 
    Sprite::update();
    int viewX = Viewport::getInstance().X();
    int width = frame->getWidth();
    if(X()+width < viewX)
        X(X() + increment);
    else if(X() > (viewX+640))
        X(X() - increment);
}
