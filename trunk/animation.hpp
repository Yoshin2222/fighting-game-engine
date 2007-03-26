#ifndef ANIMATION_H
#define ANIMATION_H

class Image;
struct SDL_Surface;
class Rectangle;
class ImageManager;

// Actually animation should probably use an image manager such that
// memory management is actually possible.

// Maybe should eventually use the same interface as Image, although
// maybe not.  At the moment it's practically just an iterator for a
// vector of Image*.

// Rewrite to use a vector to store the data and allow Image*'s to be
// added such that it can actually manage them.
class Animation
{
  public:
	// Construction Interface
	
	Animation(const Animation &anim);
	Animation(Image** images, unsigned int count = 1,
		  bool loop = true, unsigned int current = 0);
	Animation(Image* image);
	Animation& operator=(const Animation &anim);
	~Animation();

	static void setManager(ImageManager *manager) {
		m_manager = manager;
	}

	// Access Interface
	
	bool isDone() const;

	SDL_Surface* getSurface( void ) const;
	Rectangle getRectangle( void ) const;

	// Sets m_current to the next frame.  Returns true on success,
	// false if at the end of a non-looping animation
	bool next( void );
	
  private:
	static ImageManager *m_manager;

	Image** m_images;
	unsigned int m_count;
	unsigned int m_current;
	bool m_loop;
	// this is to allow more assertions and generally make loading
	// Animations safer.
	bool final;
};

#endif // ANIMATION_H
