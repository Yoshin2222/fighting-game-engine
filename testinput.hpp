#ifndef TESTINPUT_H
#define TESTINPUT_H

//#include "inputhandler.hpp"
#include "assert.hpp"



//Things to test:

//International keyboards
//Different types of gamepads (possibly buy & return the next day)
//Joysticks that use jhat instead of jaxis

//Assumes SDL has been initialized, video mode has been set.

//Note:
//For apparent reasons, this test requires user input
//To run test, enter on the keyboard, in this order,
//making sure to release a key before pressing the next:
//z x c (up) (right) (down) (left) q
//if joystick is installed, do this with player 1 joystick:
//button 1, button 2, button 3, (up) (right) (down) (left), button 1
void inputHandlerTests()
{
/*	InputHandler ih;
	Input inp;

	//test with default bindings
	//D
	inp.cmd = CMD_JUNK;
	while(inp.cmd == CMD_JUNK) ih.getInput(inp);
	ASSERT(inp.cmd == CMD_D);
	ASSERT(inp.player == 0);
	ASSERT(inp.inpType == T_PRESS);

	inp.cmd = CMD_JUNK;
	while(inp.cmd == CMD_JUNK) ih.getInput(inp);
	ASSERT(inp.cmd == CMD_D);
	ASSERT(inp.player == 0);
	ASSERT(inp.inpType == T_RELEASE);

	//E
	inp.cmd = CMD_JUNK;
	while(inp.cmd == CMD_JUNK) ih.getInput(inp);
	ASSERT(inp.cmd == CMD_E);
	ASSERT(inp.player == 0);
	ASSERT(inp.inpType == T_PRESS);

	inp.cmd = CMD_JUNK;
	while(inp.cmd == CMD_JUNK) ih.getInput(inp);
	ASSERT(inp.cmd == CMD_E);
	ASSERT(inp.player == 0);
	ASSERT(inp.inpType == T_RELEASE);

	//F
	inp.cmd = CMD_JUNK;
	while(inp.cmd == CMD_JUNK) ih.getInput(inp);
	ASSERT(inp.cmd == CMD_F);
	ASSERT(inp.player == 0);
	ASSERT(inp.inpType == T_PRESS);

	inp.cmd = CMD_JUNK;
	while(inp.cmd == CMD_JUNK) ih.getInput(inp);
	ASSERT(inp.cmd == CMD_F);
	ASSERT(inp.player == 0);
	ASSERT(inp.inpType == T_RELEASE);


	//up
	inp.cmd = CMD_JUNK;
	while(inp.cmd == CMD_JUNK) ih.getInput(inp);
	ASSERT(inp.cmd == DIR_U);
	ASSERT(inp.player == 0);
	ASSERT(inp.inpType == T_PRESS);

	inp.cmd = CMD_JUNK;
	while(inp.cmd == CMD_JUNK) ih.getInput(inp);
	ASSERT(inp.cmd == DIR_U);
	ASSERT(inp.player == 0);
	ASSERT(inp.inpType == T_RELEASE);

	//right/fwd
	inp.cmd = CMD_JUNK;
	while(inp.cmd == CMD_JUNK) ih.getInput(inp);
	ASSERT(inp.cmd == DIR_F);
	ASSERT(inp.player == 0);
	ASSERT(inp.inpType == T_PRESS);

	inp.cmd = CMD_JUNK;
	while(inp.cmd == CMD_JUNK) ih.getInput(inp);
	ASSERT(inp.cmd == DIR_F);
	ASSERT(inp.player == 0);
	ASSERT(inp.inpType == T_RELEASE);

	//down
	inp.cmd = CMD_JUNK;
	while(inp.cmd == CMD_JUNK) ih.getInput(inp);
	ASSERT(inp.cmd == DIR_D);
	ASSERT(inp.player == 0);
	ASSERT(inp.inpType == T_PRESS);

	inp.cmd = CMD_JUNK;
	while(inp.cmd == CMD_JUNK) ih.getInput(inp);
	ASSERT(inp.cmd == DIR_D);
	ASSERT(inp.player == 0);
	ASSERT(inp.inpType == T_RELEASE);

	//left/back
	inp.cmd = CMD_JUNK;
	while(inp.cmd == CMD_JUNK) ih.getInput(inp);
	ASSERT(inp.cmd == DIR_B);
	ASSERT(inp.player == 0);
	ASSERT(inp.inpType == T_PRESS);

	inp.cmd = CMD_JUNK;
	while(inp.cmd == CMD_JUNK) ih.getInput(inp);
	ASSERT(inp.cmd == DIR_B);
	ASSERT(inp.player == 0);
	ASSERT(inp.inpType == T_RELEASE);

	SDL_Event* e1 = new SDL_Event();
	e1->type = SDL_KEYDOWN;
	e1->key.keysym.sym = SDLK_q;
	SDL_Event* e2 = new SDL_Event();
	e2->type = SDL_KEYUP;
	e2->key.keysym.sym = SDLK_q;

	ih.keyBind(*e1, CMD_A, 0);	
	//A with new binding
	inp.cmd = CMD_JUNK;
	while(inp.cmd == CMD_JUNK) ih.getInput(inp);
	ASSERT(inp.cmd == CMD_A);
	ASSERT(inp.player == 0);
	ASSERT(inp.inpType == T_PRESS);

	inp.cmd = CMD_JUNK;
	while(inp.cmd == CMD_JUNK) ih.getInput(inp);
	ASSERT(inp.cmd == CMD_A);
	ASSERT(inp.player == 0);
	ASSERT(inp.inpType == T_RELEASE);

	if(SDL_NumJoysticks() > 0)
	{
		//test with default bindings
		//D
		inp.cmd = CMD_JUNK;
		while(inp.cmd == CMD_JUNK) ih.getInput(inp);
		ASSERT(inp.cmd == CMD_A);
		ASSERT(inp.player == 0);
		ASSERT(inp.inpType == T_PRESS);

		inp.cmd = CMD_JUNK;
		while(inp.cmd == CMD_JUNK) ih.getInput(inp);
		ASSERT(inp.cmd == CMD_A);
		ASSERT(inp.player == 0);
		ASSERT(inp.inpType == T_RELEASE);

		//E
		inp.cmd = CMD_JUNK;
		while(inp.cmd == CMD_JUNK) ih.getInput(inp);
		ASSERT(inp.cmd == CMD_B);
		ASSERT(inp.player == 0);
		ASSERT(inp.inpType == T_PRESS);

		inp.cmd = CMD_JUNK;
		while(inp.cmd == CMD_JUNK) ih.getInput(inp);
		ASSERT(inp.cmd == CMD_B);
		ASSERT(inp.player == 0);
		ASSERT(inp.inpType == T_RELEASE);

		//F
		inp.cmd = CMD_JUNK;
		while(inp.cmd == CMD_JUNK) ih.getInput(inp);
		ASSERT(inp.cmd == CMD_C);
		ASSERT(inp.player == 0);
		ASSERT(inp.inpType == T_PRESS);

		inp.cmd = CMD_JUNK;
		while(inp.cmd == CMD_JUNK) ih.getInput(inp);
		ASSERT(inp.cmd == CMD_C);
		ASSERT(inp.player == 0);
		ASSERT(inp.inpType == T_RELEASE);


		//up
		inp.cmd = CMD_JUNK;
		while(inp.cmd == CMD_JUNK) ih.getInput(inp);
		ASSERT(inp.cmd == DIR_U);
		ASSERT(inp.player == 0);
		ASSERT(inp.inpType == T_PRESS);

		inp.cmd = CMD_JUNK;
		while(inp.cmd == CMD_JUNK) ih.getInput(inp);
		ASSERT(inp.cmd == DIR_U);
		ASSERT(inp.player == 0);
		ASSERT(inp.inpType == T_RELEASE);

		//right/fwd
		inp.cmd = CMD_JUNK;
		while(inp.cmd == CMD_JUNK) ih.getInput(inp);
		ASSERT(inp.cmd == DIR_F);
		ASSERT(inp.player == 0);
		ASSERT(inp.inpType == T_PRESS);

		inp.cmd = CMD_JUNK;
		while(inp.cmd == CMD_JUNK) ih.getInput(inp);
		ASSERT(inp.cmd == DIR_F);
		ASSERT(inp.player == 0);
		ASSERT(inp.inpType == T_RELEASE);

		//down
		inp.cmd = CMD_JUNK;
		while(inp.cmd == CMD_JUNK) ih.getInput(inp);
		ASSERT(inp.cmd == DIR_D);
		ASSERT(inp.player == 0);
		ASSERT(inp.inpType == T_PRESS);

		inp.cmd = CMD_JUNK;
		while(inp.cmd == CMD_JUNK) ih.getInput(inp);
		ASSERT(inp.cmd == DIR_D);
		ASSERT(inp.player == 0);
		ASSERT(inp.inpType == T_RELEASE);

		//left/back
		inp.cmd = CMD_JUNK;
		while(inp.cmd == CMD_JUNK) ih.getInput(inp);
		ASSERT(inp.cmd == DIR_B);
		ASSERT(inp.player == 0);
		ASSERT(inp.inpType == T_PRESS);

		inp.cmd = CMD_JUNK;
		while(inp.cmd == CMD_JUNK) ih.getInput(inp);
		ASSERT(inp.cmd == DIR_B);
		ASSERT(inp.player == 0);
		ASSERT(inp.inpType == T_RELEASE);

		SDL_Event* e3 = new SDL_Event();
		e3->type = SDL_JOYBUTTONDOWN;
		e3->jbutton.button = 1;

		ih.joyBind(*e1, CMD_A, 0);	
		//A with new binding
		inp.cmd = CMD_JUNK;
		while(inp.cmd == CMD_JUNK) ih.getInput(inp);
		ASSERT(inp.cmd == CMD_A);
		ASSERT(inp.player == 0);
		ASSERT(inp.inpType == T_PRESS);

		inp.cmd = CMD_JUNK;
		while(inp.cmd == CMD_JUNK) ih.getInput(inp);
		ASSERT(inp.cmd == CMD_A);
		ASSERT(inp.player == 0);
		ASSERT(inp.inpType == T_RELEASE);
	}*/
}
#endif // TESTINPUT_H
