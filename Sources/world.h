#ifndef WORLD__H
#define WORLD__H
#include "viewport.h"
#include "gamedata.h"
#include "spritefactory.h"

class World {
public:
    World() :
        gdata(Gamedata::getInstance()),
        frame1(SpriteFactory::getInstance().getFrame("worldBackground1")),
        frame2(SpriteFactory::getInstance().getFrame("worldBackground2")),
        frame3(SpriteFactory::getInstance().getFrame("worldBackground3")),
        frameWidth(gdata.getXmlInt("worldBackground1Width")),
        worldWidth(gdata.getXmlInt("worldWidth")),
        worldX(0.0),
        worldY(0.0),
        factor1(gdata.getXmlFloat("worldBackground1Factor")),
        factor2(gdata.getXmlFloat("worldBackground2Factor")),
        factor3(gdata.getXmlFloat("worldBackground3Factor")),
        view(Viewport::getInstance())
    { }
    virtual ~World(){}
    void drawbackground() const { frame1->draw(static_cast<int>(worldX/factor1)%1280, worldY, 0, 0); 
        frame2->draw(static_cast<int>(worldX/factor2)%1280, worldY, 0, 0); }
    void drawforeground() const { frame3->draw(static_cast<int>(worldX)%1280, worldY, 0, 0); }
    void update(){ worldX = view.X(); worldY = view.Y();}
private:
    Gamedata& gdata;
    const Frame * frame1;
    const Frame * frame2;
    const Frame * frame3;
    unsigned frameWidth;
    unsigned worldWidth;
    float worldX;
    float worldY;
    int factor1;
    int factor2;
    int factor3;
    const Viewport& view;
    World(const World&);
    World& operator=(const World&);
};
#endif
