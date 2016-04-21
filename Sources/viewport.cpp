#include "viewport.h"

Viewport& Viewport::getInstance() {
  static Viewport view;
  return view;
}
Viewport::Viewport() : 
  gdata(Gamedata::getInstance()),
  objToTrack(), 
  viewX(0), viewY(0), 
  objWidth(0), objHeight(0),
  viewWidth(gdata.getXmlInt("viewWidth")), 
  viewHeight(gdata.getXmlInt("viewHeight")), 
  worldWidth(gdata.getXmlInt("worldWidth")), 
  worldHeight(gdata.getXmlInt("worldHeight"))
{
}
void Viewport::update() {
  const float x = objToTrack->X();
  const float y = objToTrack->Y();
  viewX = (x + objWidth/2) - viewWidth/2 +150;
  viewY = (y + objHeight/2) - viewHeight/2;
  
  if (viewX < 0) viewX = 0;
  if (viewY < 0) viewY = 0;
  if (viewX > (worldWidth - viewWidth)) 
    viewX = worldWidth-viewWidth;
  if (viewY > (worldHeight - viewHeight)) 
    viewY = worldHeight-viewHeight;
}
void Viewport::setObjectToTrack(const Sprite* s) {
    objToTrack = s; 
    objWidth = objToTrack->getFrame()->getWidth();
    objHeight = objToTrack->getFrame()->getHeight();
}
