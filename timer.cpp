#include "timer.hpp"
#include "assert.hpp"
#include <SDL/SDL.h>
#include "debug.hpp"

ITimer::ITimer(unsigned int FPS)
	: m_FPS(FPS), m_startTime( SDL_GetTicks() )
{
//	cout << "Creating Timer at " << m_startTime << endl;
}

void ITimer::setFPS(unsigned int FPS)
{
	m_FPS = FPS;
}

unsigned int ITimer::getTicks() const
{
	return SDL_GetTicks() - m_startTime;
}

unsigned int ITimer::getFrames() const
{
	double frames = ( (double)getTicks() * (double)m_FPS ) / 1000;
	return (unsigned int) frames;
}

//waits for t ticks
void ITimer::waitTicks(unsigned int t) const
{
	SDL_Delay( (int) t );
}

//waits for f frames
void ITimer::waitFrames(unsigned int f) const
{
	waitTicks( ( f * 1000 ) / m_FPS );
}

//waits until it is frame f from beginning.
//returns false if frame f has passed, otherwise returns true
bool ITimer::waitUntilFrame(unsigned int f) const
{
	double tick = (double(1000) / double(m_FPS) ) * double(f);

	if( tick < getTicks() )
		return false;

	waitTicks( (int)(tick - getTicks()) );

	return true;
}

bool ITimer::waitUntilNextFrame() const
{
	// do something later
	return false;
}
