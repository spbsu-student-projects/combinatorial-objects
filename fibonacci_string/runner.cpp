// Author: Ivan Kazmenko (gassa@mail.ru)
#include "fibonacci_string.h"

int main ()
{
	CombinatorialObject * calculator = new FibonacciString ();
	calculator -> interact ();
	delete calculator;
	return 0;
}
