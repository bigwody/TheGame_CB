#ifndef ABSTRACTFACTORY__H
#define ABSTRACTFACTORY__H

#include <string>
using std::string;
#include <map>
#include "frame.h"
#include "gamedata.h"

class AbstractFactory {
public:
  AbstractFactory() {}
  virtual ~AbstractFactory() {}
  virtual Frame* getFrame( const string& name ) = 0;
private:
  static AbstractFactory* instance;
  AbstractFactory(const AbstractFactory&);
  AbstractFactory& operator=(const AbstractFactory&);
};
#endif
