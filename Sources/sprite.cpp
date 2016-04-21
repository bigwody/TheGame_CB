#include "sprite.h"

Sprite::Sprite(const Vector2f& pos, const Vector2f& vel, 
               const string& n, const Frame* fm) :
    Drawable(pos, vel, 
           Vector2f(Gamedata::getInstance().getXmlInt(n+"MaxXSpeed"),
                    Gamedata::getInstance().getXmlInt(n+"MaxYSpeed"))
    ), 
    name(n),
    bounceFactor(Gamedata::getInstance().getXmlInt(n + "BounceFactor")),
    action(Gamedata::getInstance().getXmlInt(n + "Action")),
    worldWidth(Gamedata::getInstance().getXmlInt("worldWidth")),
    worldHeight(Gamedata::getInstance().getXmlInt("worldHeight")),
    frame(fm)
{ }
Sprite::Sprite(const string& n) :
    Drawable(Vector2f(Gamedata::getInstance().getXmlInt(n+"XLoc"),
                    Gamedata::getInstance().getXmlInt(n+"YLoc")), 
           Vector2f(Gamedata::getInstance().getXmlInt(n+"XSpeed"),
                    Gamedata::getInstance().getXmlInt(n+"YSpeed")),
           Vector2f(Gamedata::getInstance().getXmlInt(n+"MaxXSpeed"),
                    Gamedata::getInstance().getXmlInt(n+"MaxYSpeed"))
                    ), 
    name(n),
    bounceFactor(Gamedata::getInstance().getXmlInt(n + "BounceFactor")),
    action(Gamedata::getInstance().getXmlInt(n + "Action")),
    worldWidth(Gamedata::getInstance().getXmlInt("worldWidth")),
    worldHeight(Gamedata::getInstance().getXmlInt("worldHeight")),
    frame(SpriteFactory::getInstance().getFrame(name))
{
    initialize();
}
Sprite::Sprite(const string& n, AbstractFactory& factory) :
    Drawable(Vector2f(Gamedata::getInstance().getXmlInt(n+"XLoc"),
                    Gamedata::getInstance().getXmlInt(n+"YLoc")), 
           Vector2f(Gamedata::getInstance().getXmlInt(n+"XSpeed"),
                    Gamedata::getInstance().getXmlInt(n+"YSpeed")),
           Vector2f(Gamedata::getInstance().getXmlInt(n+"MaxXSpeed"),
                    Gamedata::getInstance().getXmlInt(n+"MaxYSpeed"))
                    ), 
    name(n),
    bounceFactor(Gamedata::getInstance().getXmlInt(n + "BounceFactor")),
    action(Gamedata::getInstance().getXmlInt(n + "Action")),
    worldWidth(Gamedata::getInstance().getXmlInt("worldWidth")),
    worldHeight(Gamedata::getInstance().getXmlInt("worldHeight")),
    frame(factory.getFrame(name))
{ 
initialize();
}
void Sprite::initialize() {
     if(action == 5) {
        X(Gamedata::getInstance().getXmlInt(name + "XLoc"));
    }
    if(Gamedata::getInstance().getXmlBool(name+"Randomize")) {
        X(rand() % 12000 + 10);
        Y(rand() % 350 + 10);
        velocityX(rand() % Gamedata::getInstance().getXmlInt(name + "MaxXSpeed") + 10);
        velocityY(rand() % Gamedata::getInstance().getXmlInt(name + "MaxYSpeed") + 10);
        velocityX(velocityX() * (rand() % 3 ? 1 : 1));
        velocityY(velocityY() *  (rand() % 2 ? 1 : -1));
    }
}
void Sprite::draw() const { 
    Uint32 x = static_cast<Uint32>(X());
    Uint32 y = static_cast<Uint32>(Y());
    frame->draw(x, y); 
}
unsigned Sprite::getPixel(Uint32 i, Uint32 j) const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  x = i - x;
  y = j - y;
  return frame->getPixel(x,y);
}
int Sprite::getDistance(const Sprite *obj) const { 
  return hypot(X()-obj->X(), Y()-obj->Y());
}
void Sprite::update() { 
    int ticks = Clock::getInstance().getTicks();
    float height = static_cast<float>(frame->getHeight())+6;
    float width = static_cast<float>(frame->getWidth());
    if(action == 0) {//gravity//
        if(velocityY() >= 0 && Y() < worldHeight-height) 
            velocityY(velocityY() + bounceFactor);
        else if(velocityY() < 0) 
            velocityY(velocityY()+5);
        if(velocityX() > 0) 
            velocityX(velocityX()-.2);
        else if(velocityX() < 0) 
            velocityX(velocityX()+.2);
        if ( Y() > worldHeight-height ) 
            velocityY( -abs( velocityY() ) );
        if ( Y() >= worldHeight -height && abs(velocityY()) < 6) 
            velocityY(0);
        if ( X() < 0) 
            velocityX( abs( velocityX() ) );
        else if ( X() > worldWidth - width)
                velocityX( -abs( velocityX() ) );
    }
    else if(action == 1) {//wrap//
        if ( Y() < 0) 
            velocityY( abs( velocityY() ) );
        else if ( Y() > worldHeight-height) 
            velocityY( -abs( velocityY() ) );
        if ( X() > worldWidth) 
            X(0-width);
        else if ( X() < 0-width) 
            X(worldWidth);
    }
    else if(action == 2) {//bounce//
        if ( Y() < 0) 
            velocityY( abs( velocityY() ) );
        else if ( Y() > worldHeight-height) 
            velocityY( -abs( velocityY() ) );
        if ( X() < 0) 
            velocityX( abs( velocityX() ) );
        else if ( X() > worldWidth - width)
            velocityX( -abs(velocityX()));
    }
    else if(action == 3) {//sticky//
        if(velocityX() != 0) 
            velocityY(velocityY()+1);
        if ( Y() < 0) 
            velocityY( abs( velocityY() ) );
        if ( X() < 0) {
            velocityX(0);
            velocityY(0);
        }
        else if ( X() > worldWidth - width){
            velocityX(0);
            velocityY(0);
        }
        else if ( Y() > worldHeight - height) {
            velocityX(0);
            velocityY(0);
        }
    }
    else if(action == 4) {//fall//
        if ( X() <= 0 || X() > worldWidth - width){
            velocityX(0);
            velocityY(100);
        }
        if ( Y() >= worldHeight-height ) 
            velocityY( 0 );
    }
    float incr = velocityY() * static_cast<float>(ticks) * 0.001;
    Y( Y()+incr );
    incr = velocityX() * static_cast<float>(ticks) * 0.001;
    X( X()+incr );
}
Sprite::Sprite(const Sprite& s) :
    Drawable(s.getPosition(), s.getVelocity(), s.getMaxVelocity()), 
    name( s.getName() ),
    bounceFactor(Gamedata::getInstance().getXmlInt(s.getName() + "BounceFactor")),
    action(Gamedata::getInstance().getXmlInt(s.getName() + "Action")),
    worldWidth(Gamedata::getInstance().getXmlInt("worldWidth")),
    worldHeight(Gamedata::getInstance().getXmlInt("worldHeight")),
    frame(s.frame)
{ }
Sprite& Sprite::operator=(const Sprite& rhs) {
    setName( rhs.getName() );
    setPosition(rhs.getPosition());
    setVelocity(rhs.getVelocity());
    setMaxVelocity(rhs.getMaxVelocity());
    bounceFactor = Gamedata::getInstance().getXmlInt(rhs.getName() + "BounceFactor");
    action = Gamedata::getInstance().getXmlInt(rhs.getName() + "Action");
    worldWidth = Gamedata::getInstance().getXmlInt("worldWidth");
    worldHeight = Gamedata::getInstance().getXmlInt("worldHeight");
    frame = rhs.frame;
    return *this;
}

