// Author: Ivan Kazmenko (gassa@mail.ru)
#include <cassert>
#include "combinatorial_object.h"

vector <int64_t> init_f (void)
{
	vector <int64_t> f;
	f.push_back (1);
	f.push_back (2);
	while (true)
	{
		int64_t v = f[f.size () - 1] + f[f.size () - 2];
		if (v < f[f.size () - 1])  // overflow
		{
			return f;
		}
		f.push_back (v);
	}
}

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
};

int64_t FibonacciString::total (int n)
{
	return (0 <= n && n < (int) (f.size ())) ? f[n] : INT64_MAX;
}

struct GenerateHelper
{
	vector <vector <int> > res;
	int n;
	vector <int> cur;

	GenerateHelper (int n) : n (n), cur (vector <int> (n)) {}

	void generate_recur (int k)
	{
		if (k == n)
		{
			res.push_back (cur);
			return;
		}
		cur[k] = 0;
		generate_recur (k + 1);
		if (k == 0 || cur[k - 1] == 0)
		{
			cur[k] = 1;
			generate_recur (k + 1);
		}
	}
};

vector <vector <int> > FibonacciString::generate_all (int n)
{
	GenerateHelper gen (n);
	gen.generate_recur (0);
	return gen.res;
}

int64_t FibonacciString::number_by_object (vector <int> const & v)
{
	auto n = (int) (v.size ());
	int64_t res = 0;
	for (int i = 0; i < n; i++)
	{
		if (v[i] == 1)
		{
			res += total (n - i - 1);
		}
	}
	return res;
}

vector <int> FibonacciString::object_by_number (int n, int64_t k)
{
	vector <int> res;
	if (k < 0 || total (n) <= k)
	{
		return vector <int> ();
	}
	for (int i = n - 1; i >= 0; i--)
	{
		if (k >= total (i))
		{
			k -= total (i);
			res.push_back (1);
		}
		else
		{
			res.push_back (0);
		}
	}
	assert (k == 0);
	return res;
}

bool FibonacciString::prev (vector <int> & v)
{
	auto n = (int) (v.size ());
	auto k = n - 1;
	while (k >= 0 && v[k] == 0)
	{
		k -= 1;
	}
	for (auto i = k + 1; i < n; i++)
	{
		v[i] = (i - k) & 1;
	}
	if (k >= 0)
	{
		v[k] = 0;
	}
	return (k >= 0);
}

bool FibonacciString::next (vector <int> & v)
{
	auto n = (int) (v.size ());
	auto k = n - 1;
	while (k >= 0 && !(v[k] == 0 && (k == 0 || v[k - 1] == 0)))
	{
		k -= 1;
	}
	for (auto i = k + 1; i < n; i++)
	{
		v[i] = 0;
	}
	if (k >= 0)
	{
		v[k] = 1;
	}
	return (k >= 0);
}

vector <int64_t> FibonacciString::f = init_f ();

int main (void)
{
	FibonacciString calculator;
	calculator.interact ();
	return 0;
}
