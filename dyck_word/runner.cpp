// Author: Konstantin Chelpanov (chelpkostya@yandex.ru)

#include "dyck_word.h"

{
  CombinatorialObject * calculator = new DyckWord();
	calculator->interact();
	delete calculator;
	return 0;
} 
