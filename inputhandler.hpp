#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <queue>
#include <vector>
#include <map>
#include <SDL/SDL.h>

#include "input.hpp"
#include "inputpatterns.hpp"

class InputHandler
{
public:
	InputHandler();
	//Initialize joysticks, maybe do other things
	~InputHandler();

	std::vector< Input >* getInput();
	//If there is more input, sets inp to next input in queue and returns true.
	//Otherwise returns false.

	void keyBind(SDL_Event event, Command cmd, int player);
	void joyBind(SDL_Event event, Command cmd, int player);
	//bind events to commands
private:
	std::queue< Input > m_inputQueue;

	//keyboard bindings for each player
	std::vector< std::map<Command, Uint8> > m_keyBindsVec;
	//joystick bindings for each player
	std::vector< std::map<Uint8, Command> > m_joyBtnBindsVec;	//button binds
	std::vector< std::map<Uint8, Command> > m_joyHatBindsVec;	//hat binds
	std::vector< std::map<Sint16, Command> > m_joyAxisBindsVec;	//axis binds

	//joysticks
	SDL_Joystick **joysticks;

	void m_getKeyBinds( std::vector< Input >* inpVec );
	void m_getJoyBinds( std::vector< Input >* inpVec );

	void m_addInput( std::vector< Input >* inpVec, Command c, int player);
};

#endif //INPUT_HANDLER_H