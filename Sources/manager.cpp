#include "manager.h"

Manager::~Manager() {
    delete collisionStrategy;
    delete powerup;
}
Manager::Manager() :
    env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
    screen(IOManager::getInstance().getScreen() ),
    clock( Clock::getInstance() ),
    world(),
    hud(),
    menu(screen),
    view(Viewport::getInstance()),
    player("player"),
    powerup(new Sprite("item")),
    surfboard("surfboard"),
    platform("platform"),
    couch("couch"),
    enemy("enemy","weapon1"),
    enemy1("enemy1","weapon2"),
    boss("boss","weapon4"),
    crows("crow"),
    block("animatedblock"),
    sounds( SDLSound::getInstance() ),
    collisionStrategy( new PerPixelCollisionStrategy )
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        throw string("Unable to initialize SDL: ");
    atexit(SDL_Quit);
}


void Manager::play() {
    clock.start();
    boss.trackPlayer(&player);
    static bool keyCatch = false;
    bool done = false;
    view.setObjectToTrack(&player);
    
    while ( !done ) {
        ++clock;
        draw();
        checkCollisions();
        update();        
        SDL_Flip(screen);
        SDL_Event event;
        SDL_PollEvent(&event);
        if (event.type ==  SDL_QUIT){ done = true; return; }
        if(event.type == SDL_KEYUP) { keyCatch = false; 
             switch( event.key.keysym.sym ){
                case SDLK_LEFT   : if(player.velocityX() <= 0){ player.stand(); }  break;
                case SDLK_RIGHT  : if(player.velocityX() >= 0){ player.stand(); } break;
                case SDLK_DOWN   : player.stop(); break;
                case SDLK_UP     : player.stopJump(); break;
                case SDLK_SPACE  : player.stop(); break;
                case SDLK_RCTRL  : player.stop(); break;
                case SDLK_RSHIFT : player.stop(); break;
                default : break;
            }
        }
        if(event.type == SDL_KEYDOWN) {
            switch ( event.key.keysym.sym ) {
                case SDLK_ESCAPE: done = true; break;
                //case SDLK_y     : if (!keyCatch) { keyCatch = true; clock.togglePause(); } break;
                case SDLK_p     : if (!keyCatch) { keyCatch = true; clock.togglePause(); menu.toggle(); } break;
                case SDLK_RETURN: if (!keyCatch) { 
                                        keyCatch = true; 
                                        if (menu.isVisible()) {
                                            int selected = menu.getSelection();
                                            if(selected == 0){
                                                clock.togglePause();
                                                menu.toggle();
                                            }
                                        else if(selected == 1) {
                                            player.changeDifficulty();
                                            menu.setDifficulty(player.getDifficulty());
                                        }
                                        else if(selected == 2)
                                            sounds.changeMusic();
                                        else if(selected == 3) 
                                            done = true; 
                                    }
                                  }
                                    break;
                case SDLK_LEFT  : if(!clock.isPaused())player.moveLeft(); break;
                case SDLK_RIGHT : if(!clock.isPaused()) player.moveRight(); break;
                case SDLK_1     : if (!keyCatch) { keyCatch = true; player.changeWeapon(0); hud.updateWeapon(0);} break;
                case SDLK_2     : if (!keyCatch) { keyCatch = true; player.changeWeapon(1); hud.updateWeapon(1);} break;
                case SDLK_3     : if (!keyCatch) { keyCatch = true; player.changeWeapon(2); hud.updateWeapon(2);} break;
                case SDLK_4     : if (!keyCatch) { keyCatch = true; player.changeWeapon(3); hud.updateWeapon(3);} break;
                //case SDLK_d     : if (!keyCatch) { keyCatch = true; player.die(); } break;
                case SDLK_UP    : if(clock.isPaused()){ if (!keyCatch){ keyCatch = true; menu.up(); }} else player.jump(); break;
                case SDLK_DOWN  : if(clock.isPaused()){ if (!keyCatch){ keyCatch = true; menu.down(); }} else player.crouch(); break;
                case SDLK_n     : if (!keyCatch) { keyCatch = true; player.revive(); } break;
                case SDLK_t     : if (!keyCatch) { keyCatch = true; view.setObjectToTrack(&enemy); } break;
                case SDLK_r     : if (!keyCatch) { keyCatch = true; view.setObjectToTrack(&player); } break;
                case SDLK_SPACE : if (!keyCatch) { keyCatch = true; player.throwObject(0); } break;
                case SDLK_RCTRL : if (!keyCatch) { keyCatch = true; player.throwObject(1); } break;
                case SDLK_RSHIFT: if (!keyCatch) { keyCatch = true; player.throwObject(-1); } break;
                case SDLK_TAB   : if (!keyCatch) { keyCatch = true; hud.toggle(); } break;
                case SDLK_s     : if (!keyCatch) { keyCatch = true; clock.toggleSlowMo(); } break;
                default : break;
            }
        }

    }       
}
void Manager::draw(){
    world.drawbackground();
    crows.draw();
    world.drawforeground();
    platform.draw();
    couch.draw();
    surfboard.draw();
    powerup->draw();
    enemy.draw();
    enemy1.draw();
    boss.draw();
    block.draw();
    player.draw();
    hud.draw(player.getData());
    menu.draw();
}
void Manager::update(){
    if(clock.isPaused())
        return;
    player.update();
    powerup->update();
    surfboard.update();
    platform.update();
    couch.update();
    enemy.update();
    enemy1.update();
    boss.update();
    view.update();
    world.update();        
    crows.update();
    block.update();
}
void Manager::checkCollisions(){
// Collisions to change player World height //
    // Collison between player & surfboard //
    if (player.checkRCollision(surfboard) && player.X()+30 > surfboard.X() && player.X()+30 < surfboard.X()+200 && player.velocityY() > 0) {
        if(((surfboard.Y()+46) >= (player.Y()+114)) && player.velocityY() >= 0) {
            if(surfboard.Y() > 200) {
                if(player.X()+55 < surfboard.X()+75)
                    surfboard.react(-300,-50);
                else if(player.X() > surfboard.X()+125)
                    surfboard.react(300,-50);
                else
                    surfboard.react(0,-50);
            }
            else{
                if(player.X()+55 < surfboard.X()+75)
                    surfboard.react(-300,-7);
                else if(player.X() > surfboard.X()+125)
                    surfboard.react(300,-7);
                else
                    surfboard.react(0,-7);
            }
            player.setWorld(surfboard.Y()+46);
        }
    }   
    // Collison between player & platform //
    else if(player.checkRCollision(platform) && player.X()+30 > platform.X() 
        && player.X()+30 < platform.X()+300 && player.velocityY() > 0 
        && platform.Y()+26 > (player.Y()+114)) {
           player.setWorld(platform.Y()+26);
    }
    // Collison between player & couch //
    else if(player.checkRCollision(couch) && player.X()+30 > couch.X() && player.X()+30 < couch.X()+250 && player.velocityY() > 0) {
        if(((couch.Y()+18) > (player.Y()+114)) && player.velocityY() >= 0) 
            player.setWorld(couch.Y()+18);
    }
    // Collison between player & enemy //
    else if(player.velocityY() > 0)
        player.setWorld(480);
    // Collison between player & block //
    if (player.checkCollision(block))  {
                sounds[0];
                powerup->X(block.X());
                powerup->Y(block.Y());
                powerup->velocityY(0);
                block.explode();
                block.move();
                player.adjustScore(5);
    }
      if (powerup->Y() > 200 && player.checkCollision(*powerup))  {
               // sounds[3];
                powerup->X(-100);
                powerup->Y(0);
                player.adjustHealth(10);
    }
    // Collison between player & enemies //
    if (player.velocityY() > 0 && player.checkCollision(enemy)) {
        if(enemy.Y()+20> player.Y()+114) {
            sounds[0];
            enemy.explodeEnemy();
            player.adjustScore(100);
            player.setWorld(enemy.Y()+4);
            player.react(player.velocityX(),0);
	        player.stopJump();
	    }
	    else {
	         if(enemy.X() > player.X())
                player.react(-299,0);
            else
                player.react(299,0);
            sounds[2];
                player.adjustScore(-5);
            player.adjustHealth(-1);
        }
    }
    if (player.velocityY() > 0 && player.checkCollision(enemy1)) {
        if(enemy1.Y()+55 > player.Y()+110) {
            sounds[0];
            enemy1.explodeEnemy();
            player.adjustScore(100);
            player.setWorld(player.Y()+114);
            player.react(player.velocityX(),0);
	        player.stopJump();
            
	    }
	    else {
	        if(enemy1.X() > player.X())
                player.react(-299,0);
            else
                player.react(299,0);
            sounds[2];
            player.adjustScore(-5);
            player.adjustHealth(-1);
        }
    }
    if (player.checkCollision(boss)) {
        if(boss.X() > player.X())
            player.react(-299,0);
        else
            player.react(299,0);
        sounds[2];
        player.adjustScore(-5);
        player.adjustHealth(-1);
    }
    // Collison between player & enemy weapons//
    if (player.checkCollision(enemy.getWeapon())) {
        if(enemy.getWeapon().X() > player.X())
            player.react(-201,0);
        else 
            player.react(201,0);
                sounds[0];
        enemy.explodeWeapon();
        player.adjustScore(-5);
        player.adjustHealth(-5);
    }
    if (player.checkCollision(enemy1.getWeapon())) {
        if(enemy1.getWeapon().X() > player.X())
            player.react(-201,0);
        else 
            player.react(201,0);
                sounds[0];
        enemy1.explodeWeapon();
        player.adjustScore(-5);
        player.adjustHealth(-5);
    }
    if (player.checkCollision(boss.getWeapon())) {
        if(boss.getWeapon().X() > player.X())
            player.react(-201,0);
        else 
            player.react(201,0);
                sounds[0];
        boss.explodeWeapon();
        player.adjustScore(-5);
        player.adjustHealth(-10);
    }
    // Collison between playerweapons //
    for(int i = 0; i < 10; i++){
        if (collisionStrategy->execute(*player.getWeapons()[i],enemy.getWeapon()))  {
                sounds[0];
            enemy.explodeWeapon();
            player.explodeWeapon(i);
        }
        if (collisionStrategy->execute(*player.getWeapons()[i],enemy1.getWeapon()))  {
                sounds[0];
            enemy1.explodeWeapon();
            player.explodeWeapon(i);
        }
        if (collisionStrategy->execute(*player.getWeapons()[i],boss.getWeapon()))  {
                sounds[0];
            boss.explodeWeapon();
            player.explodeWeapon(i);
        }
        if (collisionStrategy->execute(*player.getWeapons()[i],enemy)) {
                sounds[0];
            enemy.adjustHealth(-10);
            player.explodeWeapon(i);
            player.adjustScore(5);
        }
        if (collisionStrategy->execute(*player.getWeapons()[i],enemy1)) {
                sounds[0];
            enemy1.adjustHealth(-20);
            player.explodeWeapon(i);
            player.adjustScore(2);
        }
        if (collisionStrategy->execute(*player.getWeapons()[i],boss)) {
                sounds[0];
            boss.adjustHealth(-4);
            player.explodeWeapon(i);
            player.adjustScore(2);
        }
        if (collisionStrategy->execute(*player.getWeapons()[i],block)) {
                sounds[0];
                powerup->X(block.X());
                powerup->Y(block.Y());
                powerup->velocityY(0);
                player.explodeWeapon(i);
                block.explode();
                block.move();
                player.adjustScore(5);
                player.adjustHealth(10);
        }
        if (collisionStrategy->execute(*player.getWeapons()[i],couch)) {
                sounds[0];
                player.explodeWeapon(i);
            if(player.getWeapons()[i]->velocityX() > 0)
                couch.react(100,0);
            else 
                couch.react(-100,0);
        }
    }
}
