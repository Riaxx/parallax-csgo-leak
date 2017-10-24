#include "main.h"
#include "Misc.h"

IsRdyFn IsRdy;


const char *Misc::setStrRight(std::string txt, unsigned int val)
{
	txt.insert(txt.length(), val - txt.length(), ' ');

	return txt.c_str();
}


