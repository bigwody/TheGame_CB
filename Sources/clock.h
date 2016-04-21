#include <SDL.h>
#include <string>
#include <iostream>
#include <fstream>
#include "sound.h"

class Clock {
public:
  static Clock& getInstance();
  unsigned getTicks() const;
  unsigned getTotalTicks() const;
  Clock(const Clock&);
  Clock&operator=(const Clock&);
  Clock& operator++();
  Clock  operator++(int);
  bool isStarted() const { return started; }
  bool isPaused() const  { return paused;  }
  unsigned getFrames() const  { return frames;  }
  unsigned getSeconds() const { return getTotalTicks()/1000;  }
  float getFps();
  unsigned getElapsedTicks();
  void resetFps() { frames = 0; timeAtStart = 0; }

  void start();
  void pause();
  void togglePause();  
  void toggleSlowMo();
  void unpause();
  void debug();
private:
  //void save(std::fstream& xmlfile) const;
  //void restore(const std::string& filename);
  SDLSound &sounds;
  bool started;
  bool paused;
  bool slowmo;
  unsigned frames;
  unsigned timeAtStart;
  unsigned timeAtPause;
  unsigned currTicks;
  unsigned prevTicks;
  unsigned ticks;

  Clock();
};
