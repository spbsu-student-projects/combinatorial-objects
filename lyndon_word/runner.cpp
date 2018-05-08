// Author: Ivan Kazmenko (gassa@mail.ru)
#include "lyndon_word.h"

int main ()
{
	CombinatorialObject * calculator = new LyndonWord ();
	calculator -> interact ();
	delete calculator;
	return 0;
}
