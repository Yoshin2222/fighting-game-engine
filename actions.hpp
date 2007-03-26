#ifndef ACTIONS_H
#define ACTIONS_H

#include "assert.hpp"
#include "character.hpp"
#include "move.hpp"

extern unsigned int g_frame;

class Object;
class Character;
class GameObject;
class Projectile;
class Move;

//typedef Character Object;

enum Meter;

//This abstract class defines the interface for actions.
//To add new actions, make a derived class that implements
//different functionality for perform()
class Action
{
public:
	virtual void perform() = 0;
	virtual Action* clone() = 0;
//private:
	GameObject* m_target;
};

//sample Actions for testing

//SET METER: Set a character's meter to a value
class Act_setMeter : public Action
{
public:
	Act_setMeter();
	Act_setMeter( Character* target, Meter meter, int value);

	virtual void perform();
	virtual Act_setMeter* clone();
private:
//	Character* m_target;
	Meter m_meter;
	int m_value;
};

//MOD METER: Modify a character's meter by a value
class Act_modMeter : public Action
{
public:
	Act_modMeter();
	Act_modMeter( Character* target, Meter meter, int change);

	virtual void perform();
	virtual Act_modMeter* clone();
private:
//	Character* m_target;
	Meter m_meter;
	int m_change;
};


//SET MOVE: Modify a character's current move
class Act_setMove : public Action
{
public:
	Act_setMove();
	Act_setMove( GameObject* target, Move* newMove );

	virtual void perform();
	virtual Act_setMove* clone();
private:
//	GameObject* m_target;
	Move* m_newMove;
};

//ADD CHILD: Creates a child object and adds it to the
//target's children. This is for use with projectiles,
//or other things like that.
class Act_addChild : public Action
{
public:
	Act_addChild();
	Act_addChild( Character* target, Projectile* baseObj );	//baseObj will be copied; it must have a copy constructor

	virtual void perform();
	virtual Act_addChild* clone();
private:
	Projectile* m_baseObj;
};

//REMOVE CHILD: Removes a child. Uses string or Object*.
class Act_removeChild : public Action
{
public:
	Act_removeChild();
	Act_removeChild(Character* target, Projectile* obj);

	virtual void perform();
	virtual Act_removeChild* clone();
private:
	Character* m_target;
	Projectile* m_obj;
	std::string m_name;
};

//REMOVE SELF: A child removes it self. Suicide or something.
class Act_removeSelf : public Action
{
public:
	Act_removeSelf();
	Act_removeSelf(Projectile* target);

	virtual void perform();
	virtual Act_removeSelf* clone();
private:
	Projectile* m_target;
};

//CHANGE POSITION: Changes a character's positon
//TODO: Awaiting implementation
class Act_changePosition : public Action
{
public:
	Act_changePosition();
	Act_changePosition( GameObject* target );

	virtual void perform();
	virtual Act_changePosition* clone();
private:
	GameObject* m_target;
};


#endif	//ACTIONS_H