#include "assert.hpp"
#include "priority.hpp"
#include "graphics.hpp"
#include "rectangle.hpp"
#include "image_file_manager.hpp"
#include "image.hpp"
#include "sprite.hpp"
#include "image_file.hpp"
#include "timer.hpp"
#include "input.hpp"
#include "testinput.hpp"
#include "animation.hpp"
#include "image_manager.hpp"
#include "animating_sprite.hpp"
#include "sizeof.hpp"

//temporary
#include <SDL/SDL.h>

#include <iostream>
#include <string>

#define FRAMES_PER_SECOND 75
#define TEST_SPRITE_MULTIPLE 3

int main ( int argc, char * argv[] )
{
	(void) argc; (void) argv; // to suppress unused variables warning

//	SizeOf::showSizes();
	
	ImageFileManager ifManager = ImageFileManager();
	ImageManager iManager = ImageManager();

	Graphics::setManager(&ifManager);
	ImageFile::setManager(&ifManager);
	Image::setManager(&ifManager);
	Animation::setManager(&iManager);

//	CTime_Timer t( (long) 1e6 / FRAMES_PER_SECOND ); 

//	Rectangle r(Pair(), Pair(637, 480), Pair());
	
	Graphics g(1280, 1024, 32);
	g.checkInit();

	// SDL-based timer must be initialized after Graphics
	ITimer timer(FRAMES_PER_SECOND);
	std::cout
		<< "initializing timer at "
		<< FRAMES_PER_SECOND
		<< " frames per second" << std::endl;


	int i = 0;
	Priority p1(PRIORITY_BG);
	Priority p2(PRIORITY_OBJ);

//	t.waitFrame();

//	Sprite *bg, *fg;
	
	/*
	std::cout << "Testing input: " << std::endl
		  << " Press and release z, x, c, UP, RIGHT, DOWN, LEFT, q" << std::endl;
	inputHandlerTests();
	std::cout << "Input Handler Test complete" << std::endl;
	*/
	
	/*
	bg = new Sprite(
		"../resources/test.bmp",
		new Rectangle(Pair(637, 480)),
		Priority(PRIORITY_BG),
		Pair(0, 0)
		);
	*/

	Image *bg1, *bg2, *bg3, *bg4;
	Image *bgfr[4];
	/*
	bgfr[0] = new Image(
		"../resources/Capture_001.bmp",
		new Rectangle(Pair(1280, 1024))
		);
	bgfr[1] = new Image(
		"../resources/Capture_002.bmp",
		new Rectangle(Pair(1280, 1024))
		);
	bgfr[2] = new Image(
		"../resources/Capture_003.bmp",
		new Rectangle(Pair(1280, 1024))
		);
	bgfr[3] = new Image(
		"../resources/Capture_004.bmp",
		new Rectangle(Pair(1280, 1024))
		);
	*/

	bgfr[0] = new Image(
		"../resources/Capture_002.bmp",
		Rectangle(Pair(1280, 1024))
		);
	bgfr[1] = new Image(
		"../resources/Capture_003.bmp",
		Rectangle(Pair(1280, 1024))
		);
	bgfr[2] = new Image(
		"../resources/Capture_004.bmp",
		Rectangle(Pair(1280, 1024))
		);
	Image** bgtmp;
	bgtmp = new Image*[61];
	for (int i = 0; i < 61; ++i)
	{
		bgtmp[i] = bgfr[i%3];
	}

	Animation *bganim = new Animation(bgtmp, 60);
	AnimatingSprite *bg(
		new AnimatingSprite(bganim, Priority(PRIORITY_BG))
		);

	/*
	delete bgfr[0];
	delete bgfr[1];
	delete bgfr;
	delete bgtmp;
	delete bganim;
	delete bg;
	*/
	/*
	fg = new AnimatingSprite(
		new Animation(
			new Image("../resources/new.bmp",
			      new Rectangle(Pair(248, 270)))
			),
		Priority(PRIORITY_OBJ),
		Pair(35, 10)
		);
	*/

	AnimatingSprite **sprites;
	sprites = new AnimatingSprite*[10000];
	
	Pair *speeds;
	speeds = new Pair[(TEST_SPRITE_MULTIPLE * TEST_SPRITE_MULTIPLE)];
	for (int k = 0; k < (TEST_SPRITE_MULTIPLE * TEST_SPRITE_MULTIPLE); ++k)
	{
//		if (!(k%1000))
//			std::cout << "initializing: " << k << std::endl;
		sprites[k] = new AnimatingSprite(
			new Animation(
				new Image(
					"../resources/new.bmp",
					Rectangle(
//						Pair(248, 270)))),
						Pair(300, 300)))),
			Priority(PRIORITY_OBJ),
			Pair(35, 10)
			);
		speeds[k] = Pair(k%TEST_SPRITE_MULTIPLE, k/TEST_SPRITE_MULTIPLE);
	}

	bool done = false;
	
	// Loop copied from that tutorial
	
	Pair speed(8, 3);
	int ticks = 0;
	int counter = 0;
	bool skipNext = false;
	int frame = timer.getFrames();
	int framesDrawn = 0;
	bool pause = 0;
	bool change = 0;


	while( !done )
	{
		ticks = timer.getTicks();
		counter++;
//		if ( !(++i % 600))
//			std::cout << i << std::endl;
		
//		if ( !(i % FRAMES_PER_SECOND) )
//			speed = speed + Pair(1, -1);

		// move and enqueue sprites

		
		for (int k = 0; k < (TEST_SPRITE_MULTIPLE * TEST_SPRITE_MULTIPLE); ++k)
		{
			if ( (sprites[k]->getPosition().x < 0) || (sprites[k]->getPosition().x + 248 > 1280))
				speeds[k].x = -speeds[k].x;
			if ( (sprites[k]->getPosition().y < 0) || (sprites[k]->getPosition().y + 270> 1024))
				speeds[k].y = -speeds[k].y;

			sprites[k]->move(speeds[k]);
			g.enqueue(sprites[k]);
		}

		
//		std::cout << "After moving and enqueuing sprites" << std::endl;

		g.enqueue(bg);

//		std::cout
//			<< "Frame: " << frame << "/"
//			  << timer.getFrames()
//			  << std::endl;
		/*
		std::cout
			<< "Timer ticks: " << timer.getTicks()
			<< std::endl;
		*/
//		std::cout << "Ticks this frame: ";

//		std::cout << timer.getTicks() - ticks << " "
//			  << 1000/(timer.getTicks() - ticks)
//			;
//		std::cout << std::endl;

		SDL_Event event;

		change = false;
		while ( SDL_PollEvent(&event) )
		{
			if ( event.type == SDL_QUIT )  {  done = true;  }

			if ( event.type == SDL_KEYDOWN )
			{
				if ( event.key.keysym.sym == SDLK_ESCAPE ) { done = 1; }
//				std::cout << "SDL_KEYDOWN event" << std::endl;
			}

			/*
			if ( event.type == SDL_ACTIVEEVENT )
			{
				if ( SDL_APPACTIVE & event.active.state )
				{
					change = (pause == event.active.gain);
					pause = !event.active.gain;
					std::cout << "SDL_APPACTIVE event" << std::endl;
				}					
				
			}
			*/
		}
		/*
		if (change && !pause)
		{
//			g.resetVideo(1280, 1024, 32);
			std::cout << "getting new surface" << std::endl;
		}

		if (done) continue;
		if (pause) continue;
		*/
			
		if ( timer.waitUntilFrame( frame++ ) )
		{
//			std::cout << "Processing... ";
			g.process();
			++ framesDrawn;
		} else {
//			std::cout << "Skipping... ";
			g.skip();
//			std::cout << "( "
//				  << timer.getFrames()+2 - frame
//				  << " frames ) ";
			frame = timer.getFrames()+2;
		}

//		std::cout << "Before processing graphics" << std::endl;
//		std::cout << "After processing graphics" << std::endl;
//		timer.waitUntilFrame(timer.getFrames() + 1);

//		std::cout << SDL_GetTicks() << " "
		// -ticks
//		std::cout << timer.getTicks() - ticks << " "
//			  << 1000/(timer.getTicks() - ticks)
//			  <<  std::endl;

		/*
		bg->next();
//		std::cout << counter << std::endl;
		if (counter % 10)
		{
			//ifManager.debugPrint();
			//iManager.debugPrint();
		}
		*/
	}
	

	std::cerr << framesDrawn << " Frames Drawn over "
		  << timer.getTicks() / 1000 << " seconds ( "
		  << (double)framesDrawn * 1000 / timer.getTicks()
		  << " average fps)\n";
	
	// Would not be good to forget this
	delete [] speeds;
	delete [] bgtmp;

	/*
	for (int k = 0; k < (TEST_SPRITE_MULTIPLE * TEST_SPRITE_MULTIPLE); ++k)
	{
		delete sprites[k];
	}

	delete bg;


	*/

	delete [] sprites;

	std::cout << "Done" << std::endl;
	
	return 0;
}


	
