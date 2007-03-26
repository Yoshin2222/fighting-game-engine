#ifndef CHARMANAGER_H
#define CHARMANAGER_H

#include <string>
#include <vector>
#include <fstream>

#include "character.hpp"

class CharManager
{
public:
	CharManager();
	~CharManager();

	Character* getChar(const std::string& name);
	Character* getCharFromFile(const std::string& filename);
//private:
	Character* m_getRyu();

	//functions for reading a character from an iostream
	void m_readLibrary(std::iostream& in, Character* c);
	void m_readMovelists(std::iostream& in, Character* c);

	std::fstream& m_prepStream(std::fstream& fin, const std::string& filename, const std::string& search);	//searches for a string in a specified file, and returns an fstream just after that string appeared in the file

	Projectile*		m_grabProjectile	(std::iostream& in);
	Move*			m_grabMove			(std::iostream& in);
	Trigger*		m_grabTrigger		(std::iostream& in);
	Condition*		m_grabCondition		(std::iostream& in);
	Action*			m_grabAction		(std::iostream& in);

	std::string& m_getField(std::fstream& fin);
};

#endif	//CHARMANAGER_H