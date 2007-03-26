#include "charmanager.hpp"

CharManager::CharManager()
{
}

CharManager::~CharManager()
{
}

Character* CharManager::getCharFromFile(const std::string& filename)
{
	std::fstream fin;
	Character* newChar = new Character();

	m_readLibrary		(m_prepStream(fin, filename, "Library"),			newChar);
	m_readMovelists		(m_prepStream(fin, filename, "Movelists"),			newChar);

	return newChar;
}

std::fstream& CharManager::m_prepStream(std::fstream& fin, const std::string& filename, const std::string& search)
{
	fin.open(filename.c_str(), std::fstream::in);
	std::string field;

	while( 1 )	//grab fields from the file
	{
		getline(fin, field, '\t');
		printf("[%s]\n", field.c_str() );
		if( field.find(search) == 0 )	//if field contains search string, break
		{
			break;
		}
	}

	return fin;
}

void CharManager::m_readLibrary(std::iostream& in, Character* c)
{
}

void CharManager::m_readMovelists(std::iostream& in, Character* c)
{
}

Projectile* CharManager::m_grabProjectile(std::iostream& in)
{
	return NULL;
}

Character* CharManager::getChar(const std::string& name)
{
	if( name == "Ryu" ) return m_getRyu();
}

Character* CharManager::m_getRyu()
{
//	std::vector< Move* >* moves = new std::vector< Move* >;
	Character* newChar = new Character("Ryu");

	/*** Create library ***/
	Projectile* newObj_Hadoken = new Projectile("Hadoken");
	Move* newObj_Hadoken_Move = new Move(IP_JUNK, "Hadoken's Move");
	/*** Hadoken's move ***/
	//Trigger 1
	{
		Trigger* trg = new Trigger();

		//Conditions
		trg->conditions.insert(trg->conditions.end(),	new Cnd_framesSince(	newObj_Hadoken,	300,		CMP_GTE ) );

		//Actions
		trg->actions.insert(trg->actions.end(),			new Act_removeSelf(		newObj_Hadoken ) );
		newObj_Hadoken_Move->addTrigger(*trg);
	}

	newObj_Hadoken->setMove(newObj_Hadoken_Move);

	Projectile* testProj = new Projectile(*newObj_Hadoken);


	//moves
	Move* newMove_Stand = new Move(IP_JUNK, "Stand");
	Move* newMove_Hadoken = new Move(IP_QCF_A, "Hadoken");

	//move lists
	newChar->addToMovelist(ML_STAND, newMove_Hadoken);
	newChar->addToMovelist(ML_STAND, newMove_Stand);
	newChar->addToMovelist(ML_CROUCH, newMove_Stand);

	/*** Stand ***/
	//Trigger 1
	{
		Trigger* trg = new Trigger();

		//Conditions
		trg->conditions.insert(trg->conditions.end(),	new Cnd_compareMeter(	newChar,	M_HEALTH,		CMP_GT,		0 ) );

		//Actions
		trg->actions.insert(trg->actions.end(),			new Act_modMeter(		newChar,	M_HEALTH,	0 ) );
	}

	/*** Hadoken ***/
	//Trigger 1
	{
		Trigger* trg = new Trigger();
		
		//Conditions
		trg->conditions.insert(trg->conditions.end(),	new Cnd_framesSince(	newChar,	10,		CMP_E ) );
		
		//Actions
		trg->actions.insert(trg->actions.end(),			new Act_modMeter(		newChar,	M_SUPER,	20 ) );
		trg->actions.insert(trg->actions.end(),			new Act_addChild(		newChar,	newObj_Hadoken) );
		newMove_Hadoken->addTrigger(*trg);
	}
	//Triger 2
	{
		Trigger* trg = new Trigger();
		
		//Conditions
		trg->conditions.insert(trg->conditions.end(),	new Cnd_framesSince(	newChar,	20,	CMP_GTE ) );
		
		//Actions
		trg->actions.insert(trg->actions.end(),			new Act_setMove(		newChar,	newMove_Stand ) );
		newMove_Hadoken->addTrigger(*trg);
	}

//	//add the moves
//	moves->insert( moves->end(), newMove_Stand );
//	moves->insert( moves->end(), newMove_Hadoken );

	//initialize meters
	newChar->addMeter(M_HEALTH, 1000);
	newChar->addMeter(M_SUPER, 100);

	newChar->setMove(newMove_Stand);

	newChar->setMovelist(ML_STAND);

	return newChar;
}