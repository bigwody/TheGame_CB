#ifndef SCENERYSPRITE__H
#define SCENERYSPRITE__H

#include <string>
using std::string;
#include <iostream>
#include <cmath>
#include "sprite.h"
#include "viewport.h"

class ScenerySprite : public Sprite{
public:
  ScenerySprite(const string& n);
  
  virtual ~ScenerySprite() { } 
  virtual void update();

private:
    unsigned increment;
    ScenerySprite(const ScenerySprite& s);
    ScenerySprite& operator=(const ScenerySprite&);
  
};
#endif
