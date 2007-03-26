#include "image.hpp"
#include "graphics.hpp"
#include "image_file_manager.hpp"
#include "image_file.hpp"
#include "assert.hpp"
#include <SDL/SDL.h>

ImageFileManager* Image::m_manager = NULL;

Image::Image(const Image &image)
	: m_imageFile( m_manager->assoc( image.getName() ) ),
	  m_rect( Rectangle(image.m_rect) )
{

}

Image::Image(const std::string &name, Rectangle rect)
	: m_imageFile( m_manager->assoc(name) ),
	  m_rect( rect )
{

}

// This should never be used
Image& Image::operator=(const Image &image)
{
//	m_manager->dissoc( image.getName() );
//	m_imageFile = m_manager->assoc( image.getName() );p
//	m_rect = image.m_rect;

	ASSERT(false);
	
	return *this;
}
//

Image::~Image()
{
	m_manager->dissoc( getName() );
}

Rectangle Image::getRectangle() const
{
	return m_rect;
}

SDL_Surface* Image::getSurface() const
{
	// might as well check here just in case forget elsewhere
	REQUIRE(m_imageFile.getSurface() != NULL);
	return m_imageFile.getSurface();
}

const std::string& Image::getName() const
{
	return m_imageFile.getName();
}
