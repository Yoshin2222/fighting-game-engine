#include "assert.hpp"
#include "inputhandler.hpp"
#include "Character.hpp"
#include "timer.hpp"
#include "graphics.hpp"
#include "game.hpp"

#include <iostream>
#include <fstream>
#include <string>

#define FRAMES_PER_SECOND 16

unsigned int g_frame = 0;

int main ( int argc, char * argv[] )
{
	Character ch;
	InputHandler ih;
	std::vector< Input >* inp;
	bool cont = true;

		/* initialize SDL */
	if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK ) < 0 )
	{
		fprintf( stderr, "Video initialization failed: %s\n",
			SDL_GetError( ) );
		SDL_Quit( );
	}

	// Set a video mode
	if( !SDL_SetVideoMode(320, 200, 0, 0) )
	{
		fprintf( stderr, "Could not set video mode: %s\n",
			SDL_GetError( ) );
		SDL_Quit( );
	}

	printf("abc");

	CharManager cm;
	std::fstream fin("ryu.txt", std::fstream::in);
	std::string s;

	cm.m_prepStream(fin, "ryu.txt", "Library");
	getline(fin, s, '\t');
	printf("(%s)", s.c_str() );

//	Game g("Ryu", "Ryu");
//	g.play();

	return 0;
}


