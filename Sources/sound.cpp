#include <ctime>
#include "sound.h"
using std::string;

SDLSound& SDLSound::getInstance() {
  static SDLSound sounds; 
  return sounds;
}

SDLSound::~SDLSound() {
  Mix_HaltMusic();
  Mix_FreeMusic(mmusic);
  for (unsigned int i = 0; i < sounds.size(); ++i) {
    Mix_FreeChunk(sounds[i]);
  }
  for (unsigned int i = 0; i < music.size(); ++i) {
    Mix_FreeMusic(music[i]);
  }
  Mix_CloseAudio();
}

SDLSound::SDLSound() : 
  volume(SDL_MIX_MAXVOLUME/4), 
  currentSound(-1),
  currentMusic(0), 
  mmusic(NULL),
  audioRate(22050), 
  audioChannels(2), 
  audioBuffers(4096),
  sounds(),
  music(),
  titles(),
  channels() 
{
  if(Mix_OpenAudio(audioRate, MIX_DEFAULT_FORMAT, audioChannels, 
                   audioBuffers)){
    throw string("Unable to open audio!");
  }
  mmusic = Mix_LoadMUS("sounds/menu.wav");
  music.push_back( Mix_LoadMUS("sounds/background.wav"));
  music.push_back( Mix_LoadMUS("sounds/menu.wav"));
  //music.push_back( Mix_LoadMUS("sounds/bmjr.wav"));
  //music.push_back( Mix_LoadMUS("sounds/bringitback.wav"));
  //music.push_back( Mix_LoadMUS("sounds/bluntblowin.wav"));
  titles.push_back("song 1");
  titles.push_back("song 2");
  //titles.push_back("song 3");
  //titles.push_back("song 4");
  // Need to install midi to play the following:
  //music = Mix_LoadMUS("sounds/ballad2.mid");
  //if (!bmusic) throw string("Couldn't load 100Years.mp3")+Mix_GetError();

  //sounds.push_back( Mix_LoadWAV("sounds/Boom.wav") );
  //sounds.push_back( Mix_LoadWAV("sounds/Gun.wav") );
  //sounds.push_back( Mix_LoadWAV("sounds/Thump.wav") );

  sounds.push_back( Mix_LoadWAV("sounds/blockbreak.wav") );
  sounds.push_back( Mix_LoadWAV("sounds/jump.wav") );
  sounds.push_back( Mix_LoadWAV("sounds/enemy_collision.wav") );
  sounds.push_back( Mix_LoadWAV("sounds/throw.wav") );
  sounds.push_back( Mix_LoadWAV("sounds/impact.wav") );
  sounds.push_back( Mix_LoadWAV("sounds/playerdeath1.wav") );
  sounds.push_back( Mix_LoadWAV("sounds/beatgame.wav") );
  for (unsigned int i = 0; i < sounds.size(); ++i) channels.push_back(i);
  menuMusic();
}

void SDLSound::toggleMusic() {
  if( Mix_PausedMusic() ) { 
    Mix_ResumeMusic(); 
  } 
  else { 
    Mix_PauseMusic(); 
    menuMusic();
  } 
}

void SDLSound::operator[](int index) {
  //if (currentSound >= 0) Mix_HaltChannel(currentSound);
  currentSound = index;
  if(index >= 3)
  Mix_VolumeChunk(sounds[index], volume*3);
  else
  Mix_VolumeChunk(sounds[index], volume/3);
  
  channels[index] = Mix_PlayChannel(-1, sounds[index], 0);
}
void SDLSound::changeMusic() {
  currentMusic++;
  currentMusic%=music.size();
}
void SDLSound::startMusic() {
  if(currentMusic==0)
    Mix_VolumeMusic(volume);
  else  
    Mix_VolumeMusic(volume/2);
  Mix_PlayMusic(music[currentMusic], -1);
}
void SDLSound::menuMusic() {
  Mix_VolumeMusic(volume*2);
  Mix_PlayMusic(mmusic, -1);
}

/*void SDLSound::stopMusic() {
  Mix_HaltMusic();
  Mix_FreeMusic(bmusic);
}*/

