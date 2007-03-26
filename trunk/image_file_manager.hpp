#ifndef IMAGE_FILE_MANAGER_H
#define IMAGE_FILE_MANAGER_H

#include <map>
#include <string>
#include "extension.hpp"

class ImageFile;
struct SDL_PixelFormat;

// TODO: Maybe implement some sort of memory management to try to make
// sure that everything is grouped and contiguous in memory or
// something.

class ImageFileManager
{
	typedef std::map< const std::string, ImageFile * > ImageFileMap;
	typedef ImageFileMap::value_type ImageFileMapPair;

        // typedef std::map< std::string, std::string > FileNameMap ;

	// FileNameMap could be useful to allow using aliases for
	// files
  public:
	ImageFileManager();
	~ImageFileManager();

	// Basically constructor and destructor for ImageFile(name)
	const ImageFile& assoc(const std::string name);
	void dissoc(const std::string name);
	
	// Maybe this should be done another way
	SDL_PixelFormat* getFormat( void ) const;
	void setFormat( SDL_PixelFormat* format );
	void debugPrint() const;
  private:
	// TODO: add private construct (const ImageFileManager &)
	// to suppress warnings; assert false
	ImageFileMap m_fileMap;
	SDL_PixelFormat *m_format;
};


#endif // IMAGE_FILE_MANAGER_H
