#ifndef INPUTPATTERN_H

#define INPUTPATTERN_H

//#include <vector>
#include "inputhandler.hpp"

struct Input;

enum InputPattern
{
	IP_QCF_A,
	IP_QCF_B,
	IP_QCF_C,
	IP_QCF_QCF_A,
	IP_QCB,
	IP_HCF,
	IP_HCB,
	IP_DP_A,
	IP_RDP,
	IP_TK,
	IP_DASHFWD,
	IP_DASHBACK,

	IP_JUNK
};

#define NUM_PATTERNS 12

//General info:
//This class stores various input patterns for easy access.
//An input pattern is an array of commands. For example, qcf + A
//is the array { DIR_D, DIR_DF, DIR_F, CMD_A, CMD_TERM }. All
//input patterns are terminated by CMD_TERM. To get the entire
//input pattern, use getPattern(IP_QCF_A). To get a specific 
//Command of an input, use getPatternCommand(...). For example,
//to get the second command of qcf + A, use this function call:
//getPatternCommand(IP_QCF_A, 1). 
//
//Using in conjunction with Move:
//An InputPattern is bound to a a Move by the Move constructor.
//That's about all there is to it. 

class InputPatterns
{
public:
	InputPatterns();
	~InputPatterns();

	Command* getPattern(const InputPattern& p);
	Command getPatternCommand(const InputPattern& p, const int& index);
private:
	Command** m_patterns;
};

#endif //INPUTPATTERN_H
