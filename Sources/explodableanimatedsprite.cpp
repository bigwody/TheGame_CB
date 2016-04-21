#include "explodableanimatedsprite.h"


ExplodableAnimatedSprite::ExplodableAnimatedSprite(const string& n) :
    AnimatedSprite(n),
    explosion(*this)
{   
    explosion.clearChunks();
}
void ExplodableAnimatedSprite::draw() const { 
    AnimatedSprite::draw();
    explosion.draw();
}
void ExplodableAnimatedSprite::drawExplosion() const { 
    explosion.draw();
}
void ExplodableAnimatedSprite::update() { 
    AnimatedSprite::update();
    explosion.update();
}
void ExplodableAnimatedSprite::updateExplosion() { 
    explosion.update();
}
void ExplodableAnimatedSprite::explode() { 
    explosion.X(X());
    explosion.Y(Y());
    explosion.makeChunks();
}
