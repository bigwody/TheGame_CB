#ifndef EXPLODABLEANIMATEDSPRITE__H
#define EXPLODABLEANIMATEDSPRITE__H

#include <string>
using std::string;
#include <iostream>
#include <cmath>
#include "animatedsprite.h"
#include "explodingsprite.h"
#include "viewport.h"

class ExplodableAnimatedSprite : public AnimatedSprite {
public:
  ExplodableAnimatedSprite(const string& n);
  virtual ~ExplodableAnimatedSprite() { } 
  virtual void update();
  virtual void updateExplosion();
  virtual void draw() const;
  virtual void drawExplosion() const;
  void explode();

private:
    ExplodingSprite explosion;
    ExplodableAnimatedSprite(const ExplodableAnimatedSprite& s);
    ExplodableAnimatedSprite& operator=(const ExplodableAnimatedSprite&);
  
};
#endif
