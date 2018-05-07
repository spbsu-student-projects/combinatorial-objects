// Author: Ivan Kazmenko (gassa@mail.ru)
#include "runner.h"

int main (void)
{
	CombinatorialObject * calculator = getCombinatorialObject ();
	calculator -> interact ();
	delete calculator;
	return 0;
}
