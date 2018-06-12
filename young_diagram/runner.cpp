// Author: Dmitry Yartsev (jarcev.v.2017@list.ru)
#include "young_diagram.h"

int main ()
{
	CombinatorialObject * calculator = new YoungDiagram ();
	calculator -> interact ();
	delete calculator;
	return 0;
}
