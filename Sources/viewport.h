#ifndef VIEWPORT__H
#define VIEWPORT__H
#include "sprite.h"
class Viewport {
public:
    static Viewport& getInstance();
    ~Viewport(){};
    void update();
    const Sprite* getObjectToTrack() const { return objToTrack; }
    void setObjectToTrack(const Sprite*);
    float X() const { return viewX; }
    void X(float x) { viewX = x; }
    float Y() const { return viewY; }
    void Y(float y) { viewY = y; }
private:
    Gamedata& gdata;
    const Sprite * objToTrack;
    float viewX;
    float viewY;
    Uint16 objWidth;
    Uint16 objHeight;
    unsigned viewWidth;
    unsigned viewHeight;
    unsigned worldWidth;
    unsigned worldHeight;
    Viewport() ;    
    Viewport(const Viewport&);
    Viewport& operator=(const Viewport&);
};
#endif
