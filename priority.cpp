#include "priority.hpp"

Priority::~Priority()
{
	(void) 0; // Do nothing
}


Priority::Priority(PriorityFlags pFlags)
	: p(pFlags)
{

}

Priority::Priority(const Priority &priority)
	: p(priority.p)
{
	
}

/*
static Priority& Priority::Hitting(Character &character)
{
	return character.getPriority() + PRIORITY_INC;
}
*/

Priority& Priority::operator+(PriorityFlags pFlags)
{
	p = p | pFlags;
	return *this;
}

Priority& Priority::operator-(PriorityFlags pFlags)
{
	p = p ^ pFlags;
	return *this;
}

bool Priority::operator<(PriorityFlags pFlags) const
{
	return (getValue() < Priority(pFlags).getValue());
}

bool Priority::operator>(PriorityFlags pFlags) const
{
	return (getValue() > Priority(pFlags).getValue());
}

Priority& Priority::operator+(const Priority &arg)
{
	p = p | arg.p;
	return *this;
}

Priority& Priority::operator-(const Priority &arg)
{
	p = p ^ arg.p;
	return *this;
}

bool Priority::operator<(const Priority &arg) const
{
	return (getValue() < arg.getValue());
}

bool Priority::operator>(const Priority &arg) const
{
	return (getValue() > arg.getValue());
}

/* Maybe implement later
// Returns first flag matched
int Value(PriorityFlag flag)
{
	
}
*/

// Make better by having a function that returns the value
// corresponding to the flag, then doing something like
//
// for ( int i = 0; i < MAX; ++i) 
// { 
// 	if ((tmp >> i) % 2 ) 
// 		ret += value(PriorityFlag(tmp)); 
// }
//
// That is, put the extraction and addition into one function, and
// finding the value of an individual flag in another
int Priority::getValue() const
{
	int ret;
	
	ret = 0;
	
	if   (p & PRIORITY_CHAR) 
		ret += PRI_CHAR;
	if   (p & PRIORITY_OBJ) 
		ret += PRI_OBJ;
	if   (p & PRIORITY_EFFECT) 
		ret += PRI_EFFECT;
	if   (p & PRIORITY_INTERFACE) 
		ret += PRI_INTERFACE;
	if   (p & PRIORITY_BG) 
		ret += PRI_BG;

	if   (p & PRIORITY_DODGE_FORWARD) 
		ret += PRI_DODGE_FORWARD;
	if   (p & PRIORITY_ATTACK) 
		ret += PRI_ATTACK;
	if   (p & PRIORITY_DODGE_BACK) 
		ret += PRI_DODGE_BACK;
	if   (p & PRIORITY_REEL) 
		ret += PRI_REEL;
	if   (p & PRIORITY_SUPER) 
		ret += PRI_SUPER;
	if   (p & PRIORITY_SPECIAL) 
		ret += PRI_SPECIAL;

	if   (p & PRIORITY_MISC_DEC) 
		ret += PRI_MISC_DEC;
	if   (p & PRIORITY_MISC_INC) 
		ret += PRI_MISC_INC;
	if   (p & PRIORITY_INC) 
		ret += PRI_INC;
	if   (p & PRIORITY_DEC) 
		ret += PRI_DEC;

	// Move these later
	if   (p & PRIORITY_TOP_EFFECT) 
		ret += PRI_TOP_EFFECT;
	if   (p & PRIORITY_TOP_INTERFACE) 
		ret += PRI_TOP_INTERFACE;

	return ret;

} 

