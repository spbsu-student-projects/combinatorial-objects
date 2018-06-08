// Author: Babenko Mikhail (misha-babenko@yandex.ru)
#include "delannoy_path.h"

int main()
{
	CombinatorialObject * calculator = new DelannoyPath();
	calculator->interact();
	delete calculator;
	return 0;
}
