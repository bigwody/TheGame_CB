#include "animatedsprite.h"

AnimatedSprite::AnimatedSprite(const string& n) : 
    Sprite(n, AnimationFactory::getInstance()),
    totalTicks(0),
    currentFrame(0),
    numberOfFrames(Gamedata::getInstance().getXmlInt(n+"FrameCount") ),
    frameInterval(Gamedata::getInstance().getXmlInt(n+"FrameInterval"))
{ 
    if(getAction() == 5) 
        currentFrame = rand() % numberOfFrames;
}
void AnimatedSprite::advanceFrame() {
    totalTicks += Clock::getInstance().getTicks();;
    if (totalTicks > frameInterval) {
        ++currentFrame;
        currentFrame%=numberOfFrames;
        totalTicks = 0;
    }
}
void AnimatedSprite::update() { 
    if(abs(velocityX()) >  1 || getAction() == 5)
    advanceFrame();
    Sprite::update();
}
