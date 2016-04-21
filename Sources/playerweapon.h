#include <iostream>
#include "gamedata.h"
#include "explodableanimatedsprite.h"
#include <vector>
using std::vector;

class PlayerWeapon {
public:
    PlayerWeapon(const string& name);
    virtual ~PlayerWeapon(){ for(unsigned int i = 0; i < max_sprites; ++i) delete(sprites[i]); }
    void update(){  for(unsigned int i = 0; i < index; ++i) sprites[i]->update(); }
    void draw() const { for(unsigned int i = 0; i < index; ++i) sprites[i]->draw(); }
    void loadSprites(){ for (unsigned int i = 0; i <  max_sprites; ++i) sprites.push_back(new ExplodableAnimatedSprite(name)); }
    void explodeWeapon(int i){ sprites[i]->explode(); sprites[i]->X(-1000); }
    unsigned activeSpriteCount(){ return index; }
    ExplodableAnimatedSprite* operator[](int index) const{ return sprites[index];}
    void loadNext(float, float, float, float);
    void loadNext();
private:
    vector<ExplodableAnimatedSprite*> sprites;
    string name;
    Gamedata& gdata;
    unsigned int max_sprites;
    unsigned int index;
    unsigned int current;
    PlayerWeapon(const PlayerWeapon&);
    PlayerWeapon& operator=(const PlayerWeapon&);
};
