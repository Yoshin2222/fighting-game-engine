#ifndef IMAGE_H
#define IMAGE_H

#include "rectangle.hpp" // for default constructor
#include <string>

struct SDL_Surface;
class ImageFile;
class ImageFileManager;

class Image
{
  public:
	static void setManager(ImageFileManager *manager) {
		m_manager = manager;
	}

	Image(const Image &image);
	Image(const std::string &name, Rectangle rect = Rectangle());
	~Image();

	Rectangle getRectangle( void ) const;
	
	SDL_Surface* getSurface( void ) const;
  private:
	// operator= should never be used, asserts false
	Image& operator=(const Image &image);
	// This replaces m_name
	const std::string& getName( void ) const;
	
	static ImageFileManager *m_manager;

	const ImageFile &m_imageFile;
	Rectangle m_rect;
};

#endif // IMAGE_H
