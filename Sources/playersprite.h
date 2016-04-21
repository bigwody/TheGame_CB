#ifndef PLAYERSPRITE__H
#define PLAYERSPRITE__H

#include <iostream>
#include "sprite.h"
#include "animationfactory.h"
#include "playerweapon.h"
#include "viewport.h"
#include <algorithm>
using std::vector;

class PlayerSprite : public Sprite {
public:
    PlayerSprite(const string&);
    virtual ~PlayerSprite() { delete throwable; } 
    virtual void draw() const { throwable->draw(); frame[currentFrame+spacer].draw(X(), Y());}
    virtual const Frame* getFrame() const { return &frame[currentFrame+spacer]; }
    virtual unsigned getPixel(Uint32, Uint32) const;
    int getDir(){ return(direction); }
    bool isAlive(){ return(alive); }
    void setWorld(int w){ world = w; }
    void resetWorld(){ world = 480; }
    void adjustScore(int points){ score+=points; }
    Vector2f getData(){  return Vector2f(score,health);}
    string getDifficulty();
    PlayerWeapon& getWeapons(){ return *throwable;  }
    void explodeWeapon(int i){ throwable->explodeWeapon(i); }
    void adjustHealth(int points){ health+=(difficulty+1)*points; if(health<=0) die(); }
    void changeDifficulty(){ difficulty+=1; difficulty%=3; }
    void throwObject();
    void crouch() { if(alive){ velocityX(0); currentFrame=5; }}
    void stop(){ if(alive) { if(velocityX() == 0) currentFrame=0; action=false; } }
    void stopJump(){ if(alive) { action=false; } }
    void stand(){ if(alive) {  velocityX(0); currentFrame=0;} }
    void changeWeapon(int);
    void throwObject(int);
    //void kick(){ currentFrame = 7; velocityX(0); }
    void update();
    //void move(int);
    void moveRight();
    void moveLeft();
    //void recoil(int);
    void jump();
    void die();
    void revive();
    bool checkCollision(const Sprite&);
    bool checkRCollision(const Sprite&);
private:
    PlayerWeapon * throwable;
    SDLSound &sounds;
    unsigned totalTicks;
    unsigned currentFrame;
    int difficulty;
    int direction;
    int spacer;
    int world;
    int score;
    int health;
    unsigned frameInterval;
    unsigned numFrames;
    bool alive;
    bool action;
    
    void advanceFrame(Uint32);
    PlayerSprite(const PlayerSprite&);
    PlayerSprite& operator=(const PlayerSprite&);
};
#endif
