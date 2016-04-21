#include <iostream>
#include <map>
#include <sstream>
#include "clock.h"
using std::cout; using std::endl;

Clock& Clock::getInstance() {
  static Clock clock; 
  return clock;
}

Clock::Clock() :
  sounds( SDLSound::getInstance() ),
  started(false), 
  paused(true), 
  slowmo(false), 
  frames(0), 
  timeAtStart(0), timeAtPause(0),
  currTicks(0), prevTicks(0), ticks(0)
  {
  start();
}

Clock::Clock(const Clock& c) :
  sounds(c.sounds),
  started(c.started), 
  paused(c.paused), slowmo(c.slowmo), frames(c.frames), 
  timeAtStart(c.timeAtStart), timeAtPause(c.timeAtPause),
  currTicks(c.currTicks), prevTicks(c.prevTicks), ticks(c.ticks)
  {
  start();
}

void Clock::debug( ) { 
  cout << "The clock is:" << endl;
  cout << "\tstarted:" << started << endl;
  cout << "\tpaused:" << paused << endl;
  cout << "\tframes:" << frames << endl;
  cout << "\ttimeAtStart:" << timeAtStart << endl;
  cout << "\ttimeAtPause:" << timeAtPause << endl;
  cout << "\tcurrTicks:" << currTicks << endl;
  cout << "\tprevTicks:" << prevTicks << endl;
  cout << "\tticks:" << ticks << endl;
  cout << endl;
}

unsigned Clock::getTicks() const { 
if (paused) return 0;
if (slowmo) return 1;
  return(ticks);
}

unsigned Clock::getTotalTicks() const { 
  if (paused) return timeAtPause;
  else return SDL_GetTicks() - timeAtStart; 
}

unsigned Clock::getElapsedTicks() { 
  if (paused) return 0;
  currTicks = getTotalTicks();
  ticks = currTicks-prevTicks;
  prevTicks = currTicks;
  return ticks;
}

float Clock::getFps(){ 
  static unsigned seconds = getSeconds();
  static float fps = 0;
  if ( getSeconds() > 0 && getSeconds() > seconds) {
    seconds = getSeconds();
    fps = frames/seconds;
    return frames/getSeconds();  
  }
  else if ( getSeconds() > 0 ) return fps;
  else {
    fps = 0;
    return 0;
  }
}

Clock& Clock::operator++() { 
  getElapsedTicks();
  if ( !paused ) ++frames; 
  return *this;
}
Clock  Clock::operator++(int) { 
  getElapsedTicks();
  if ( !paused ) frames++; 
  return *this;
}
void Clock::toggleSlowMo() {
    if(slowmo) {
        slowmo = false;
    }
    else {
        slowmo = true;
    }
}
void Clock::togglePause() {
    if(paused) {
        unpause();
        sounds.startMusic();
    }
    else {
        pause();
        sounds.menuMusic();
    }
}
void Clock::start() { 
  started = true; 
  paused = true; 
  frames = 0;
  timeAtPause = timeAtStart = SDL_GetTicks(); 
}
void Clock::pause() {
  if( started && !paused ) {
    timeAtPause = SDL_GetTicks() - timeAtStart;
    paused = true;
  }
}
void Clock::unpause() {
  if( started && paused ) {
    timeAtStart = SDL_GetTicks() - timeAtPause;
    paused = false;
  }
}

