#include <vector>
#include <iostream>
using std::vector;

#include "explosion.h"

class ExplodingSprite : public Sprite {
public:
  ExplodingSprite(const Sprite&);
  ~ExplodingSprite();
  virtual void draw() const;
  virtual void update();
  Frame* makeChunkFrames();
  void clearChunks(){chunks.clear();}
  void makeChunks();
  unsigned int chunkCount() const { return chunks.size(); }
  unsigned int freeCount()  const { return freeList.size(); }
private:
  SDL_Surface *screen;
  const Frame *frame;
  SDL_Surface *spriteSurface;
  std::vector<Explosion> chunks;
  std::vector<Explosion> freeList;
  unsigned totalChunks;
  Vector2f getNewVelocity() const;
  ExplodingSprite(const ExplodingSprite&);
  ExplodingSprite& operator=(const ExplodingSprite&);
};
