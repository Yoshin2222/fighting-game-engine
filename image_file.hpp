#ifndef IMAGE_FILE_H
#define IMAGE_FILE_H

#include "extension.hpp"
#include <string> // May be able to get rid of this

class ImageFileManager;
struct SDL_Surface;

class ImageFile
{
	friend class ImageFileManager;
  public:
	ImageFile(std::string fileName = "../resources/default.bmp", Extension ext = EXT_BMP);
	~ImageFile();

	// These should never be used.  Currently they will
	// ASSERT(false).  Basically, the whole point of ImageFile is
	// to prevent copying surfaces unless necessary.  They are
	// only included to suppress warnings.
	ImageFile(const ImageFile &imgFile);
	ImageFile& operator=(const ImageFile &imgFile);
	// 

	// TODO: const &
	static void setManager(ImageFileManager *manager) {
		m_manager = manager;
	}

	// If efficiency is an issue, can return an SDL_Surface**.
	// Actually, in that case, Image wouldn't even have to have an
	// ImageFile*, which could be good for a variety of reasons.
	SDL_Surface* getSurface( void ) const;

	const std::string &getName( void ) const;
	
  protected:
	// These are protected to distinguish them as what friends are
	// supposed to be allowed to use

	// If reference incremented from zero, loads and converts
	// surface if necessary.  If reference count decremented to
	// zero, frees surface.
	void incRef( void );
	void decRef( void );

	// Theoretically some sort of memory manager should take
	// advantage of this, but for now should probably just call
	// these on initialization
	void load( void ); 
	void convert( void );

  private:
	static ImageFileManager *m_manager;

	// Breaks if more than 2^32 references (was previous unsigned
	// char so 2^8), but it will assert if it does overflow.
	unsigned int m_refCount;
	std::string m_fileName; // TODO: make this const
	SDL_Surface *m_surface; // TODO: make this SDL_Surface const *
	Extension m_ext; // TODO: might as well make this const too

	// Theoretically would be useful if used with some sort of
	// memory manager, but causes trouble for now.
//	bool m_isLoaded;
//	bool m_isConverted;
};


#endif // IMAGE_FILE_H
