#ifndef PLAYERMANAGER__H
#define PLAYERMANAGER__H
#include "playersprite.h"

class PlayerManager{
public:
    PlayerManager(const string& n);
    virtual ~PlayerManager() { } 
    void draw() const { player.draw(); }
    void update();
    const Sprite& getPlayer(){ return player;  }
    PlayerWeapon& getWeapons(){ return player.getWeapons();  }
    Vector2f getData(){  return player.getData();}
    void adjustScore(int points){ player.adjustScore(points); }
    void adjustHealth(int points){ player.adjustHealth(points); }
    void setWorld(int w){ player.setWorld(w); }
    void resetWorld(){ player.resetWorld(); }
    void explode(int i){ player.explodeWeapon(i); }
    void jump(){ player.jump(); }
    void crouch(){ player.crouch(); }
    void stop(){ player.stop(); }
    void stopJump(){ player.stopJump(); }
    void stand(){ player.stand(); }
    void die(){ player.die(); }
    void revive(){ player.revive(); }
    //void kick(){ player.kick(); }
    //void move(int dir){ player.move(dir); }
    void moveRight(){ player.moveRight(); }
    void moveLeft(){ player.moveLeft(); }
    //void recoil(int dir){ player.recoil(dir); }
    void react(int xs, int ys){ player.react(xs,ys); }
    float X() const { return player.X(); }
    float Y() const { return player.Y(); }
    float velocityX() const { return player.velocityX(); }
    float velocityY() const { return player.velocityY(); }
    bool checkCollision(const Sprite& sprite){ return player.checkCollision(sprite); }
    bool checkRCollision(const Sprite& sprite){ return player.checkRCollision(sprite); }
    void changeWeapon(int i){ player.changeWeapon(i); }
    void throwObject(int i){ player.throwObject(i); }
private:
    //int score;
    //int health;
    PlayerSprite  player;
    PlayerManager(const PlayerManager&);
    PlayerManager& operator=(const PlayerManager&);
};
#endif
