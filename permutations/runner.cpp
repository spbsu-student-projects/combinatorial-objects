// Author: Pavel Granin (GraninInfo@mail.ru)
#include "permutations.h"

int main ()
{
	CombinatorialObject * calculator = new Permutations ();
	calculator -> interact ();
	delete calculator;
	return 0;
}
