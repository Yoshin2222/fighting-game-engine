#ifndef SPRITE_H
#define SPRITE_H

#include "unit.hpp"
#include "priority.hpp"
#include "pair.hpp"
#include "rectangle.hpp"
#include <string> // may be able to get rid of this

class Image;
struct SDL_Surface;

// TODO: Add functions to modify priority
class Sprite
{
	friend class Graphics;
	friend class SpriteCompare;
  public:
	Sprite(const Sprite &s);
	explicit Sprite(const Image *image,
	       Priority priority = Priority(),
	       Pair position = Pair()
		);
	explicit Sprite(const std::string &name = "../resources/default.bmp",
	       Rectangle *rect = new Rectangle(),
	       Priority priority = Priority(),
	       Pair position = Pair()
		);
	Sprite& operator=(const Sprite &s);
	~Sprite();

	void move(Pair distance);
	Pair getPosition( void );

	// Blits to specified surface
	void writeTo(SDL_Surface *surface);
  private:
	Image *m_image;
	Priority m_priority;
	Pair m_position;
};

// Higher priority first, opposite of default sort of
class SpriteCompare {
  public:
	bool operator () (Sprite *arg1, Sprite *arg2) {
		return arg1->m_priority > arg2->m_priority;
	}
};

#endif // SPRITE_H
