// Author: Mikhail Ivanov (ivanovmihail99@gmail.com)
#include "restricted_growth_string.h"

int main ()
{
	CombinatorialObject * calculator = new RestrictedGrowthString ();
	calculator -> interact ();
	delete calculator;
	return 0;
}
