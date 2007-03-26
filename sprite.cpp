#include "sprite.hpp"
#include "image.hpp"
#include "image_file_manager.hpp"
#include "priority.hpp"
#include "assert.hpp"
#include "graphics.hpp"
//#include <iostream>


Sprite::Sprite(const Sprite &s)
	: m_image( new Image(*s.m_image) ),
	  m_priority(s.m_priority), m_position(s.m_position)
{
	REQUIRE(s.m_image != NULL);
	ENSURE(m_image != NULL);
}

Sprite::Sprite(const Image *image,
	       Priority priority,
	       Pair position)
	: m_image( new Image(*image) ),
	  m_priority(priority), m_position(position)
{
	REQUIRE(image != NULL);
	ENSURE(m_image != NULL);
}

Sprite::Sprite(
	const std::string &name,
	Rectangle *rect,
	Priority priority,
	Pair position
	)
	: 	  m_image( new Image(name, *rect) ),
		  m_priority(priority), m_position(position)
{
	REQUIRE(rect != NULL);
	ENSURE(m_image != NULL);
}

Sprite& Sprite::operator=(const Sprite &s)
{
	REQUIRE(s.m_image != NULL);
	m_position = s.m_position;
	m_priority = s.m_priority;
	m_image = new Image(*s.m_image);
	ENSURE(m_image != NULL);
	return *this;
}

Sprite::~Sprite()
{
	delete &m_priority;
	delete &m_position;
	delete m_image;
}

void Sprite::move(Pair distance)
{
	m_position += distance;
}

Pair Sprite::getPosition( void )
{
	return m_position;
}


void Sprite::writeTo(SDL_Surface *surface)
{
	REQUIRE(m_image->getSurface() != NULL);
	REQUIRE(surface != NULL);
	// TODO: Warn if not of same format.  It's probably still
	// valid and possibly useful, but is usually unexpected.
	
	SDL_BlitSurface(m_image->getSurface(),
			&Graphics::toSDL_Rect( m_image->getRectangle() ),
			surface,
			&Graphics::toSDL_Rect(  m_image->getRectangle() - m_image->getRectangle().getRef() + m_position )
		);
}
