#ifndef ENEMYSPRITE__H
#define ENEMYSPRITE__H
#include "smartsprite.h"

class EnemySprite : public SmartSprite{
public:
    EnemySprite(const string& n);
    virtual ~EnemySprite() {} 
    void draw() const { SmartSprite::draw();weapon.draw();}
    void update();
    const ExplodableAnimatedSprite& getWeapon(){ return weapon;  }
    void explodeEnemy() { explode(); move(); }
    void explodeWeapon() { weapon.explode(); weapon.Y(-1000); }
    void adjustHealth(int val){ health+=val;if(health <= 0){ explode(); move(); health=100; }}
    void throwObject();
private:
    ExplodableAnimatedSprite weapon;
    int interval;
    int elapsed;
    int health;
    EnemySprite(const EnemySprite&);
    EnemySprite& operator=(const EnemySprite&);
};
#endif
