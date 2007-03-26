#include "animating_sprite.hpp"
#include "image.hpp"
#include "image_file_manager.hpp"
#include "priority.hpp"
#include "assert.hpp"
#include "graphics.hpp"
#include "animation.hpp"
#include "rectangle.hpp"

#include <iostream>

AnimatingSprite::AnimatingSprite(const AnimatingSprite &s)
	: m_animation( new Animation(*s.m_animation) ),
	  m_priority(s.m_priority), m_position(s.m_position)
{
	REQUIRE(s.m_animation != NULL);
	// should call animation isvalid method or something, but that
	// doesn't exist yet
	ENSURE(m_animation != NULL);
}

AnimatingSprite::AnimatingSprite(const Animation *animation,
	       Priority priority,
	       Pair position)
	: m_animation( new Animation(*animation) ),
	  m_priority(priority), m_position(position)
{
	REQUIRE(animation != NULL);
	ENSURE(m_animation != NULL);
}

AnimatingSprite& AnimatingSprite::operator=(const AnimatingSprite &s)
{
	REQUIRE(s.m_animation != NULL);
	m_position = s.m_position;
	m_priority = s.m_priority;
	m_animation = new Animation(*s.m_animation);
	ENSURE(m_animation != NULL);
	return *this;
}

AnimatingSprite::~AnimatingSprite()
{
	REQUIRE(m_animation != NULL);
	delete &m_priority;
	delete &m_position;
	delete m_animation;
}

void AnimatingSprite::move(Pair distance)
{
	m_position += distance;
}

Pair AnimatingSprite::getPosition( void )
{
	return m_position;
}

SDL_Surface *AnimatingSprite::getSurface( void )
{
	return m_animation->getSurface();
}


Rectangle AnimatingSprite::getRegion( void )
{
	return (m_animation->getRectangle() -
		m_animation->getRectangle().getRef() +
		m_position);
}
Pair AnimatingSprite::getOffset( void )
{
	return m_animation->getRectangle().getRef() - m_position;
}

bool AnimatingSprite::next( void )
{
	return m_animation->next();
}

void AnimatingSprite::writeTo(SDL_Surface *surface)
{
	REQUIRE(m_animation != NULL);
	REQUIRE(m_animation->getSurface() != NULL);
	REQUIRE(surface != NULL);
	// TODO: Warn if not of same format.  It's probably still
	// valid and possibly useful, but is usually unexpected.

	// TODO: Should handle reference point somewhere else

	SDL_BlitSurface(m_animation->getSurface(),
			&Graphics::toSDL_Rect(  m_animation->getRectangle()),
//			&Graphics::toSDL_Rect(  Rectangle(Pair(1,1), Pair(1,1))),
			surface,
			&Graphics::toSDL_Rect(  m_animation->getRectangle() - m_animation->getRectangle().getRef() + m_position )
//			&Graphics::toSDL_Rect(  Rectangle(Pair(1,1), Pair(1,1)) )			
		);

}

