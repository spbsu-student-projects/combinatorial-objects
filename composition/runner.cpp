// Author: Semyon Shestakov (06k8@mail.ru)
#include "composition.h"

int main ()
{
	CombinatorialObject * calculator = new Composition ();
	calculator -> interact ();
	delete calculator;
	return 0;
}
