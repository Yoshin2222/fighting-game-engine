#ifndef CONDITIONS_H
#define CONDITIONS_H

#include <string>

#include "assert.hpp"
#include "character.hpp"

extern unsigned int g_frame;

class Object;
class Character;
class GameObject;
class Move;

enum Meter;

enum CmpType
{
	CMP_LT,		// <
	CMP_LTE,	// <=
	CMP_GT,		// >
	CMP_GTE,	// >=
	CMP_E		// ==
};

//This abstract class defines the interface for conditions.
//To add new conditions, make a derived class that implements
//different functionality for check()
class Condition
{
public:
	virtual bool check() = 0;	//check if this condition is met
	virtual Condition* clone() = 0;
//private:
	GameObject* m_obj;
};

//sample condition for testing
//COMPARE METER: Compares a meter 
class Cnd_compareMeter : public Condition
{
public:
	Cnd_compareMeter();
	Cnd_compareMeter(Character* obj, Meter meter, CmpType t, int value);

	virtual bool check();
	virtual Cnd_compareMeter* clone();
private:
	Meter m_meter;
	CmpType m_t;
	int m_value;
};

//FRAME: Checks the frame
class Cnd_frame : public Condition
{
public:
	Cnd_frame();
	Cnd_frame(GameObject* obj, unsigned int frame, CmpType t);

	virtual bool check();
	virtual Cnd_frame* clone();
private:
	unsigned int m_frame;
	CmpType m_t;
};

//FRAMES SINCE: More useful thane FRAME. Checks the number of
//frames since the Character's current move was executed
class Cnd_framesSince : public Condition
{
public:
	Cnd_framesSince();
	Cnd_framesSince(GameObject* obj, unsigned int frames, CmpType t);

	virtual bool check();
	virtual Cnd_framesSince* clone();

private:
	unsigned int m_frames;
	CmpType m_t;
};

//HIT: Checks for collisions
//TODO: Awaiting implementation
class Cnd_hit : public Condition
{
public:
	Cnd_hit();
	Cnd_hit(GameObject* obj);

	virtual bool check();
	virtual Cnd_hit* clone();
private:
};

//MOVE: Compares an obj's current move to another move
class Cnd_move : public Condition
{
public:
	Cnd_move();
	Cnd_move(GameObject* obj, std::string cmpName);

	virtual bool check();
	virtual Cnd_move* clone();
private:
	std::string m_cmpName;
};


#endif	//CONDITIONS_H