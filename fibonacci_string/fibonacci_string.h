// Author: Ivan Kazmenko (gassa@mail.ru)
#ifndef __FIBONACC_STRING_H__
#define __FIBONACC_STRING_H__
#include "combinatorial_object.h"
class FibonacciString : public CombinatorialObject
{
	static vector <int64_t> f;  // number of Fibonacci strings

public:
	int64_t total (int n);
	vector <vector <int> > generate_all (int n);
	int64_t number_by_object (vector <int> const & v);
	vector <int> object_by_number (int n, int64_t k);
	bool prev (vector <int> & v);
	bool next (vector <int> & v);
	~FibonacciString ();
};
#endif // __FIBONACC_STRING_H__
