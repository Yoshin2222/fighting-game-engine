#ifndef PRIORITY_H
#define PRIORITY_H

//class Character;

typedef unsigned int PriorityFlags;

enum PriorityFlag
{
	PRIORITY_NONE = 0,
	PRIORITY_CHAR = 1,
	PRIORITY_OBJ = 2,
	PRIORITY_EFFECT = 4,
	PRIORITY_INTERFACE = 8,
	PRIORITY_BG = 16,

	PRIORITY_DODGE_FORWARD = 32,
	PRIORITY_ATTACK = 64,
	PRIORITY_DODGE_BACK = 128,
	PRIORITY_REEL = 256,
	PRIORITY_SUPER = 512,
	PRIORITY_SPECIAL = 1024,

	PRIORITY_MISC_DEC = 2048,
	PRIORITY_MISC_INC = 4096,
	PRIORITY_INC = 8192,
	PRIORITY_DEC = 16384,

	// Should put together a script to re-order these later
	PRIORITY_TOP_EFFECT = 32768, 
	PRIORITY_TOP_INTERFACE = 65536 
	
};  // See PriorityHelper somewhere below for values



// This should use a flag system along with Priority Helper
class Priority
{
  public:
	~Priority();
	Priority(const Priority &Priority);
	Priority(PriorityFlags pFlags = PRIORITY_NONE);
	
	Priority& operator+(PriorityFlags pFlags);
	Priority& operator-(PriorityFlags pFlags);
	bool operator<(PriorityFlags pFlags) const;
	bool operator>(PriorityFlags pFlags) const;

	Priority& operator+(const Priority &arg);
	Priority& operator-(const Priority &arg);
	bool operator<(const Priority &arg) const;
	bool operator>(const Priority &arg) const;
	
	
	// This is here because when objects interact, there should be
	// nothing visually separating them.  Don't necessarily have to
	// use or implement though.
//	static Priority& Hitting(Character character);
	
	int getValue() const;
	
  private:
	PriorityFlags p;

	enum PriorityHelper
	{
		PRI_CHAR = 128,
		PRI_OBJ = 256,
		PRI_EFFECT = 512,
		PRI_TOP_EFFECT = 2048, // These go in front of super invincibility etc.
		PRI_INTERFACE = 4096, // These are for meters etc. that always stay in front
		PRI_BG = -8192,
		PRI_TOP_INTERFACE = 16384, // This is for vital interface elements (pause menu, etc.)

		PRI_DODGE_FORWARD = 1024, // like A-groove activation and probably super invincibility
		PRI_ATTACK = 64, // attacks go in front
		PRI_DODGE_BACK = -32, // CvS2-style dodging layer
		PRI_REEL = -16, // reeling characters shouldn't normally be in front
		PRI_SUPER = 8, // for when attacks trade/clash, the super should be more visible
		PRI_SPECIAL = 4, // for when attacks trade/clash, the special should be more visible
		// However, dodging back or not attacking (while the opponent is) will still put you behind
		// unless dodge forward is set (should be used whenever you're invincible for supers and such)

		PRI_MISC_DEC = -2,
		PRI_MISC_INC = 2,
		PRI_INC = 1,
		PRI_DEC = -1
	
	}; // possibly useful for getting general idea of positioning

};

#endif // PRIORITY_H

