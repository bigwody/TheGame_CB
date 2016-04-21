#include "smartsprite.h"

SmartSprite::SmartSprite(const string& n) : 
    ExplodableAnimatedSprite(n),
    spacer(Gamedata::getInstance().getXmlInt(n+"Spacer")),
    direction(1),
    xloc(Gamedata::getInstance().getXmlInt(n+"XLoc")),
    range(Gamedata::getInstance().getXmlInt(n+"Range")),
    increment(Gamedata::getInstance().getXmlInt(n+"Increment"))
{}
void SmartSprite::move() {
        xloc += increment;
        X(xloc);
}
void SmartSprite::react(int dir) {
    if(direction != dir){ 
        direction = dir;
    }
     velocityX(((dir*2)-1)*abs(velocityX()));
}
void SmartSprite::update() { 
    int viewX = Viewport::getInstance().X();
    int width = frame->getWidth();
        int dir = 0;
        if(X() < xloc+range && direction == 1)
            dir = 1;
        else if(X() < xloc && direction == 0)
            dir = 1;
        react(dir);
        if(xloc+width < viewX-300) 
            move();
            
    int ticks = Clock::getInstance().getTicks();
    advanceFrame();
    modifyFrameIndex(4);
    float incr = velocityX() * static_cast<float>(ticks) * 0.001;
    X( X()+incr );
    updateExplosion();
}
