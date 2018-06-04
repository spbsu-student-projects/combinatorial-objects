// Author: Nikita Karagodin (nikitus20@gmail.com)
#include "bit_vector.h"

int main ()
{
	CombinatorialObject * calculator = new BitVector ();
	calculator -> interact ();
	delete calculator;
	return 0;
}
