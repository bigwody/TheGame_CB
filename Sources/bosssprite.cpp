#include "bosssprite.h"

BossSprite::BossSprite(const string& n, const string& w) :
    SmartSprite(n),
    weapon(w),
    balls("ball"),
    player(),
    sounds( SDLSound::getInstance() ),
    gameover(false),
    interval(Gamedata::getInstance().getXmlInt(n + "AttackInterval")),
    elapsed(0),
    health(100)
{
        weapon.X(X()-28);
        weapon.Y(Y()+50);
        weapon.velocityX(-400);
        weapon.velocityY(0);
}
void BossSprite::update(){
    elapsed += Clock::getInstance().getTicks();
    weapon.update(); 
    if(gameover)
        balls.update();
    if(elapsed >= interval) {
            elapsed = 0;
            weapon.explode();
            throwObject();
    } 
    if(gameover)
        IOManager::getInstance().printMessageAt("You Have Beaten The Game", 240, 199);
    SmartSprite::update();
}
void BossSprite::throwObject() {
    
        if(player->Y() > 300 && (X()-player->X()) < 300)
            weapon.velocityY(0);
        else
            weapon.velocityY(-abs(player->Y()-640));
        weapon.X(X()-28);
        weapon.Y(Y()+100);
        weapon.velocityX(-400);
}
