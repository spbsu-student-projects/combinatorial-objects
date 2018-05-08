// Author: Ivan Kazmenko (gassa@mail.ru)
#include <algorithm>
#include <cassert>
#include "lyndon_word.h"

string LyndonWord::name ()
{
	return "LyndonWord";
}

bool is_valid (vector <int> const & v)
{
	auto n = (int) (v.size ());
	for (int i = 1; i < n; i++)
	{
		vector <int> checker (n);
		for (int j = 0; j < n; j++)
		{
			checker[(i + j) % n] = v[j];
		}
		if (checker <= v)
		{
			return false;
		}
	}
	return true;
}

int64_t LyndonWord::total (int n)
{
	auto all = generate_all (n);
	return (int64_t) (all.size ());
}

struct GenerateHelper
{
	vector <vector <int> > res;
	int n;
	vector <int> cur;

	GenerateHelper (int n) : n (n), cur (n) {}

	void generate_recur (int k)
	{
		if (k == n)
		{
			if (is_valid (cur))
			{
				res.push_back (cur);
			}
			return;
		}
		cur[k] = 0;
		generate_recur (k + 1);
		cur[k] = 1;
		generate_recur (k + 1);
	}
};

vector <vector <int> > LyndonWord::generate_all (int n)
{
	GenerateHelper gen (n);
	gen.generate_recur (0);
	return gen.res;
}

bool LyndonWord::is_valid (vector <int> const & v)
{
	return ::is_valid (v);
}

int64_t LyndonWord::number_by_object (vector <int> const & v)
{
	auto n = (int) (v.size ());
	auto all = generate_all (n);
	return (int64_t) (std::find (begin (all), end (all), v) - begin (all));
}

vector <int> LyndonWord::object_by_number (int n, int64_t k)
{
	auto all = generate_all (n);
	return all[k];
}

bool LyndonWord::prev (vector <int> & v)
{
	auto n = (int) (v.size ());
	auto k = number_by_object (v);
	if (k == 0)
	{
		return false;
	}
	v = object_by_number (n, k - 1);
	return true;
}

bool LyndonWord::next (vector <int> & v)
{
	auto n = (int) (v.size ());
	auto k = number_by_object (v);
	if (k + 1 == total (n))
	{
		return false;
	}
	v = object_by_number (n, k + 1);
	return true;
}

LyndonWord::~LyndonWord ()
{
}
