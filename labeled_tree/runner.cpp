#include "labeled_tree.h"

int main ()
{
	CombinatorialObject * calculator = new LabeledTree ();
	calculator -> interact ();
	delete calculator;
	return 0;
}
