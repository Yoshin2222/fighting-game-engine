#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL/SDL.h>
#include "rectangle.hpp"

#include <string>
#include <queue>
#include "animating_sprite.hpp"

class ImageFileManager;
class ImageFile;
class Image;
//class AnimatingSprite;
//class AnimatingSpriteCompare;

class Graphics
{
  public:
	// There may be a better way of doing this
	static void setManager(ImageFileManager *manager) {
		m_manager = manager;
	}

	// I considered adding this to the Rectangle class, but I
	// don't see why Rectangle should have to include the SDL
	// headers or know what an SDL_Rect is.  Although actually,
	// there isn't any reason for Graphics to know what a
	// Rectangle or SDL_Rect is either.  It should probably be put
	// into a separate namespace and header or something.
	static SDL_Rect toSDL_Rect(Rectangle r) {
		SDL_Rect ret;

		ret.x = r.getMin ().x;
		ret.y = r.getMin ().y;
		ret.w = r.getSize().x;
		ret.h = r.getSize().y;
		
		return ret;
	}

	// Likewise, I'm not sure if this is the best way of doing
	// this.
	static SDL_Surface* newSDL_Surface(SDL_Surface *surface) {
		return SDL_CreateRGBSurfaceFrom(
			surface->pixels,
			surface->w,
			surface->h,
			surface->format->BitsPerPixel,
			surface->pitch,
			surface->format->Rmask,
			surface->format->Gmask,
			surface->format->Bmask,
			surface->format->Amask
			);
	}

	// Temporary default values.  Maybe should take a Pair
	// instead, but would require more headers being included
	Graphics(int width = 640, int height = 480, int bpp = 16);
	Graphics(const Graphics &g);
	Graphics& operator=(const Graphics &g);
	~Graphics();

	void checkInit();
	void resetVideo(int width, int height, int bpp);

	void enqueue(AnimatingSprite *sprite); // adds image to *next

	// Eventually should work as follows: Begin drawing whatever
	// is in the *current draw queue.  If drawing finishes before
	// it is time to stop, waits or calls a callback or something
	// until out of time, and then switches *next, the draw queue
	// for the next frame, with *current and flips *screen onto
	// the display.  In either case, it will then clear *next to
	// allow for adding next frame's sprites there.
	void process();
	// Skips this frame
	void skip();

  private:
	typedef std::priority_queue< AnimatingSprite *, std::vector< AnimatingSprite * >, AnimatingSpriteCompare > DrawQueue;
	
	static ImageFileManager *m_manager;

	void change(); // switches current and next
	void clear(); // clears next
	bool draw(); // draws current to screen
	bool draw_accel(); // draws using graphics acceleration, 256 sprites per line
	void flip(); // Switches screen with current display
	
	void sLock(); // Locks the screen for writing (presumably possibly necessary)
	void sUlock(); // Unlocks the screen after writing

	bool m_verbose, m_sound;
	bool m_ready; // set after drawing to buffer; unset after flipping to screen
//	int m_alt1;

	SDL_Surface *m_screen;
	SDL_Surface *m_icon;

	// As it turns out, m_format is obtained by just using
	// SDL_GetVideoInfo()->vfmt, and at the moment it's only used
	// for initializing the ImageFileManager, so it's not really
	// necessary
//	SDL_PixelFormat *m_format;

	DrawQueue *m_current, *m_next;
	int m_alt;
//	int m_width, m_height, m_bpp;
	
};



#endif // GRAPHICS_H

