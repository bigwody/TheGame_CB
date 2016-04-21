#ifndef ANIMATEDSPRITE__H
#define ANIMATEDSPRITE__H

#include <iostream>
#include "sprite.h"
#include "animationfactory.h"

class AnimatedSprite : public Sprite {
public:
    AnimatedSprite(const string& n);
    AnimatedSprite(const Vector2f& p, const Vector2f v, const Vector2f m, 
        const string& n, const Frame* fm);
    virtual ~AnimatedSprite() {  } 
    virtual void advanceFrame();
    virtual void draw() const { frame[currentFrame].draw(X(), Y()); }
    virtual void update();
    virtual const Frame* getFrame() const { return &frame[currentFrame]; }
    virtual int getFrameCount() const{ return numberOfFrames; }
    virtual int getCurrentFrame() const{ return currentFrame; }
    //virtual void setCurrentFrame(int i) { currentFrame = i; }
    virtual void modifyFrameIndex(int i) { currentFrame %= i; }
private:
    unsigned totalTicks;
    unsigned currentFrame;
    unsigned numberOfFrames;
    unsigned frameInterval;
    AnimatedSprite(const AnimatedSprite&);
    AnimatedSprite& operator=(const AnimatedSprite&);
};
#endif
