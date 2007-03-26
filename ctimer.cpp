#define DISPLAY_OVERFLOW
#undef DISPLAY_OVERFLOW

#include "ctimer.hpp"
#include <unistd.h>
#include <iostream>
// Replace iostream with logfile or output wrapper or something


// Slightly based on source from
// http://finmath.uchicago.edu/~wilder/Code/timer/

#define EXPERIMENTAL
#define BUFFER_USEC 2

CTime_Timer::CTime_Timer(long usec)
	: start(clock()) //Testing
	  , frameLength(usec)
{
	ticksPerFrame = (CLOCKS_PER_SEC * frameLength)
		/ 1e6;
	// tickPerFrame = (Ticks / Sec * (Usec / Frame)) * (Sec / Usec)
//	start = clock();
}

CTime_Timer::~CTime_Timer()
{
	(void) 0; // Do nothing
}

void CTime_Timer::setFPS(int FPS)
{
	m_FPS = FPS;
}

void CTime_Timer::waitFrame( void )
{
	// TODO: Ensure best data types
	long usecLeft;

	// TODO: Check if trailing or something
	if ( clock() > (start + ticksPerFrame) )
		std::cerr << "WARNING: Timer is behind by "
			  << ((clock() - start - ticksPerFrame) * 1000) / CLOCKS_PER_SEC
			  << " ms"
			  << std::endl;
	
	//--------------------------------------------------------------
#ifdef EXPERIMENTAL
	// EXPERIMENTAL: Sleep until BUFFER_USEC left
	usecLeft =  ( 1e6 * ( start + ticksPerFrame - clock() ) )
		/ ( CLOCKS_PER_SEC);
	if ( usecLeft > BUFFER_USEC )
		usleep( usecLeft - BUFFER_USEC );
#endif // EXPERIMENTAL
	//--------------------------------------------------------------
	
	while ( clock() < (start + ticksPerFrame) )
	{
		(void) 0; // Do nothing
	}

#ifdef DISPLAY_OVERFLOW
	std::cout << "Timer overflow: " << std::endl;
	std::cout << "\t" << ( clock() - (start + ticksPerFrame) )
		  << "\t" << ( CLOCKS_PER_SEC )
		  << std::endl;
#endif // DISPLAY_OVERFLOW
	
	start += ticksPerFrame;
	
	return;
}

void CTime_Timer::restart( void )
{
	start = clock();
}
