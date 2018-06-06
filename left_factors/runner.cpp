// Author: Olga Badazhkova (olgabadazhkova@mail.ru)
#include "left_factors.h"

int main ()
{
	CombinatorialObject * calculator = new LeftFactors ();
	calculator -> interact ();
	delete calculator;
	return 0;
}
