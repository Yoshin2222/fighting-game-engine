#ifndef INPUT_H
#define INPUT_H

enum Command
{
	DIR_N = 0,

	DIR_U = 1,
	DIR_F = 2,
	DIR_B = 4,
	DIR_D = 8,

	DIR_UF = 3,
	DIR_DF = 10,
	DIR_DB = 12,
	DIR_UB = 5,

	CMD_A = 16,
	CMD_B,
	CMD_C,
	CMD_D,
	CMD_E,
	CMD_F,
	CMD_S,

	CMD_JUNK,	//something we don't care about

	CMD_TERM	//the last command in an input pattern
};

enum Type
{
	T_PRESS,
	T_RELEASE
};

struct Input
{
	Input();
	Input(Command c, Type t, int ti, int p);

	bool operator==(const Input& i);
	Input& operator=(const Input& i);

	Command cmd;
	Type inpType;	//press or release
	int time;	//probably a frame
	int player;	//which player?
};

#endif // INPUT_H
