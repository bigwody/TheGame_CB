#ifndef SPRITEFACTORY__H
#define SPRITEFACTORY__H
#include "abstractfactory.h"

class SpriteFactory : public AbstractFactory {
public:
  static SpriteFactory& getInstance();
  virtual ~SpriteFactory();

  Frame* getFrame(const string & name);
private:
  const Gamedata& gdata;
  std::map<string, Frame*> frames;
  SpriteFactory();
  SpriteFactory(const SpriteFactory &);
  SpriteFactory& operator=(const SpriteFactory &);
};
#endif
