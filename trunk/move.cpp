#include "move.hpp"

//Trigger class
Trigger::Trigger()
{
}

Trigger::Trigger(const Trigger& t)
{
	//for all the actions in the trigger
	for(unsigned int i = 0; i < t.actions.size(); i++)
	{
		actions.insert( actions.end(), t.actions[i]->clone() );
	}

	//for all the conditions in the trigger
	for(unsigned int i = 0; i < t.conditions.size(); i++)
	{
		conditions.insert( conditions.end(), t.conditions[i]->clone() );
	}
}

Trigger::~Trigger()
{
	//for all the actions in the trigger
	for(unsigned int i = 0; i < actions.size(); i++)
	{
		delete actions[i];
	}

	//for all the conditions in the trigger
	for(unsigned int i = 0; i < conditions.size(); i++)
	{
		delete conditions[i];
	}
}

//Move class
Move::Move()
: m_inpPattern (IP_JUNK), m_name("Junk"), m_startFrame(0)
{
//	m_triggers.clear();
}

Move::Move(InputPattern inpPattern, std::string name)
: m_inpPattern (inpPattern), m_name(name), m_startFrame(0)
{
//	m_triggers.clear();
}

Move::Move(Move& m)
//: m_inpPattern( m.getPattern() ), m_name( *(m.getName()) ), m_startFrame( m.getStartFrame() )
{
	if( &m == NULL )	//make a null move
	{
		m_inpPattern	= IP_JUNK;
		m_name			= "Junk";
		m_startFrame	= 0;
		m_triggers.clear();

		return;
	}

	m_inpPattern	=	 m.getPattern();
	m_name			= *( m.getName() );
	m_startFrame	=	 m.getStartFrame();

	for(unsigned int i = 0; m.getTrigger(i) != NULL; i++)	//copy over every trigger from m
	{
		addTrigger( new Trigger( *m.getTrigger(i) ) );
	}
}

Move::~Move()
{
	//TODO: This class probably causes memory leaks
}

void Move::perform(GameObject* obj)
{
	printf("%s,\tf %i\n", m_name.c_str(), g_frame );
	bool execute = true;

	for(unsigned int trg = 0; trg < m_triggers.size(); trg++)	//for every trigger
	{
		for(unsigned int cnd = 0; cnd < m_triggers[trg].conditions.size(); cnd++)	//check the conditions for this trigger
		{
			if( !m_triggers[trg].conditions[cnd]->check() )	//if a condition is not met, don't execute
			{
				execute = false;
				break;
			}
		}

		if(execute)
		{
			for(unsigned int act = 0; act < m_triggers[trg].actions.size(); act++)	//peform every action
			{
				printf("Executed trigger action\n");
				m_triggers[trg].actions[act]->perform();
			}
		}

		execute = true;	//reset execute
	}
}

InputPattern Move::getPattern() const
{
	return m_inpPattern;
}

void Move::addTrigger(Trigger& trg)
{
	m_triggers.insert(m_triggers.end(), trg);
}

void Move::addTrigger(Trigger* trg)
{
	m_triggers.insert(m_triggers.end(), *trg);
}

Trigger* Move::getTrigger(unsigned int index)
{
	if( index >= m_triggers.size() )
		return NULL;

	return &m_triggers[index];
}

void Move::setStartFrame(unsigned int frame)
{
	m_startFrame = frame;
}


unsigned int Move::getStartFrame() const
{
	return m_startFrame;
}


std::string* Move::getName()
{
	return &m_name;
}