#include "spritefactory.h"
#include "ioManager.h"

SpriteFactory& SpriteFactory::getInstance() {
    static SpriteFactory factory;
    return factory;
}

SpriteFactory::~SpriteFactory() { 
  std::map<string, Frame*>::iterator pos = frames.begin(); 
  while ( pos != frames.end() ) {
    SDL_Surface* surface = pos->second->getSurface();
    SDL_FreeSurface(surface);
    delete pos->second;
    ++pos;
  }
  frames.clear();
}

SpriteFactory::SpriteFactory() : 
  gdata( Gamedata::getInstance() ),
  frames( std::map<string, Frame*>() ) 
{}

Frame* SpriteFactory::getFrame( const string& name ) {
  // Frames are stored by filename, which is unique
  std::map<string, Frame*>::iterator pos = frames.find(name); 
  if ( pos == frames.end() ) {
    const string filename = gdata.getXmlStr(name+"File");
    bool colorKey = gdata.getXmlBool(name+"Transparency");
    SDL_Surface* surface = IOManager::
      getInstance().loadAndSet(filename, colorKey);
  Frame* frame =
    new Frame(surface, 
      gdata.getXmlInt(name+"Width"), gdata.getXmlInt(name+"Height"),
      gdata.getXmlInt(name+"SrcX"), gdata.getXmlInt(name+"SrcY")); 
      frames[name] = frame;
      return frame;
  }
  else return pos->second;
}

