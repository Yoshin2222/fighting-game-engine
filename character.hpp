#ifndef CHARACTER_H

#define CHARACTER_H

#include <string>
#include <map>
#include <queue>
#include <vector>
#include <algorithm>	//sort


#include "graphics.hpp"
#include "rectangle.hpp"
#include "pair.hpp"
#include "inputhandler.hpp"
#include "assert.hpp"
#include "move.hpp"
#include "conditions.hpp"
#include "actions.hpp"

//type definitions, etc.
class Condition;
class Character;
class Move;
class Projectile;

typedef Command Direction;

enum Meter
{
	M_HEALTH,
	M_SUPER
};

enum Movelist
{
	ML_STAND,
	ML_JUMP,
	ML_CROUCH
	//NOTE: be sure to update ML_SIZE when adding to enum Movelist
};

const unsigned int ML_SIZE = 3;
extern unsigned int g_frame;

/*
Object:

A basic interface.
*/
class Object
{
public:
	virtual void draw() = 0;				//draw self

	virtual void setName(const std::string& name);		//set name
	virtual std::string* getName();						//get the Object's name
private:
//	unsigned int* m_cFrame;					//the current frame	
	std::string m_name;						//Object's name
};

/*
GameObject:

The interface for things that are part of the game--characters,
projetiles, familiars, etc.
*/

class GameObject : public Object
{
	friend class Projectile;
public:
	/*** Object interface ***/
	virtual void draw() = 0;						//draw self
//	virtual std::string* getName() = 0;				//get the Object's name

	/*** GameObject interface ***/
	virtual void update(Input inp) = 0;				//update based on input
	virtual void execute();							//execute the current move
	virtual GameObject* clone() = 0;				//copy constructor emulation

	virtual void setMove(Move* m);					//set the current move
	virtual Move* getMove( void ) const;			//get the current move

	void setPosition(const Pair& newpos);			//set a new position
	void setPosition(int x, int y);					//set a new position
	void changePosition(const int dx, const int dy); //change position in a direction (fwd, back, down, or up)
	Pair& getPosition();							//get the position

	Direction getDir() const;						//get the direction
	void setDir(const Direction newDir);			//change the direction
	void flipDir();									//reverse the direction

private:
	Move* m_cMove;					//the current move
	Pair m_position;				//the position
	Direction m_dir;				//direction the Projectile is facing. Either fwd or back
};


/*

Projectile spec:
* Must have a parent
* Can destroy itself

*/
class Projectile : public GameObject
{
public:
	/*** Constructors and Destructor ***/
	Projectile();								//default constructor
	Projectile(const std::string& name);		//constructor with name
	Projectile(Projectile& p);			//copy constructor

	/*** Object interface ***/
	virtual void draw();							//draw self
	/*** GameObject interface ***/
	virtual void update(Input inp);					//update based on input
	virtual GameObject* clone();				//copy constructor emulation

	/*** Projectile interface ***/
	void setParent(Character* obj);			//set this Projectile's parent
	Character* getParent() const;			//get this Projectile's parent

	void setHitbox(const Pair& pos, const Pair& size);	//set hitbox based on position and size
	void setHitbox(const Rectangle& hb);				//set hitbox based on a rectangle
	Rectangle& getHitbox();					//get this Projectile's hitbox

private:
	virtual void m_copyMove(Move* m);					//Like setMove, but makes a copy of the move instead of setting a pointer.

	Character* m_parent;			//the parent
	Rectangle m_hitbox;				//the hitbox

	bool m_copyFlag;				//TODO: think of something that doesn't use this
};

class Character : public GameObject
{
public:
	/*** Constructors and Destructor ***/
	Character();
	Character(const std::string& name);
	~Character();

	/*** Object interface ***/
	virtual void draw();								//draw self
//	virtual std::string* getName();						//get the character's name

	/*** GameObject interface ***/
	virtual void update(Input inp);						//update move based on input
	virtual GameObject* clone();						//copy constructor emulation
	virtual void execute();								//execute the current move, and those of children

	/*** Character interface ***/
	virtual void addChild(Projectile* obj);				//add a child object to this character
														//automatically sets parent
	virtual void removeChild(Projectile* obj);			//remove a child by pointer

	void addToLibrary(Projectile* obj);					//add a Projectile to the library
	Projectile* getFromLibrary(const std::string& name);	//get a Projectile by it's name

	void setPlayer(unsigned int p);						//set this character's player number
	unsigned int getPlayer() const;						//get this character's player number

	void addMeter(const Meter m, const int value);		//TODO: What does this do again?
	void setMeter(const Meter m, const int value);		//set a meter to a value
	int getMeter(const Meter m);						//get the value of a meter

	void addToMovelist(Movelist list, Move* m);			//add a move to a movelist
	void setMovelist(Movelist list);					//set the current movelist
//	Movelist getMovelist();								//get the current movelist

	unsigned int getFrame() const;						//get the current frame
														//TODO: should this really be on Character?
private:
	int m_interpretInput( void );
	//Interprets the input in m_inpQ. If is a move to execute,
	//it returns the index of that move in m_inpQ. Other wise,
	//returns -1.
	void m_showQ();
	
//	std::string m_name;

	Character* m_opp;		//The opponent

	Character* m_parent;		//Some Objects have parents. Others are orphans. 

	std::map < std::string, Projectile* > m_library;		//possible children that this character could have
	std::vector < GameObject* > m_children;					//current children of this character
//	std::map < std::string, Object* > m_children;		//Children are usually things like projectiels


	/*** Move stuff ***/
//	Move* m_cMove;
	//The current move in execution.
	std::vector< Move* >* m_moves;
	//This stores a characters moves. For input recognition to
	//work correctly, the moves with longest inputs must be in
	//the beggining of the vector. There is an assertion in the
	//constructor that checks this.

	//std::map< Move*, std::vector< Move* >* > m_moveLists;
	std::vector< std::vector< Move* >* > m_moveLists;
	//A character's movelists. Movelists are collections of moves
	//that a character can perform.

	//Meters. Use std::map because some characters may have 
	//different meters.
	std::map< Meter, int > m_meters;
	
	InputPatterns m_inpPatterns;		//stores input patterns TODO: might want this somewhere else; only need one copy
	std::deque< Input >* m_inpQ;		//Inputs for this character. Newer inputs are towards the front.
	unsigned int m_player;				//this character's player number

	Pair m_position;
	Rectangle m_defHitbox;
	Direction m_dir;				//direction the Projectile is facing. Either fwd or back
};

#endif //CHARACTER_H
