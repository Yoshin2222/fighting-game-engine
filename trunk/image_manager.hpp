#ifndef IMAGE_MANAGER_H
#define IMAGE_MANAGER_H

#include <map>
//#include <string>

class Image;

// TODO: Maybe provide memory allocation services and/or name to Image*
// services.  Something like register(Image constructor parameters),
// or register(string name, Image constructor parameters).  Then could
// Image* assoc(string name) sort of like ImageFileManager.

// At the moment ImageManager is basically just a smart_ptr<Image>.
// May want to use that instead or something eventually.
class ImageManager
{
	typedef std::map< Image *, unsigned int > ImageRefMap;
	typedef ImageRefMap::value_type ImageRefPair;

	// ImageNameMap could be useful to allow using aliases for
	// files
  public:
	ImageManager();
	~ImageManager();

	// Counts references to the image.  Deletes it when the
	// reference count reaches zero.  For some sort of memory
	// management, could have an image loader load all the images
	// that are expected to be used.  Although since Images are
	// mostly used by Sprites and Animations, it would also work
	// if all the appropriate Sprites and Animations were loaded
	// in that manner.
	void assoc(Image *image);
	void dissoc(Image *image);
	void debugPrint() const;
  private:
	ImageRefMap m_refMap;
};


#endif // IMAGE_MANAGER_H
