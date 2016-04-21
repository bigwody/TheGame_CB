#include "animationfactory.h"

AnimationFactory& AnimationFactory::getInstance() {
    static AnimationFactory factory;
    return factory;
}

AnimationFactory::~AnimationFactory() { 
  std::map<string, Frame*>::iterator pos = multiFrames.begin(); 
  while ( pos != multiFrames.end() ) {
    SDL_Surface* surface = pos->second->getSurface();
    SDL_FreeSurface(surface);

    const string name = pos->first;
    unsigned numberOfFrames = gdata.getXmlInt(name+"FrameCount");
    Frame *frames = pos->second;
    for (unsigned i = 0; i < numberOfFrames; ++i) {
      frames[i].~Frame();
    }
    operator delete[](frames);
    ++pos;
  }
  multiFrames.clear();
}

AnimationFactory::AnimationFactory() : 
  gdata( Gamedata::getInstance() ),
  multiFrames( std::map<string, Frame*>() ) 
{}

Frame* AnimationFactory::getFrame( const string& name ) {
  std::map<string, Frame*>::iterator pos = multiFrames.find(name); 
  if ( pos == multiFrames.end() ) {
    const string filename = gdata.getXmlStr(name+"File");
    bool colorKey = gdata.getXmlBool(name+"Transparency");
    SDL_Surface* surface = IOManager::
      getInstance().loadAndSet(filename, colorKey);
  
    unsigned numberOfFrames = gdata.getXmlInt(name+"FrameCount");
    Uint16 pwidth = gdata.getXmlInt(name+"Width") / numberOfFrames;
    Uint16 pheight = gdata.getXmlInt(name+"Height");
    Uint16 srcX = gdata.getXmlInt(name+"SrcX");
    Uint16 srcY = gdata.getXmlInt(name+"SrcY");
    
    void *rawMemory = operator new[](numberOfFrames*sizeof(Frame));
    Frame* frames = static_cast<Frame*>(rawMemory);

    for (unsigned i = 0; i < numberOfFrames; ++i) {
      unsigned frameX = i * pwidth + i + srcX;
      new (&frames[i]) Frame( surface, pwidth, pheight, frameX, srcY);
    }
    multiFrames[name] = frames;
    return frames;
  }
  else return pos->second;
}

