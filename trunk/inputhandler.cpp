#include "inputhandler.hpp"
#include <SDL/SDL.h>

//InputHandler class

//Initialize default key bindings
InputHandler::InputHandler()
{
	//enable joysticks
    SDL_JoystickEventState(SDL_ENABLE);
	joysticks = new SDL_Joystick* [SDL_NumJoysticks()];

	/* Default Keyboard Bindings */
	std::map< Command, Uint8 >* newKeyBinds = new std::map< Command, Uint8 >();
	m_keyBindsVec.insert( m_keyBindsVec.begin(), *newKeyBinds );

	//player 0
	m_keyBindsVec[0][DIR_U] = SDLK_w;
	m_keyBindsVec[0][DIR_F] = SDLK_d;
	m_keyBindsVec[0][DIR_D] = SDLK_s;
	m_keyBindsVec[0][DIR_B] = SDLK_a;

	m_keyBindsVec[0][CMD_A] = SDLK_r;
	m_keyBindsVec[0][CMD_B] = SDLK_t;
	m_keyBindsVec[0][CMD_C] = SDLK_y;
	m_keyBindsVec[0][CMD_D] = SDLK_f;
	m_keyBindsVec[0][CMD_E] = SDLK_g;
	m_keyBindsVec[0][CMD_F] = SDLK_h;
	m_keyBindsVec[0][CMD_S] = SDLK_j;

	/* Default Joystick Bindings */
	//button binds
	std::map< Uint8, Command >* newJoyBtnBinds = new std::map< Uint8, Command >();
	m_joyBtnBindsVec.insert( m_joyBtnBindsVec.begin(), *newJoyBtnBinds );

	//player 0
	m_joyBtnBindsVec[0][1] = CMD_A;
	m_joyBtnBindsVec[0][2] = CMD_B;
	m_joyBtnBindsVec[0][3] = CMD_C;
	m_joyBtnBindsVec[0][4] = CMD_D;
	m_joyBtnBindsVec[0][5] = CMD_E;
	m_joyBtnBindsVec[0][6] = CMD_F;
	m_joyBtnBindsVec[0][7] = CMD_S;

	//hat binds
	std::map< Uint8, Command >* newJoyHatBinds = new std::map< Uint8, Command >();
	m_joyHatBindsVec.insert( m_joyHatBindsVec.begin(), *newJoyHatBinds );

	//player 0
	m_joyHatBindsVec[0][SDL_HAT_UP]		= DIR_U;
	m_joyHatBindsVec[0][SDL_HAT_RIGHT]	= DIR_F;
	m_joyHatBindsVec[0][SDL_HAT_DOWN]	= DIR_D;
	m_joyHatBindsVec[0][SDL_HAT_LEFT]	= DIR_B;

	//axis binds
	std::map< Sint16, Command >* newJoyAxisBinds = new std::map< Sint16, Command >();
	m_joyAxisBindsVec.insert( m_joyAxisBindsVec.begin(), *newJoyAxisBinds );

	//player 0
	m_joyAxisBindsVec[0][-32768	^ 1] = DIR_U;	//bitwise ^ to distinguish axes
	m_joyAxisBindsVec[0][32767	^ 0] = DIR_F;
	m_joyAxisBindsVec[0][32767	^ 1] = DIR_D;
	m_joyAxisBindsVec[0][-32768	^ 0] = DIR_B;
}

std::vector< Input >* InputHandler::getInput()
{
	std::vector< Input >* rVec = new std::vector< Input >();

	m_getKeyBinds( rVec );
	if( rVec->size() == 1 && rVec->operator[](0).cmd == DIR_N ) //if size is 1, we only added DIR_N
	{
		rVec->clear();	//prevent repetition of DIR_N, not really necessary though
		m_getJoyBinds( rVec );	
	}

	return rVec;
}

void InputHandler::m_getKeyBinds(std::vector< Input >* inpVec)
{
	//put events into array
	SDL_PumpEvents();
	//then grab them
	Uint8* keys;
	keys = SDL_GetKeyState(NULL);

	//get direction
	for(int i = 0; i < m_keyBindsVec.size(); i++ )
	{
		Command cmdTmp = DIR_N;
		//this is in case someone is holding down more than one direction
		cmdTmp = (Command) (	DIR_N |
					(DIR_U * keys[ m_keyBindsVec[i][DIR_U] ]) |
					(DIR_F * keys[ m_keyBindsVec[i][DIR_F] ]) |
					(DIR_D * keys[ m_keyBindsVec[i][DIR_D] ]) |
					(DIR_B * keys[ m_keyBindsVec[i][DIR_B] ]) );

		Input* newInp = new Input(cmdTmp, T_PRESS, 0, i);
		inpVec->push_back( *newInp );
	}

	//get commands
	for(int i = 0; i < m_keyBindsVec.size(); i++)
	{
		for(int c = CMD_A; c <= CMD_S; c++)
		{
			if(keys[ m_keyBindsVec[i][(Command)c] ] == 1)
			{
				Input* newInp = new Input((Command)c, T_PRESS, 0, i);
				inpVec->push_back( *newInp );
			}
		}
	}

	delete []keys;
}

void InputHandler::m_getJoyBinds(std::vector< Input >* inpVec)
{
	Command cmdDir = DIR_N;

	//open joysticks if not opened already
	//TODO: does this actually have to be here? seems like it
	for(int i = 0; i < SDL_NumJoysticks(); i++)
	{
		if(! SDL_JoystickOpened(i) ) joysticks[i] = SDL_JoystickOpen(i);
	}

	for(int i = 0; i < m_joyBtnBindsVec.size() && i < SDL_NumJoysticks(); i++)	//for each player
	{
		//check buttons
		for(int btn = 1; btn <= SDL_JoystickNumButtons( joysticks[i] ); btn++)	//check every button
		{
			if( SDL_JoystickGetButton( joysticks[i], btn) == 1 )	//if it's pressed
			{
				if(m_joyBtnBindsVec[i][btn] >= CMD_A)	//for commands, simply push into vector
				{
					m_addInput(inpVec, m_joyBtnBindsVec[i][btn], i);
				}
				else	//otherwise, modify direction
				{
					cmdDir =  (Command)(cmdDir |  m_joyBtnBindsVec[i][btn]);
				}
			}
		}

		//check the hat
		for(Uint8 dir = SDL_HAT_UP; dir <= SDL_HAT_LEFT; dir *= 2)
		{	
			Command cmdTmp = m_joyHatBindsVec[i][dir & SDL_JoystickGetHat( joysticks[i], 0 ) ];
			if(cmdTmp >= CMD_A)	//for commands, simply push into vector
			{
				m_addInput(inpVec, cmdTmp, i);
			}
			else	//otherwise, modify direction
			{
				cmdDir = (Command)( cmdDir | cmdTmp);
			}
		}

		//check the axes
		for(int axis = 0; axis <= 1; axis++)
		{
//			if( m_joyAxisBindsVec[i][ SDL_JoystickGetAxis(joysticks[i], axis) | axis ] != NULL )
			{
				Command cmdTmp = m_joyAxisBindsVec[i][ SDL_JoystickGetAxis(joysticks[i], axis) ^ axis ];
				if(cmdTmp >= CMD_A)
				{
					m_addInput(inpVec, cmdTmp, i);
				}
				else	//modifiy direction
				{
					cmdDir = (Command)( cmdDir | cmdTmp);
				}
			}
		}
		m_addInput(inpVec, cmdDir, i);
	}
}

//add input to the queue
void InputHandler::m_addInput(std::vector<Input>* inpVec, Command c, int player)
{
	Input* newInp = new Input( c, T_PRESS, 0, player);
	inpVec->push_back( *newInp );
}

InputHandler::~InputHandler()
{
}