#ifndef BOSSSPRITE__H
#define BOSSSPRITE__H
#include "smartsprite.h"
#include "spritemanager.h"

class BossSprite : public SmartSprite{
public:
    BossSprite(const string&,const string&);
    virtual ~BossSprite() { } 
    void draw() { SmartSprite::draw();weapon.draw(); if(gameover)balls.draw(); }
    void update();
    const ExplodableAnimatedSprite& getWeapon(){ return weapon;  }
    void explodeEnemy() { explode(); move(); }
    void explodeWeapon() { weapon.explode(); weapon.Y(-1000); }
    virtual void adjustHealth(int val){ health+=val;if(health <= 0){ sounds[6]; explode(); gameover=true; move(); balls.loadAll(); }}
    void playSound(int i){ sounds[i]; }
    void throwObject();
    void trackPlayer(Sprite* p){ player = p; }
private:
    ExplodableAnimatedSprite weapon;
    SpriteManager balls;
    Sprite * player;
    SDLSound &sounds;
    bool gameover;
    int interval;
    int elapsed;
    int health;
    BossSprite(const BossSprite&);
    BossSprite& operator=(const BossSprite&);
};
#endif
