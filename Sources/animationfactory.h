#ifndef ANIMATIONFACTORY__H
#define ANIMATIONFACTORY__H
#include "abstractfactory.h"

class AnimationFactory : public AbstractFactory {
public:
  static AnimationFactory& getInstance();
  virtual ~AnimationFactory();

  Frame* getFrame( const string& name );
private:
  const Gamedata& gdata;
  std::map<string, Frame*> multiFrames;
  AnimationFactory();
  AnimationFactory(const AnimationFactory &);
  AnimationFactory& operator=(const AnimationFactory &);
};
#endif
