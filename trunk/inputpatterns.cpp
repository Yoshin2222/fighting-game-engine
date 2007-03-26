#include "inputpatterns.hpp"

InputPatterns::InputPatterns()
{
	m_patterns = new Command*[NUM_PATTERNS];

	/* Pattern definitions */
	//QCF A
	Command* qcfa = new Command[5];
	qcfa[0] = DIR_D;
	qcfa[1] = DIR_DF;
	qcfa[2] = DIR_F;
	qcfa[3] = CMD_A;
	qcfa[4] = CMD_TERM;
	m_patterns[IP_QCF_A] = qcfa;


	//QCF B
	Command* qcfb = new Command[5];
	qcfb[0] = DIR_D;
	qcfb[1] = DIR_DF;
	qcfb[2] = DIR_F;
	qcfb[3] = CMD_B;
	qcfb[4] = CMD_TERM;
	m_patterns[IP_QCF_B] = qcfb;

	//QCF C
	Command* qcfc = new Command[5];
	qcfc[0] = DIR_D;
	qcfc[1] = DIR_DF;
	qcfc[2] = DIR_F;
	qcfc[3] = CMD_C;
	qcfc[4] = CMD_TERM;
	m_patterns[IP_QCF_C] = qcfc;

	//QCF QCF C
	Command* qcfqcfa = new Command[8];
	qcfqcfa[0] = DIR_D;
	qcfqcfa[1] = DIR_DF;
	qcfqcfa[2] = DIR_F;
	qcfqcfa[3] = DIR_D;
	qcfqcfa[4] = DIR_DF;
	qcfqcfa[5] = DIR_F;
	qcfqcfa[6] = CMD_A;
	qcfqcfa[7] = CMD_TERM;
	m_patterns[IP_QCF_QCF_A] = qcfqcfa;

	//DP A
	Command* dpa = new Command[5];
	dpa[0] = DIR_F;
	dpa[1] = DIR_D;
	dpa[2] = DIR_DF;
	dpa[3] = CMD_A;
	dpa[4] = CMD_TERM;
	m_patterns[IP_DP_A] = dpa;

	//JUNK
	Command* junk = new Command[1];
	junk[0] = CMD_JUNK;		//should never be matched
	m_patterns[IP_JUNK] = junk;
}

InputPatterns::~InputPatterns()
{
}

Command* InputPatterns::getPattern(const InputPattern& p)
{
	return m_patterns[p];
}

Command InputPatterns::getPatternCommand(const InputPattern& p, const int& index)
{
	//TODO: Potential for memory violations
	return m_patterns[p][index];
}