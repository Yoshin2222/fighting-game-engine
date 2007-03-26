#include "graphics.hpp"
#include "assert.hpp"
#include "priority.hpp"
#include "image_file_manager.hpp"
#include "image.hpp"
#include "sprite.hpp"
#include "animating_sprite.hpp"
#include "rectangle.hpp"
#include "pair.hpp"
#include <SDL/SDL.h>
#include <memory>
#include <iostream>
#include <queue>


ImageFileManager* Graphics::m_manager = NULL;

// Public Methods

// Should probably be completely re-written for error-handling,
// organization, multiple settings etc.
Graphics::Graphics(int width, int height, int bpp)
	: m_verbose(true), m_ready(0),
	  m_current(new DrawQueue), 
	  m_next(new DrawQueue)
{
	// TODO: Add error-handling, etc.
	SDL_Init(
		SDL_INIT_VIDEO //|
//		SDL_INIT_AUDIO |
//		SDL_INIT_TIMER |
//		SDL_INIT_EVENTTHREAD
		);

	Uint32 init = SDL_WasInit(SDL_INIT_AUDIO);

	if(init & SDL_INIT_AUDIO)
	{
		m_sound = true;  // Audio init sucessful, use sound
	} else {
		m_sound = false;  // Audio init unsucessful, don't use sound
	}
	
	// Initializes at 32 bpp, so should be careful with fewer colors
	m_screen = SDL_SetVideoMode(width, height, bpp,
//				  SDL_SWSURFACE);
				  SDL_SWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
//				  SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
//				  SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN|SDL_ASYNCBLIT);

	if ( !(m_screen->flags && SDL_HWSURFACE) )
		std::cerr << "Graphics: Failed to initialize in Video Memory"  << std::endl;
	if ( !(m_screen->flags && SDL_DOUBLEBUF) )
		std::cerr << "Graphics: Failed to initialize double buffering" << std::endl;

	m_manager->setFormat(SDL_GetVideoInfo()->vfmt);

	// These should be parameters or something, and probably
	// within a separate function
	SDL_WM_SetCaption("Game", "");
	m_icon = SDL_LoadBMP("../resources/testicon.bmp");
	SDL_SetColorKey(m_icon, SDL_SRCCOLORKEY,
			SDL_MapRGB(m_icon->format, 0xff, 0xff, 0xff));
	SDL_WM_SetIcon(m_icon, NULL);


	// TODO: put in initializer list later
//	m_width = width;
//	m_height = height;
//	m_bpp = bpp;
	// Replace with error-handling
	ENSURE ( m_screen != NULL );
	
}

Graphics::~Graphics()
{
	SDL_FreeSurface(m_screen);
	SDL_Quit();
}


void Graphics::resetVideo(int width, int height, int bpp)
{
	m_screen = SDL_SetVideoMode(width, height, bpp,
//				  SDL_SWSURFACE);
//				  SDL_SWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
				  SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
//				  SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN|SDL_ASYNCBLIT);

}

/*
SDL_Surface *SDL_CreateRGBSurfaceFrom(void *pixels, int width, int height, int bitsPerPixel, int pitch, 
                                      Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask);
*/

Graphics& Graphics::operator=(const Graphics &g)
{
	m_verbose = g.m_verbose;
	m_sound = g.m_sound;
	m_screen = Graphics::newSDL_Surface(g.m_screen);
	m_current = new DrawQueue(*g.m_current);
	m_next = new DrawQueue(*g.m_next);

	return *this;
}

// This copy constructor should not be used.  At the moment it
// probably doesn't even work.
Graphics::Graphics(const Graphics &g)
	: m_verbose(g.m_verbose), m_sound(g.m_sound),
	  m_screen(Graphics::newSDL_Surface(g.m_screen)),
	  m_current(new DrawQueue(*g.m_current)),
	  m_next(new DrawQueue(*g.m_current))
{
	ASSERT(false); // See comment above
}


// Update if used SDL subsystems change
void Graphics::checkInit()
{
	// May not work for everything
	Uint32 init = SDL_WasInit(SDL_INIT_EVERYTHING);
	
	if ( init & SDL_INIT_VIDEO )
	{
		if (m_verbose) std::cout << "Video initialized" << std::endl;
	} else {
		std::cerr << "Video failed to initialize" << std::endl;
	}

	/*
	if ( init & SDL_INIT_AUDIO )
	{
		if (m_verbose) std::cout << "Audio initialized" << std::endl;
	} else {
		std::cerr << "Audio failed to initialize" << std::endl;
	}

	if ( init & SDL_INIT_TIMER )
	{
		if (m_verbose) std::cout << "Timer initialized" << std::endl;
	} else {
		std::cerr << "Timer failed to initialize" << std::endl;
	}

	if ( init & SDL_INIT_EVENTTHREAD )
	{
		if (m_verbose) std::cout << "Event Thread initialized" << std::endl;
	} else {
		std::cerr << "Event Thread failed to initialize" << std::endl;
	}
	*/
}

void Graphics::enqueue(AnimatingSprite *sprite)
{
	m_next->push(sprite);
}

void Graphics::process()
{
	if (draw())
	{
		// TODO: Implement this
		// timer.waitUntilFrame(NEXT_FRAME);
		flip();
		change(); // prepares current for drawing
	}
	
	clear(); // prepares next for input

	return;
	
}

void Graphics::skip()
{
	clear();
	return;
}

// Private Methods

void Graphics::change()
{
	DrawQueue *tmp;
	
	// Switch current and next
	tmp = m_current;
	m_current = m_next;
	m_next = tmp;

	return;
}

void Graphics::clear()
{
	// clears next
	while ( !m_next->empty() )
	{
		m_next->pop();
	}
}

bool Graphics::draw_accel()
{
	// 296 ms for 400 sprites + bg
	// increases efficiency, might make harder to test speed though
//	if (m_current->empty())
//		return false;

	++m_alt %= 2;
	// could store stuff elsewhere to avoid allocation
	std::vector <AnimatingSprite *> lines[m_screen->h];
	for (int i = 0; i < m_screen->h; ++i)
	{
		lines[i].reserve(255);
	}


	// fill lines with appropriate Animating Sprite *s
	// ~17ms
	while ( !m_current->empty() )
	{
		ASSERT(m_current->top() != NULL);

		Rectangle tmp;
		tmp = m_current->top()->getRegion();

		for (int i = tmp.getMin().y;
		     i < ( tmp.getMax().y);
		     ++i)
		{
			// doesn't seem to work once sprites go off screen
			if (!( i < m_screen->h)) break;
			if (!( i >= 0)) break;
			lines[i].push_back(m_current->top());
		}
		m_current->pop();
	}

	// pixels stores which sprite is on top
	unsigned char pixels[m_screen->h][m_screen->w];

	for (int i = 0; i < m_screen->h; ++i)
	{
		memset(&pixels[i][0], 255, m_screen->w);
	}


	// TODO: make this reasonably efficient
	// finds which sprite on top for all pixels
	// ~66 ms
	for (int i = m_alt; i < m_screen->h - 1; i += 2)
	{
		for (unsigned char j = 0; j < lines[i].size() and j < 255; ++j)
		{
			Rectangle tmp;
			tmp = lines[i][j]->getRegion();
			// incorrect display if entire sprite off screen to left
			memset(
				&pixels[i][std::max(tmp.getMin().x, 0)],
				j,
				std::min(tmp.getMax().x, m_screen->w) - tmp.getMin().x
				);
		}
	}
/*
	for (int i = 0; i < 1280; ++i)
	{
		for (int j = 0; j < 1024; ++j)
		{
			std::cout << int(pixels[i][j]) << " ";
		}
	}
*/
	// iterates through finding run lengths and blitting to screen
	// uses SDL_Rect rather than separate variables for efficiency

	SDL_Rect r;
	r.h = 1;
	for (r.y = m_alt; r.y < m_screen->h - 1; r.y += 2)
	{
		unsigned char last = pixels[r.y][0];
		r.x = 0;
		r.w = 1;
		for (int i = 1; i < m_screen->w; ++i)
		{
			if (last == 255) continue;
			if (pixels[r.y][i] == last)
			{
				++r.w;
			} else {


				SDL_BlitSurface(lines[r.y][last]->getSurface(),
						&toSDL_Rect(
							Rectangle(
//								Pair(r.w, 1),
								Pair(r.w, 1),
								Pair(r.x, r.y))							+ lines[r.y][last]->getOffset()),
						m_screen,
						&r
					);

				r.x = i;
				r.w = 1;
				last = pixels[r.y][i];
			}
		}
		if (last != 255)
		{

			SDL_BlitSurface(lines[r.y][last]->getSurface(),
					&toSDL_Rect(
						Rectangle(
//							Pair(r.w, 1),
							Pair(r.w, 1),
							Pair(r.x, r.y))
						+ lines[r.y][last]->getOffset()),
					m_screen,
					&r
				);

		}
	}


/*
				std::cout << int(last) << " ("
					  << r.x << ",\t"
					  << r.y << ",\t"
					  << r.w << ",\t"
					  << r.h << ")\n";
//					  << r.x
*/
		// TODO: Implement this
//		if (TIME_TO_BREAK)
//			return false;

//	m_alt = !m_alt;
	m_ready = true;

	return true;
}

bool Graphics::draw()
{
	// increases efficiency, might make harder to test speed though
//	if (m_current->empty())
//		return false;
	while ( !m_current->empty() )
	{
		ASSERT(m_current->top() != NULL);
		m_current->top()->writeTo(m_screen);
		
		m_current->pop();

		// TODO: Implement this
//		if (TIME_TO_BREAK)
//			return false;
	}

	m_ready = true;

	return true;
}



void Graphics::flip()
{
	SDL_Flip(m_screen);
	m_ready = false;
}

void Graphics::sLock()
{
	if ( SDL_MUSTLOCK(m_screen) )
	{
		if ( SDL_LockSurface(m_screen) < 0 )
		{
			return;
		}
	}
}

void Graphics::sUlock()
{
	if ( SDL_MUSTLOCK(m_screen) )
	{
		SDL_UnlockSurface(m_screen);
	}
}

