#ifndef SPRITE__H
#define SPRITE__H

#include <string>
using std::string;
#include <iostream>
#include <cmath>
#include "drawable.h"
#include "frame.h"
#include "clock.h"
#include "spritefactory.h"

class Sprite : public Drawable {
public:
  Sprite(const string& n);
  Sprite(const string& n, AbstractFactory& factory);
  Sprite(const Vector2f& pos, const Vector2f& vel,
         const string& n, const Frame*);
  Sprite(const Sprite& s);
  Sprite& operator=(const Sprite&);
  virtual ~Sprite() { } 
  const string& getName() const { return name; }
  int getAction() { return action; }
  void setName(const string& n) { name = n; }
  virtual void react(int xs, int ys) { velocityX(xs); velocityY(ys); }
  virtual const Frame* getFrame() const { return frame; }
  virtual void setFrame(const Frame* f) { frame = f; }
  virtual void draw() const;
  void initialize();
  int worldW() const { return worldWidth; }
  int worldH() const { return worldHeight; }
  virtual void update();
  virtual unsigned getPixel(Uint32, Uint32) const;

  Vector2f getCenter() const { 
    return Vector2f( X()+frame->getWidth()/2, Y()+frame->getHeight()/2 );
  }

private:
    string name;
    int bounceFactor;
    int action;
protected:
    int worldWidth;
    int worldHeight;
    const Frame * frame;
    int getDistance(const Sprite*) const;
};
#endif
