#include "image_manager.hpp"
#include "assert.hpp"
#include "image.hpp"
#include "debug.hpp"

ImageManager::ImageManager()
	: m_refMap()
{
	
}

ImageManager::~ImageManager()
{
	// TODO: Check this for memory leaks or something
	// Deletes refMap, may not entirely work
	ImageRefMap::iterator iter;
	for ( iter =  m_refMap.begin();
	      iter != m_refMap.end()  ;
	      iter++ )
	{
		// iter->second is an unsigned int!
//		delete iter->second;
//		delete iter->first;
	}
	m_refMap.clear();
}

void ImageManager::assoc(Image *image)
{
	unsigned int last;
	if ( m_refMap.count(image) == 0 )
	{
		// tmp = new ImageFile(m_imageMap[image], EXT_BMP);
		// m_imageMap[image] = tmp;
		m_refMap[image] = 0;
	}

	last = m_refMap[image];
	// Hopefully this works
	m_refMap[image] = (unsigned int)m_refMap[image] + 1;

	// Asserts if it doesn't
	ASSERT(m_refMap[image] == last + 1);
	
	ENSURE ( m_refMap.count(image) == 1 );
	ENSURE ( m_refMap[image] > 0 ); // asserts on overflow
}

void ImageManager::dissoc(Image *image)
{
	REQUIRE ( m_refMap.count(image) == 1 );
	REQUIRE ( m_refMap[image] > 0 ); // asserts on dissoc after
					// overflow or logic error
	
	unsigned int last = m_refMap[image];

	// Hopefully this works
	m_refMap[image] = (unsigned int)m_refMap[image] - 1;

	// Asserts if it doesn't
	ASSERT(m_refMap[image] == last - 1);

	// Deletes image if no more references.  If everything of this
	// level or a higher one (Animation or Sprite) is pre-loaded
	// and released, it shouldn't delete anything until those are
	// released.
	if (m_refMap[image] == 0)
		delete image;
}

void ImageManager::debugPrint() const
{
	ImageRefMap::const_iterator iter = m_refMap.begin();
	int count = 0;
	for ( iter =  m_refMap.begin();
	      iter != m_refMap.end()  ;
	      iter++ )
	{
		cout << "  ";
		cout << ++count << ":: ";
		cout << iter->first;
		cout << " " ;
		cout << iter->second << endl;
	}
}
