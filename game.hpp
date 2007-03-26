#ifndef GAME_H
#define GAME_H

#include <map>
#include <string>

#include "graphics.hpp"
#include "inputhandler.hpp"
#include "character.hpp"
#include "charmanager.hpp"
#include "timer.hpp"

extern unsigned int g_frame;

class Game
{
public:
	Game();
	Game( const std::string& char1, const std::string& char2 );
	//could make this usable for more than 2 players if it seems necessary

	void play();

private:
	InputHandler m_ih;
	ITimer m_t;
	unsigned int m_frame;

	CharManager m_cm;
	std::vector< Character* > m_chars;

//	Graphics m_g;
	//initialize a character's moves
};

#endif	//GAME_H