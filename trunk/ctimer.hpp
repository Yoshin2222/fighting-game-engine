#ifndef CTIMER_H
#define CTIMER_H

#include "timer.hpp"
#include <ctime>

class CTime_Timer : public ITimer
{
  public:
	CTime_Timer(long usec);
	~CTime_Timer();

	void setFPS(int FPS);
	void waitFrame( void );
	void restart( void );


  private:
	clock_t start;
	long ticksPerFrame;
	long frameLength; // usec

};


#endif // CTIMER_H
