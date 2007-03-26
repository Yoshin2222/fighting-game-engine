#include "image_file_manager.hpp"
#include "image_file.hpp"
#include "assert.hpp"
#include <SDL/SDL.h>
#include "debug.hpp"
#include <map>

ImageFileManager::ImageFileManager()
	: m_fileMap()
{
	
}

ImageFileManager::~ImageFileManager()
{
	// Check this for memory leaks or something
	// Delete fileMap, may not entirely work
	ImageFileMap::iterator iter;
	for ( iter =  m_fileMap.begin();
	      iter != m_fileMap.end()  ;
	      iter++ )
	{
//		delete iter->second;
//		delete &(iter->first);
	}
	m_fileMap.clear();

	// CHECK: this might not work as expected, especially without
	// including SDL.h
	delete m_format;
}

const ImageFile& ImageFileManager::assoc(const std::string name)
{
	// For efficiency, should store m_fileMap[name] as local
	// variable to avoid repeatedly searching for it
	if ( m_fileMap.count(name) == 0 )
	{
		// tmp = new ImageFile(m_nameMap[name], EXT_BMP);
		// m_nameMap[name] = tmp;
		m_fileMap[name] = new ImageFile(name, EXT_BMP);
		ASSERT( m_fileMap[name]->m_refCount == 0 );
	}

	/*
		m_fileMap.insert(
			ImageFileMapPair (
				name, new ImageFile(name, EXT_BMP))
			);
	*/
	// m_fileMap[m_nameMap[name]] = new ImageFile(name, m_ext);

	m_fileMap[name]->incRef();

	ENSURE ( m_fileMap[name] != NULL );
	ENSURE ( m_fileMap.count(name) == 1 );
	ENSURE ( m_fileMap[name]->m_refCount > 0); // asserts on overflow
	ENSURE ( m_fileMap[name]->getSurface() != NULL );

	return *m_fileMap[name];
}

void ImageFileManager::dissoc(const std::string name)
{
	REQUIRE ( m_fileMap.count(name) == 1 );
	
	m_fileMap[name]->decRef();
}

SDL_PixelFormat* ImageFileManager::getFormat() const
{
	return m_format;
}

void ImageFileManager::setFormat( SDL_PixelFormat* format )
{
	m_format = format;
}

void ImageFileManager::debugPrint() const
{
	ImageFileMap::const_iterator iter = m_fileMap.begin();
	int count = 0;
	for ( iter =  m_fileMap.begin();
	      iter != m_fileMap.end()  ;
	      iter++ )
	{
		cout << " ";
		cout << ++count << ": ";
		cout << iter->second;
		cout << " " ;
		cout << iter->first << endl;
	}
}
