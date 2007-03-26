#ifndef MOVE_H
#define MOVE_H

#include <vector>
#include <string>

#include "assert.hpp"
#include "inputhandler.hpp"
#include "conditions.hpp"
#include "actions.hpp"

class Character;
class Condition;
class Action;

struct Trigger
{
	Trigger();
	Trigger(const Trigger& t);
	int x;	//TODO: For unknown reasons, removing this seems to cause a runtime crash. Not sure why. Feel free to investigate.

	std::vector< Condition* > conditions;
	std::vector< Action* > actions;
};

class Move
{
public:
	Move();
	Move(InputPattern inpPattern, std::string name);
	Move(Move& m);

	void perform(GameObject* obj);
	//For every trigger, checks conditions. If the condition is met,
	//executes every action for that trigger.

	void setStartFrame(unsigned int frame);
	//Set this when a move has just been executed
	unsigned int getStartFrame() const;

	InputPattern getPattern() const;

	void addTrigger(Trigger& trg);				//Adds a trigger to the end of the trigger list.
	void addTrigger(Trigger* trg);				//Adds a trigger to the end of the trigger list.
	Trigger* getTrigger(unsigned int index);	//Get a trigger. If index is out of bounds, returns null.

//	void swapTargetPointers(GameObject* original, GameObject* replacement);
	//This function has pretty limited use: for every trigger with m_obj
	//that points to original, it sets m_obj to point to replacement. 
	//Originally, this was needed for Projectile::Projectile(Projectile& p),
	//but it might be useful for other things as well. This function is
	//also the original reason why Move is a friend of conditions/actions.

	std::string* getName();
private:
	InputPattern m_inpPattern;
	unsigned int m_startFrame;

	std::string m_name;

	std::vector< Trigger > m_triggers;
	//Stores triggers for this move.

//	std::vector< Move* > m_moveList;
//	//TODO: Maybe character should have the move list? Not sure.
//	//Character his movelist now. This should eventually be deleted.
};

#endif	//MOVE_H