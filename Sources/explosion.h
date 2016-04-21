#include <iostream>
#include "sprite.h"
#include "gamedata.h"

class Explosion : public Sprite {
public:
  explicit Explosion(
    const Vector2f& pos, const Vector2f& vel,
    const string& name, const Frame* fm) :
    Sprite(pos, vel, name, fm), 
    distance(0.0)
  { }
  virtual void update();
  float getDistance() const { return distance; }
  bool outOfBounds() const { 
    bool out = ( X() < 0 || X() > worldW() || 
                 Y() < 0 || Y() > worldH() ); 
    return out;
  }
  void reset() {
    distance = 0.0;
  }
private:
  float distance;
};
