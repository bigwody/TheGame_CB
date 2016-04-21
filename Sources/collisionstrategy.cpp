#include "ioManager.h"
#include "collisionstrategy.h"

bool MidPointCollisionStrategy::execute(
      const Sprite& obj1, const Sprite& obj2) const {
  int COLLISION_DISTANCE = 
    obj1.getFrame()->getWidth()/2 + obj2.getFrame()->getWidth()/2;
  float xobj1 = obj1.X()+obj1.getFrame()->getWidth()/2;
  float yobj1 = obj1.Y()+obj1.getFrame()->getHeight()/2;
  float xobj2 = obj2.X() + obj2.getFrame()->getWidth()/2;
  float yobj2 = obj2.Y() + obj2.getFrame()->getHeight()/2;
  return distance(xobj1, yobj1, xobj2, yobj2) < COLLISION_DISTANCE;
}

float MidPointCollisionStrategy::
distance(float x1, float y1, float x2, float y2) const {
  float x = x1-x2, y = y1-y2;
  return hypot(x, y);
}
bool RectangularCollisionStrategy::execute(
     const Sprite& obj1, const Sprite& obj2) const {
  //only calculate collisions that are in view //
  int x = Viewport::getInstance().X();
  if(obj1.X()+obj1.getFrame()->getWidth() < x || obj1.X() > (x+640))
    return false;
  if(obj2.X()+obj2.getFrame()->getWidth() < x || obj2.X() > (x+640))
    return false;
  float left1 = obj1.X();
  float left2 = obj2.X();
  float right1 = left1+obj1.getFrame()->getWidth();
  float right2 = left2+obj2.getFrame()->getWidth();
  float top1 = obj1.Y();
  float top2 = obj2.Y();
  float bottom1 = top1+obj1.getFrame()->getHeight();
  float bottom2 = top2+obj2.getFrame()->getHeight();
  if ( right1 < left2 ) return false;
  if ( left1 > right2 ) return false;
  if ( bottom1 < top2 ) return false;
  if ( bottom2 < top1 ) return false;
  return true;
}
bool PerPixelCollisionStrategy::execute(
  const Sprite& obj1, const Sprite& obj2) const {
   RectangularCollisionStrategy strategy;
    if ( !strategy.execute(obj1, obj2) ) return false;
    Vector2f p1 = obj1.getPosition();
    Vector2f p2 = obj2.getPosition();
    const Frame * const frame1 = obj1.getFrame();
    const Frame * const frame2 = obj2.getFrame();
    int o1Left = p1[0]; 
    int o1Right = o1Left+frame1->getWidth();
    int o2Left = p2[0]; 
    int o2Right = o2Left+(frame2->getWidth());
    vector<int> x;
    x.reserve(4);
    x.push_back( o1Left +1);
    x.push_back( o1Right );
    x.push_back( o2Left +1);
    x.push_back( o2Right );
    std::sort( x.begin(), x.end() );

    int o1Up = p1[1];
    int o1Down = o1Up+frame1->getHeight();
    int o2Up = p2[1];
    int o2Down = o2Up+frame2->getHeight();
    vector<int> y;
    y.reserve(4);
    y.push_back( o1Up +1);
    y.push_back( o1Down );
    y.push_back( o2Up +1);
    y.push_back( o2Down );
    std::sort( y.begin(), y.end() );

    SDL_Surface* surface1 = frame1->getSurface();
    SDL_Surface* surface2 = frame2->getSurface();

    SDL_LockSurface(surface1);
    SDL_LockSurface(surface2);
    unsigned pixels1;
    unsigned pixels2;
    for (int i = x[1]; i < x[2]; ++i) {
    for (int j = y[1]; j < y[2]; ++j) {
      pixels1 = obj1.getPixel(i, j);
      pixels2 = obj2.getPixel(i, j);
      
      if ( pixels1 != 16711935 && pixels2 != 16711935) {
        SDL_UnlockSurface(surface1);
        SDL_UnlockSurface(surface2);
        return true;
      }
    }
    }
    SDL_UnlockSurface(surface1);
    SDL_UnlockSurface(surface2);

    return false;
    }

