// Author: Olga Badazhkova (olgabadazhkova@mail.ru)
#include "dyck_prefix_sum.h"

int main ()
{
	CombinatorialObject * calculator = new DyckPrefixSum ();
	calculator -> interact ();
	delete calculator;
	return 0;
}
