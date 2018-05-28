// Author: Ivan Kazmenko (gassa@mail.ru)
#include "derangement.h"

int main ()
{
	CombinatorialObject * calculator = new Derangement ();
	calculator -> interact ();
	delete calculator;
	return 0;
}
