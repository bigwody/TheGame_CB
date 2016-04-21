#include  <iostream>
#include  <string>
using std::string;
#include  <vector>
using std::vector;
#include <stdlib.h>
#include <SDL.h>
#include <SDL_mixer.h>

// In this demo, we use Mix_Music *Mix_LoadMUS(const char *file)
// Where file is the name of the music file to use. 
//
// SDL_mixer supports music and sound samples from the following formats:
// - WAVE/RIFF (.wav)
// - AIFF (.aiff)
// - VOC (.voc)
// - MOD (.mod .xm .s3m .669 .it .med and more) using included mikmod
// - MIDI (.mid) using timidity or native midi hardware
// - OggVorbis (.ogg) requiring ogg/vorbis libraries on system
// - MP3 (.mp3) requiring SMPEG library on system
// - also any command-line player, which is not mixed by SDL_mixer...
//   that requires a command to play with.

class SDLSound {
public:
  ~SDLSound();
  static SDLSound& getInstance();
  void startMusic();
  void menuMusic();
 // void stopMusic();      // stop all sounds
  void changeMusic();      // change music
  void toggleMusic();    // stop all sounds
  void operator[](int);  // play the indexed sound
  string getMusic(){ return titles[currentMusic]; }
private:
  int volume;
  int currentSound;
  int currentMusic;
  Mix_Music *mmusic;
  

  int audioRate;
  int audioChannels;
  int audioBuffers;
  std::vector<Mix_Chunk*> sounds;
  std::vector<Mix_Music*> music;
  std::vector<string> titles;
  std::vector<int> channels;
  SDLSound();
  SDLSound(const SDLSound&);
  SDLSound& operator=(const SDLSound&);
};

