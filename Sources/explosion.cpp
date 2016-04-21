#include <iostream>
#include <cmath>

#include "explosion.h"

void Explosion::update() { 
  int ticks = Clock::getInstance().getTicks();
  velocityY(velocityY()-1);
  float yincr = velocityY() * static_cast<float>(ticks) * 0.001;
  Y( Y()- yincr );
  float xincr = velocityX() * static_cast<float>(ticks) * 0.001;
  X( X()- xincr );
  distance += ( hypot(xincr, yincr) );
}

