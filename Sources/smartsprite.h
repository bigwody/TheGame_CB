#ifndef SMARTSPRITE_H
#define SMARTSPRITE_H

#include <iostream>
#include "explodableanimatedsprite.h"
#include "animationfactory.h"
#include "viewport.h"


class SmartSprite : public ExplodableAnimatedSprite {
public:
    SmartSprite(const string& n);
    virtual ~SmartSprite() {  } 
    virtual void draw() const { frame[getCurrentFrame()+(direction*spacer)].draw(X(), Y()); drawExplosion();}
    virtual const Frame* getFrame() const { return &frame[getCurrentFrame()+(direction*spacer)]; }
    virtual void update();
    virtual void move();
    virtual void react(int dir);
private:
    int spacer;
    int direction;
    int xloc;
    unsigned range;
    int increment;
    SmartSprite(const SmartSprite&);
    SmartSprite& operator=(const SmartSprite&);
};
#endif
