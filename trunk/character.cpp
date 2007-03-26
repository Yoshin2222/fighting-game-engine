#include "character.hpp"

//Character class
Character::Character()
{
	m_inpQ = new std::deque< Input >;
	m_moves = new std::vector< Move* >;

	//set up empty vectors of moves for Movelists
	m_moveLists.resize(ML_SIZE);
	for( int i = 0; i < ML_SIZE; i++ )
	{
		m_moveLists[i] = new std::vector< Move* >;
	}
}

Character::Character(const std::string& name)
//: m_name(name)
{
	m_inpQ = new std::deque< Input >();
//	m_name = name;
	setName(name);

	//set up empty vectors of moves for Movelists
	m_moveLists.resize(ML_SIZE);
	for( int i = 0; i < ML_SIZE; i++ )
	{
		m_moveLists[i] = new std::vector< Move* >;
	}

	//set parent to NULL
//	setParent(NULL);

	//Sort. This is based on InputPattern, such that patterns
	//which should be checked first should be in the beggining.
	//TODO: Using this involves writing a bunch of copy
	//constructors and overloading assignment operators. Seems
	//like too much work and it's not really necessary.
	//sort( m_moves->begin(), m_moves->end() );

	//check to make sure longest inputs are first
	for(unsigned int j = 0; j < m_moveLists.size(); j++)
	{
		m_moves = m_moveLists[j];
		int previousSize = 1000;
		for(unsigned int i = 0; i < m_moves->size(); i++)
		{
			int j = 0;
			InputPattern cp = m_moves->operator [](i)->getPattern();
			for(; m_inpPatterns.getPatternCommand(cp, j) != CMD_TERM; j++) ;
			ASSERT(j <= previousSize);
			previousSize = j;
		}
	}
}

Character::~Character()
{
	delete m_inpQ;
	delete m_moves;
	for( unsigned int i = 0; i < m_moveLists.size(); i++ )
	{
		delete m_moveLists[i];
	}
}

GameObject* Character::clone()
{
	return new Character(*this);
}

void Character::update(Input inp)
{
	//if it's a different player, return
//	if( inp.player != m_player ) return;

	if(m_inpQ->empty() || m_inpQ->back().cmd != inp.cmd) m_inpQ->push_back(inp);
	//TODO: cull like this for now; base on time or something else later
	if(m_inpQ->size() > 50) m_inpQ->pop_front();
	
	int moveToExecute;
	moveToExecute = m_interpretInput();

	//if there is a new move, change the move
	if(moveToExecute != -1)
	{
//		m_cMove = m_moves->operator [](moveToExecute);
		//TODO: This is for testing purposes
//		m_cMove->perform(this);
//		m_cMove->setStartFrame(m_cFrame);
		setMove( m_moves->operator [](moveToExecute) );
		getMove()->setStartFrame(g_frame);
	}
}

void Character::execute()
{
	getMove()->perform(this);

	for(unsigned int i = 0; !m_children.empty() && i < m_children.size(); i++)
	{
		m_children[i]->execute();
	}
}

/*
Pseudocode:
//TODO: Write pseudocode for future reference
*/
int Character::m_interpretInput()
{
	//switch directions
	//TODO: this

	bool executed = false;

	std::deque< Input > *newQ = new std::deque< Input>(), *tempQ = m_inpQ;
	unsigned int move = 0;

	//create an vector to keep track of number of matched inputs
	//vector is needed because InputPattern enum has numbers out of order
	std::map< InputPattern, int >* trackers  = new std::map< InputPattern, int >();
	//init trackers to 0
	for(std::vector< Move* >::iterator i = m_moves->begin(); i != m_moves->end(); i++)	//go through each move and compare Commands
	{
		trackers->operator []( (*i)->getPattern() ) = 0;
	}

	while( !m_inpQ->empty() && !executed )	//while there are inputs to examine and haven't executed a move
	{
		Command cmdTmp = m_inpQ->front().cmd;	//look at the front, which is the oldest input
		newQ->push_back( m_inpQ->front() );	//recreate an identical queue
		m_inpQ->pop_front();

		for(move = 0; move < m_moves->size() && !executed; move++)	//go through each move and compare Commands
		{
			InputPattern cp = m_moves->operator [](move)->getPattern();

			if( cmdTmp == m_inpPatterns.getPatternCommand( cp, trackers->operator [](cp) ) )	//if this is the next Command for the InputPattern we're checking
			{
				(trackers->operator [](cp))++;	//increment the tracker
				if( m_inpPatterns.getPatternCommand( cp, trackers->operator [](cp) ) == CMD_TERM )	//if this was the last Command in an InputPattern
				{
					executed = true;	//the input has been found
				}
			}

			if(executed) break;
		}
	}

	//free memory
	delete trackers;

	if(executed)	//if a move was executed, return that move
	{
		printf("EXECUTED %s on frame %i\n", m_moves->operator [](move)->getName()->c_str(), g_frame );
		newQ->clear();

		m_inpQ = newQ;
		delete tempQ;

		return move;
	}

	m_inpQ = newQ;
	delete tempQ;

	return -1;
}

void Character::draw()
{
}

void Character::setPlayer(unsigned int p)
{
	m_player = p;
}

unsigned int Character::getPlayer() const
{
	return m_player;
}

void Character::addMeter(const Meter m, const int value)
{
	m_meters[m] = value;
}

void Character::setMeter(const Meter m, const int value)
{
	m_meters[m] = value;
}

int Character::getMeter(const Meter m)
{
	return m_meters[m];
}

void Character::addToMovelist(Movelist list, Move* m)
{
	ASSERT( ((int)list) < ML_SIZE );
	m_moveLists[list]->push_back(m);	//add a move to the end of this movelist
}

void Character::setMovelist(Movelist list)
{
	m_moves = m_moveLists[list];		//set the current movelist
}

unsigned int Character::getFrame() const
{
//	return m_cFrame;

	//new version using global frame indicator
	//however, since frame indicator is global, this shouldn't really be used
	ASSERT(false);
	return g_frame;
}

//THIS IS NO LONGER USED
//std::string* Character::getName()
//{
//	return &m_name;
//}
//
//void Character::setParent(Character* obj)
//{
//	m_parent = obj;
//}
//
//Character* Character::getParent() const
//{
//	return m_parent;
//}

void Character::addChild(Projectile* obj)
{
	obj->setParent( this );
	m_children.insert(m_children.end(), obj);
}

//void Character::removeChild(std::string name)
//{
//	m_children.erase("name");
//}

void Character::removeChild(Projectile* obj)
{
	//linear search should be fine, since there won't be too many elements in m_children
	for(unsigned int i = 0; i < m_children.size(); i++)
	{
		if( m_children[i] == obj )
		{
			m_children.erase( &m_children[i] );
		}
	}
}

void Character::addToLibrary(Projectile* obj)
v{
	REQUIRE( ( obj->getName() != NULL ) );			//the Projectile should not be NULL
	REQUIRE( (*(obj->getName()) != "" ) );			//the Projectile should have a name
	REQUIRE( m_library.find( *(obj->getName())) == m_library.end() );	//the Projectile shouldn't already be in the library
	
	m_library[ *(obj->getName()) ] = obj;			//library[name] = obj
}

Projectile* Character::getFromLibrary(const std::string& name)
{
	if( m_library.find( name ) != m_library.end() )
	{
		return m_library[name];
	}
	else
	{
		return NULL;
	}
}

void Character::m_showQ()
{
	std::deque< Input > *newQ = new std::deque< Input>(), *tempQ = m_inpQ;
	
	printf("The deque is: ");

	while(!m_inpQ->empty())
	{

		printf("%i ", m_inpQ->front().cmd);
		newQ->push_back( m_inpQ->front() );
		m_inpQ->pop_front();
	}
	printf("\n");

	m_inpQ = newQ;
	delete tempQ;
}
