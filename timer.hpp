#ifndef TIMER_H
#define TIMER_H

class ITimer
{
public:
	ITimer(unsigned int FPS = 60);

	unsigned int getTicks() const;
	//returns number of ticks since creation

	unsigned int getFrames() const;
	//returns frames since creation

	void waitTicks(unsigned int t) const;
	//waits t ticks

	void waitFrames(unsigned int f) const;
	//waits f frames

	void setFPS(unsigned int FPS);
	//sets a new FPS

	bool waitUntilFrame(unsigned int f) const;
	//waits until it is frame f from beggining.
	//returns false if frame f has passed, otherwise returns true.

	bool waitUntilNextFrame() const;
private:
	unsigned int m_FPS, m_startTime;
};

#endif // TIMER_H
