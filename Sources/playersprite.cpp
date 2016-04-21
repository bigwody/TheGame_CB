#include "playersprite.h"

PlayerSprite::PlayerSprite(const string& n) : 
        Sprite(n, AnimationFactory::getInstance()),
        throwable(new PlayerWeapon("weapon0")),
        sounds( SDLSound::getInstance() ),
        totalTicks(0),
        currentFrame(0),
        difficulty(0),
        direction(1),
        spacer(8),
        world(Gamedata::getInstance().getXmlInt("worldHeight")),
        score(0),
        health(100),
        frameInterval(Gamedata::getInstance().getXmlInt(n+"FrameInterval")),
        numFrames(Gamedata::getInstance().getXmlInt(n+"FrameCount")),
        alive(true),
        action(false)
{ }
string PlayerSprite::getDifficulty() {
    if(difficulty == 0)
        return("Easy");
    else if(difficulty == 1)
        return("Medium");
    else
        return("Hard");
}
void PlayerSprite::moveRight() {
    if(alive) { 
        direction=1;
        spacer = 8;
        if(velocityX() < 300)
            velocityX(velocityX()+20);
        else
            velocityX(300);
    }
}
void PlayerSprite::moveLeft() {
    if(alive) {
        direction=0;
        spacer = 0;
        if(velocityX() > -300)
            velocityX(velocityX()-20);
        else
         velocityX(-300);
     }
}
void PlayerSprite::jump() {
    if(!alive)
        return;
    if(velocityY() == 0) {
         sounds[1];
        action = true;
    }
    if(velocityY() <= 0 && action) {
        if(velocityY() > -500) 
         velocityY(velocityY()-50);
        else
            velocityY(-500);
       currentFrame=4;
    }
}
void PlayerSprite::die() {
    if(alive){
        sounds[5];
        alive = false;
       currentFrame=0;
        velocityX(0);
        spacer = direction*5;
        setFrame(AnimationFactory::getInstance().getFrame("playerdeath"));
    }
}
void PlayerSprite::revive() {
    if(!alive) {
        health=100; 
        alive = true;
        currentFrame=0;
        spacer = direction*8;
        setFrame(AnimationFactory::getInstance().getFrame("player"));
    }
}
void PlayerSprite::advanceFrame(Uint32 ticks) {
    totalTicks += ticks;
    if(alive) {
        if(abs(velocityX()) > 5) {
            if(direction == 0 && velocityX() > 0) {
                currentFrame=0;
            }
            else if(direction == 1 && velocityX() < 0) {
                currentFrame=0;
            }
            else if (totalTicks > frameInterval) {
                ++currentFrame;
                currentFrame%=4;
                totalTicks = 0;
            }
        }
    } 
   else if(currentFrame < 4 && totalTicks > frameInterval) {
            ++currentFrame;
            totalTicks = 0;
    }
}
void PlayerSprite::changeWeapon(int weapon) {
    delete throwable;
    if(weapon == 0) {
        throwable = new PlayerWeapon("weapon0");
    }
    if(weapon == 1) {
        throwable = new PlayerWeapon("weapon1");
    }
    if(weapon == 2) {
        throwable = new PlayerWeapon("weapon2");
    }
    if(weapon == 3) {
        throwable = new PlayerWeapon("weapon3");
    }
}
void PlayerSprite::throwObject(int dir) {
    if(alive) {
        if(velocityX()==0){ 
            action=true; 
            currentFrame=6; 
        }
        sounds[3];
        throwable->loadNext(X()+(direction*28),Y()+50,((direction*2)-1)*400,(dir*400)+10);
    }
}
void PlayerSprite::update() { 
    throwable->update();
    float height = static_cast<float>(frame->getHeight())+6;
    int ticks = Clock::getInstance().getTicks();
        if(Y() < world-300) {
            if(velocityY()<0)
                velocityY(7);
            else if(velocityY()>-300)
                velocityY(velocityY() + 7);
            if(alive){
                currentFrame=0;
		        //action = false;
	        }
        }   
        if(Y() > world-height) {
            velocityY(0);
            Y(world-height);
            if(velocityX()==0 && !action && alive){
                currentFrame=0;
                //action = false;
	        }
        }
        else
            velocityY(velocityY()+7);
        if(abs(velocityX()) <= 10)
            velocityX(0);
        else if(abs(velocityX()) != 300){
        if(velocityX() > 0)
                velocityX(velocityX()-1);
            else 
                velocityX(velocityX()+1);
        }
    
   
        float incr = velocityY() * static_cast<float>(ticks) * 0.001;
        Y( Y()+incr );
        incr = velocityX() * static_cast<float>(ticks) * 0.001;
        X( X()+incr );
	    //if(abs(velocityX()) > 5)
            advanceFrame(ticks);
   
    //else if(!action)
    //    setCurrentFrame(0);
}
unsigned PlayerSprite::getPixel(Uint32 i, Uint32 j) const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  x = i - x;
  y = j - y;
  return frame[currentFrame+spacer].getPixel(x,y);
}
bool PlayerSprite::checkRCollision(const Sprite& obj) {
  if(!alive)
    return(false);
  int viewX = Viewport::getInstance().X();
  if(obj.X()+obj.getFrame()->getWidth() < viewX || obj.X() > (viewX+640))
    return false;
  float left1 = X();
  float left2 = obj.X();
  float right1 = left1+getFrame()->getWidth();
  float right2 = left2+obj.getFrame()->getWidth();
  float top1 = Y();
  float top2 = obj.Y();
  float bottom1 = top1+getFrame()->getHeight();
  float bottom2 = top2+obj.getFrame()->getHeight();
  if ( right1 < left2 ) return false;
  if ( left1 > right2 ) return false;
  if ( bottom1 < top2 ) return false;
  if ( bottom2 < top1 ) return false;
  else return true;
}
bool PlayerSprite::checkCollision(const Sprite& obj) {
  if(!alive)
    return(false);
  int viewX = Viewport::getInstance().X();
  if(obj.X()+obj.getFrame()->getWidth() < viewX || obj.X() > (viewX+640))
    return false;
  float left1 = X();
  float left2 = obj.X();
  float right1 = left1+getFrame()->getWidth();
  float right2 = left2+obj.getFrame()->getWidth();
  float top1 = Y();
  float top2 = obj.Y();
  float bottom1 = top1+getFrame()->getHeight();
  float bottom2 = top2+obj.getFrame()->getHeight();
  if ( right1 < left2 ) return false;
  if ( left1 > right2 ) return false;
  if ( bottom1 < top2 ) return false;
  if ( bottom2 < top1 ) return false;
  else {
    const Frame * const frame2 = obj.getFrame();
    vector<int> x;
    x.reserve(4);
    x.push_back( left1 );
    x.push_back( right1 );
    x.push_back( left2 );
    x.push_back( right2 );
    std::sort( x.begin(), x.end() );
    Vector2f p1 = obj.getPosition();
    vector<int> y;
    y.reserve(4);
    y.push_back( top1);
    y.push_back( bottom1 );
    y.push_back( top2);
    y.push_back( bottom2 );
    std::sort( y.begin(), y.end() );
    SDL_Surface* surface1 = getFrame()->getSurface();
    SDL_Surface* surface2 = frame2->getSurface();
    SDL_LockSurface(surface1);
    SDL_LockSurface(surface2);
    unsigned pixels1;
    unsigned pixels2;

    for (int i = x[1]; i < x[2]; ++i) {
    for (int j = y[1]; j < y[2]; ++j) {
      pixels1 = getPixel(i, j);
      pixels2 = obj.getPixel(i, j);
      
      if ( pixels1 != 16711935 && pixels2 != 16711935) {
        SDL_UnlockSurface(surface1);
        SDL_UnlockSurface(surface2);
        return true;
      }
    }
    }
    SDL_UnlockSurface(surface1);
    SDL_UnlockSurface(surface2);
    return false;
    }
}
/*void PlayerSprite::move(int dir) {
    if(!alive)
        return;
    if(direction != dir){ 
        direction = dir;
        totalTicks = 0;
        currentFrame = 0;
    }
    spacer = dir*8;
    if(abs(velocityX()) < 300)
        velocityX(velocityX()+(((dir*2)-1)*20));
    else
        velocityX(((dir*2)-1)*300);
}*/
