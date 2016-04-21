#ifndef MENU__H
#define MENU__H
#include "gamedata.h"
#include "ioManager.h"
#include "aaline.h"

class Menu {
public:
    Menu(SDL_Surface* s) :
        gdata(Gamedata::getInstance()),
        io(IOManager::getInstance()),
        sounds(SDLSound::getInstance()),
        frame(SpriteFactory::getInstance().getFrame("Menu")),
        frame1(SpriteFactory::getInstance().getFrame("MenuBackground")),
        screen(s),
        black(SDL_MapRGB(screen->format, 0x00, 0x99, 0x10)),
        Menuenabled(true),
        loc(75),
        selected(0),
        difficulty("easy")
    { 
        frame1->setAlpha(200);
    }
    virtual ~Menu(){};
    bool isVisible(){ return Menuenabled; }
    int getSelection(){ return selected; }
    void setDifficulty(string diff){ difficulty = diff; }
    void up() { if(loc > 100) { selected-= 1; loc-= 88; } else { loc += 264; selected+=3; }}
    void down() { if(loc < 300){ selected+=1; loc+=88; } else { loc -= 264; selected-=3; }}
    void draw() { if(Menuenabled){ 
        frame1->draw(0,0,0,0);
        frame->draw(0,0,0,0); 
        Draw_AALine(screen, 74, loc, 563, loc, 10.0f, black);
        Draw_AALine(screen, 78, loc-4, 78, loc+80, 10.0f, black);
        Draw_AALine(screen, 559, loc-4, 559, loc+80, 10.0f, black);
        Draw_AALine(screen, 74, loc+76, 563, loc+76, 10.0f, black);
        io.printMessageAt(sounds.getMusic(), 350, 287);
        io.printMessageAt(difficulty, 390, 199);
    }}
    void toggle() { if(Menuenabled) Menuenabled = false; else Menuenabled = true; }
private:
    Gamedata& gdata;    
    IOManager& io;
    SDLSound &sounds;
    const Frame * frame;
    const Frame * frame1;
    SDL_Surface* screen;
    Uint32 black;
    bool Menuenabled;
    int loc;
    int selected;
    string difficulty;
    Menu(const Menu&);
    Menu& operator=(const Menu&);
};
#endif
