#ifndef HUD__H
#define HUD__H
#include "gamedata.h"
#include "ioManager.h"
#include "animationfactory.h"

class Hud {
public:
    Hud() :
        gdata(Gamedata::getInstance()),
        io(IOManager::getInstance()),
        frame(SpriteFactory::getInstance().getFrame("HUD")),
        frame1(AnimationFactory::getInstance().getFrame("weapon0")),
        HUDenabled(true),
        weapon_id(0)
    { }
    virtual ~Hud(){};
    void draw(const Vector2f& player_data) { if(HUDenabled){ frame->draw(0,0,0,0); 
        io.printMessageValueAt("Score : ", player_data[0], 20, 14); 
        io.printMessageValueAt("Health : ", player_data[1], 20, 29); 
        io.printMessageValueAt("FPS : ", Clock::getInstance().getFps(), 20, 44);
        frame1->draw(Viewport::getInstance().X()+580-((frame1->getWidth()-32)/2),10);
    }}
    void updateWeapon(int id){
        if(weapon_id != id) {
            weapon_id = id;
            if(id == 0)
                frame1 = AnimationFactory::getInstance().getFrame("weapon0");
            if(id == 1)
                frame1 = AnimationFactory::getInstance().getFrame("weapon1");
            if(id == 2)
                frame1 = AnimationFactory::getInstance().getFrame("weapon2");
            if(id == 3)
                frame1 = AnimationFactory::getInstance().getFrame("weapon3");
        }
    }
    void update(){ };
    void toggle() { if(HUDenabled) HUDenabled = false; else HUDenabled = true; }
private:
    Gamedata& gdata;
    IOManager& io;
    const Frame * frame;
    const Frame * frame1;
    bool HUDenabled;
    int weapon_id;
    Hud(const Hud&);
    Hud& operator=(const Hud&);
};
#endif
