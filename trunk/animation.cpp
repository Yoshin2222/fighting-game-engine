#include "animation.hpp"
#include "assert.hpp"
#include "image.hpp"
#include "image_manager.hpp"

//#include "image.hpp"
// Actually doesn't need to know anything about Image except that it
// exists...err no longer, since adding getRectangle and getSurface

ImageManager* Animation::m_manager = NULL;

Animation::Animation(Image** images, unsigned int count,
		     bool loop, unsigned int current)
	: m_images(new Image*[count]), m_count(count),
	  m_current(current), m_loop(loop)
{
	REQUIRE(count > 0);
	REQUIRE(current < count);
	for(unsigned int i = 0; i < count; ++i)
	{
		m_images[i] = images[i];
		REQUIRE(images[i] != NULL);
		m_manager->assoc(images[i]);
	}
	
}

Animation::Animation(Image* image)
	: m_images(new Image*[1]), m_count(1),
	  m_current(0), m_loop(true)
{
	m_images[0] = image;
	REQUIRE(m_images[0] != NULL);
	m_manager->assoc(m_images[0]);
}

Animation::Animation(const Animation &anim)
	: m_images(new Image*[anim.m_count]), m_count(anim.m_count),
	  m_current(anim.m_current), m_loop(anim.m_loop)
{
	REQUIRE(m_current < m_count);
	for(unsigned int i = 0; i < m_count; ++i)
	{
		m_images[i] = anim.m_images[i];
		REQUIRE(m_images[i] != NULL);
		m_manager->assoc(m_images[i]);
	}
}

Animation& Animation::operator=(const Animation &anim)
{
	m_images = new Image*[m_count];
	m_count = anim.m_count;
	m_current = anim.m_current;
	m_loop = anim.m_loop;

	REQUIRE(m_count > 0);
	REQUIRE(m_current < m_count);
	for(unsigned int i = 0; i <= m_count; ++i)
	{
		m_images[i] = anim.m_images[i];
		m_manager->assoc(m_images[i]);
		REQUIRE(m_images[i] != NULL);
	}
	
	return *this;
}

Animation::~Animation()
{
	for(unsigned int i = 0; i < m_count; ++i)
	{
		delete m_images;
		m_manager->dissoc(m_images[i]);
	}
}

Rectangle Animation::getRectangle( void ) const
{
	ENSURE(m_images[m_current] != NULL);
	return m_images[m_current]->getRectangle();
}

SDL_Surface* Animation::getSurface( void ) const
{
	REQUIRE(m_current < m_count);
	ENSURE(m_images[m_current] != NULL);
	ENSURE(m_images[m_current]->getSurface() != NULL);
	return m_images[m_current]->getSurface();
}

bool Animation::next()
{
	if (++m_current < m_count)
	{
		// Do nothing, continuing as normal
	} else { // now m_current == m_count, so make it valid again
		if (m_loop == true)
		{
			m_current = 0;
		} else {
			m_current--;
			ASSERT(m_count - 1 == m_current);
			return false; // no more frames
		}
	}
	
	return true;
}
