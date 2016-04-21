#include "enemysprite.h"

EnemySprite::EnemySprite(const string& n, const string& w) :
    SmartSprite(n),
    weapon(w),
    sounds( SDLSound::getInstance() ),
    interval(Gamedata::getInstance().getXmlInt(n + "AttackInterval")),
    elapsed(0),
    health(100)
{
        weapon.X(X()-28);
        weapon.Y(Y()+50);
        weapon.velocityX(-400);
        weapon.velocityY(0);
}
void EnemySprite::update(){
    elapsed += Clock::getInstance().getTicks();
    weapon.update(); 
    if(elapsed >= interval) {
            elapsed = 0;
            weapon.explode();
            throwObject();
    } 
    SmartSprite::update();
}
void EnemySprite::throwObject() {
    
    if(velocityX()>0){
        weapon.X(X()+28);
        weapon.Y(Y()+50);
        weapon.velocityX(400);
        weapon.velocityY(0);
    }
    else {
        weapon.X(X()-28);
        weapon.Y(Y()+50);
        weapon.velocityX(-400);
        weapon.velocityY(0);
    }
}
