// Author: Dmitry Yartsev (jarcev.v.2017@list.ru)
#include "young_diagram.h"
#include "combinatorial_object.h"

int main ()
{
	CombinatorialObject * calculator;
	calculator = new CombinatorialObject();
	calculator -> CombinatorialObject::interact ();
	delete calculator;
	return 0;
}
