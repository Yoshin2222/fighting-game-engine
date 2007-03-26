#include "input.hpp"
#include <SDL/SDL.h>

//Input class
Input::Input()
: cmd(CMD_JUNK), time(0)
{
}

Input::Input(Command c, Type t, int ti, int p)
: cmd(c), inpType(t), time(ti), player(p)
{
}

bool Input::operator==(const Input& i)
{
	return ( this->cmd == i.cmd && this->inpType == i.inpType );
}

Input& Input::operator=(const Input& i)
{
	this->cmd = i.cmd;
	this->inpType = i.inpType;
	this->player = i.player;
	this->time = i.time;

	return *this;
}