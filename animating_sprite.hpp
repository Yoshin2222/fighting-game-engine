#ifndef ANIMATING_SPRITE_H
#define ANIMATING_SPRITE_H

#include "priority.hpp"
#include "pair.hpp"

class Animation;
struct SDL_Surface;
class Rectangle;


// TODO: Fully replace Sprite
// TODO: Add functions to modify priority
class AnimatingSprite
{
	friend class Graphics;
	friend class AnimatingSpriteCompare;
	friend class DisplayLine;
  public:
	AnimatingSprite(const AnimatingSprite &s);
	explicit AnimatingSprite(const Animation *animation,
	       Priority priority = Priority(),
	       Pair position = Pair()
		);
	AnimatingSprite& operator=(const AnimatingSprite &s);
	~AnimatingSprite();

	void move(Pair distance);
	Pair getPosition( void );

	SDL_Surface *getSurface( void );
	
	// Gives region to blit to
	Rectangle getRegion( void );
	// Gives region to blit from as offset
	Pair getOffset( void );
	
	bool next( void );

	// Blits to specified surface
	void writeTo(SDL_Surface *surface);
//	void writeTo(SDL_Surface *surface, Rectangle region);
  private:
	Animation *m_animation;
	Priority m_priority;
	Pair m_position;
};

// Higher priority first, opposite of default sort of
class AnimatingSpriteCompare {
  public:
	bool operator () (AnimatingSprite *arg1, AnimatingSprite *arg2) {
		return arg1->m_priority > arg2->m_priority;
	}
};

#endif // ANIMATING_SPRITE_H
