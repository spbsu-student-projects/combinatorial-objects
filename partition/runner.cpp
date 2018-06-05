// Author: Matvei Zhukov (matzhukov2000@gmail.com)
#include "partition.h"

int main()
{
	CombinatorialObject * calculator = new Partition();
	calculator->interact();
	delete calculator;
	return 0;
}
