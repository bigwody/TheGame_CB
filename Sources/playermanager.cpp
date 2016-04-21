#include "playermanager.h"

PlayerManager::PlayerManager(const string& n) :
    //score(0),
    //health(100),
    player(n)
    //throwable(new PlayerWeapon("weapon0"))
{}
/*void PlayerManager::changeWeapon(int weapon) {
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
}*/
void PlayerManager::update() {
    player.update(); 
}
/*void PlayerManager::throwObject(int dir) {
    if(player.isAlive()) {
        player.throwObject();
        int direction = player.getDir();
        throwable->loadNext(X()+(direction*28),Y()+50,((direction*2)-1)*400,(dir*400)+10);
    }
}*/
