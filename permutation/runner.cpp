// Author: Pavel Granin (GraninInfo@mail.ru)
#include "permutation.h"

int main ()
{
	CombinatorialObject * calculator = new Permutation ();
	calculator -> interact ();
	delete calculator;
	return 0;
}
