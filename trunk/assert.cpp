#include "assert.hpp"
#include <iostream>
#include "stdlib.h" // defines abort() 

void assert::aFailed(char *expr, char *file, int line)
{
	/*
	  std::cerr << "Assertion failed: "
	  << expr << ", file "
	  << file << ", line "
	  << line << std::endl;
	*/

#ifdef WIN32

	printf("Assertion failed:\n\t%s in\n%s, line\n%i\n\n", expr, file, line);

#endif

	std::cerr << "Assertion failed: "
		  << expr << " in "
		  << file << ", line "
		  << line << std::endl;

	OPTIONALLY_ABORT;
}
