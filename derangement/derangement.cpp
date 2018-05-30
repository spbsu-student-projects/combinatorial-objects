// Author: Ivan Kazmenko (gassa@mail.ru)
#include <cassert>
#include "derangement.h"

string Derangement::name ()
{
	return "Derangement";
}

int64_t Derangement::total (int n)
{
	return (n < 0) ? 0 : generate_all (n).size ();
}

struct GenerateHelper
{
	vector <vector <int> > res;
	int n;
	vector <bool> used;
	vector <int> cur;

	GenerateHelper (int n) : n (n), used (n + 1), cur (n) {}

	void generate_recur (int k)
	{
		if (k == n)
		{
			res.push_back (cur);
			return;
		}
		cur[k] = 0;
		for (int value = 1; value <= n; value++)
		{
			if (value != k + 1 && !used[value])
			{
				used[value] = true;
				cur[k] = value;
				generate_recur (k + 1);
				used[value] = false;
			}
		}
	}
};

vector <vector <int> > Derangement::generate_all (int n)
{
	if (n < 0)
	{
		return vector <vector <int> > ();
	}
	GenerateHelper gen (n);
	gen.generate_recur (0);
	return gen.res;
}

bool Derangement::is_valid (vector <int> const & v)
{
	auto n = (int) (v.size ());
	vector <bool> used (n + 1);
	for (int i = 0; i < n; i++)
	{
		if (v[i] < 1 || v[i] > n || used[v[i]] || v[i] == i + 1)
		{
			return false;
		}
		used[v[i]] = true;
	}
	return true;
}

int64_t Derangement::number_by_object (vector <int> const & v)
{
	auto n = (int) (v.size ());
	auto all = generate_all (n);
	for (int i = 0; i < (int) (all.size ()); i++)
	{
		if (v == all[i])
			return i;
	}
	return -1;
}

vector <int> Derangement::object_by_number (int n, int64_t k)
{
	auto all = generate_all (n);
	return all[(int) (k)];
}

bool Derangement::prev (vector <int> & v)
{
	auto k = number_by_object (v);
	auto n = (int) (v.size ());
	k -= 1;
	bool res = (k >= 0);
	if (!res) k += total (n);
	auto all = generate_all (n);
	v = all[(int) (k)];
	return res;
}

bool Derangement::next (vector <int> & v)
{
	auto k = number_by_object (v);
	auto n = (int) (v.size ());
	k += 1;
	bool res = (k < total (n));
	if (!res) k -= total (n);
	auto all = generate_all (n);
	v = all[(int) (k)];
	return res;
}

Derangement::~Derangement ()
{
}
