#include "image_file.hpp"
#include "image_file_manager.hpp"
#include "graphics.hpp"
#include "assert.hpp"
#include <SDL/SDL.h>
#include <string>

ImageFileManager* ImageFile::m_manager = NULL;

ImageFile::ImageFile(std::string fileName, Extension ext)
	: m_refCount(0), m_fileName(fileName), m_surface(NULL), m_ext(ext)
{
	// Might not do this here later
	load();

	// Might not do this here later
	convert();
	
	// Maybe change this to handle it in another way later.  
	// For example, loading an obviously incorrect image
	ENSURE(m_surface != NULL);
}

// Actually, this should never be used
ImageFile::ImageFile(const ImageFile &imgFile)
	: m_refCount(imgFile.m_refCount), m_fileName(imgFile.m_fileName),
	  m_ext(imgFile.m_ext)
{
	m_surface = Graphics::newSDL_Surface(imgFile.m_surface);
	
	ENSURE( false ); // this constructor should never be used
}

// Actually, this should never be used
ImageFile& ImageFile::operator=(const ImageFile &imgFile)
{
	m_refCount = imgFile.m_refCount;
	m_fileName = imgFile.m_fileName;
	m_ext = imgFile.m_ext;
	m_surface = Graphics::newSDL_Surface(imgFile.m_surface);
	
	ENSURE ( false ); // this constructor should never be used

	return *this;
}

ImageFile::~ImageFile()
{
	if (m_surface != NULL)
		SDL_FreeSurface( m_surface );
}

void ImageFile::incRef( void )
{
	if ( (m_refCount++ == 0) && (m_surface == NULL) )
	{
		// Might not do this here later
		load();
		convert();
	}

	// This will assert on overflow
	ENSURE(m_refCount > 0);

	return;
}

void ImageFile::decRef( void )
{
	REQUIRE( m_refCount > 0 );
	
	m_refCount--;
	if (m_refCount == 0)
	{
		// Optionally free surface
		SDL_FreeSurface( m_surface );
		m_surface = NULL;
	}

	// asserts on overflow, update if using smaller data type
	ENSURE( m_refCount < (1 << 30) );

	return;
}


void ImageFile::load()
{
	// Free memory
	if (m_surface != NULL)
		SDL_FreeSurface(m_surface);
	
	switch (m_ext)
	{
	case (EXT_BMP):
		m_surface = SDL_LoadBMP( m_fileName.c_str() );
		break;
	default:
		
		break;
	}
	
	ENSURE(m_surface != NULL);
	// TODO: Do something if unable to load image, probably load a
	// default image
}

void ImageFile::convert()
{
	REQUIRE(m_surface != NULL);

	SDL_Surface *tmp;
		
	tmp = SDL_ConvertSurface(m_surface, m_manager->getFormat(),
			   SDL_HWSURFACE | SDL_SRCCOLORKEY
		);

	// Free memory
	SDL_FreeSurface(m_surface);
	m_surface = tmp;
	
	// TODO: Support different transparency systems?

	// Defaults to Green and RLEACCEL
	SDL_SetColorKey(
		m_surface
		, SDL_SRCCOLORKEY | SDL_RLEACCEL
		, SDL_MapRGB(m_surface->format, 0, 0xff, 0)
			);

	// TODO: Check if this can be combined with first ConvertSurface
	tmp = SDL_DisplayFormat(m_surface);

	SDL_FreeSurface(m_surface);
	m_surface = tmp;

	ENSURE(m_surface != NULL);
}

SDL_Surface* ImageFile::getSurface() const
{
	REQUIRE(m_surface != NULL);
	return m_surface;
}

const std::string& ImageFile::getName() const
{
	return m_fileName;
}
