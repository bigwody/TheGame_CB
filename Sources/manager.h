#include <SDL.h>
#include <iostream>
#include <string>
#include "world.h"
#include "hud.h"
#include "menu.h"
#include "playersprite.h"
#include "enemysprite.h"
#include "bosssprite.h"
#include "spritemanager.h"
#include "scenerysprite.h"
#include "collisionstrategy.h"

class Manager {
public:
    Manager ();
    ~Manager ();
    void play();
    void draw();
    void update();
    void checkCollisions();
private:
    const bool env;
    SDL_Surface * const screen;
    Clock& clock;
    
    World world;
    Hud hud;
    Menu menu;
    Viewport &view;
    PlayerSprite player;
    Sprite * powerup;
    Sprite surfboard;
    ScenerySprite platform;
    Sprite couch;
    EnemySprite enemy;
    EnemySprite enemy1;
    BossSprite boss;
    SpriteManager crows;
    SmartSprite block;
    SDLSound& sounds;

    CollisionStrategy *collisionStrategy;
    Manager(const Manager&);
    Manager& operator=(const Manager&);
};
