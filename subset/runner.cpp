// Author: Nikita Karagodin (nikitus20@gmail.com)
#include "subset.h"

int main ()
{
	CombinatorialObject * calculator = new Subset ();
	calculator -> interact ();
	delete calculator;
	return 0;
}
