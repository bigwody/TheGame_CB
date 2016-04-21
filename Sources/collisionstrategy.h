#include <cmath>
#include "playersprite.h"
#include <vector>
#include <algorithm>
#include "viewport.h"

using std::vector;
class CollisionStrategy {
public:
  virtual ~CollisionStrategy(){};
  virtual bool execute(const Sprite&, const Sprite&) const = 0;
};

class MidPointCollisionStrategy : public CollisionStrategy {
public:
  MidPointCollisionStrategy() {}
  virtual bool execute(const Sprite&, const Sprite&) const;
  float distance(float, float, float, float) const;
};

class RectangularCollisionStrategy : public CollisionStrategy {
public:
  RectangularCollisionStrategy() {}
  virtual bool execute(const Sprite&, const Sprite&) const;
  float distance(float, float, float, float) const;
};

class PerPixelCollisionStrategy : public CollisionStrategy {
public:
  PerPixelCollisionStrategy() {}
  virtual bool execute(const Sprite&, const Sprite&) const;
  float distance(float, float, float, float) const;
};
