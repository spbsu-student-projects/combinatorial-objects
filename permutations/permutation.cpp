// Author: Pavel Granin (GraninInfo@mail.ru)
#include <cassert>
#include "permutation.h"

string Permutation::name ()
{
	return "Permutations";
}

int64_t Permutation::total (int n)
{
	int i;
	int64_t o;
	if (n > 20) return INT64_MAX;
	if (n < 0) return INT64_MAX;
	o = 1;
	for (i = 1; i < n+1; i++) o = o * i;
	return o;
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
			if (!used[value])
			{
				used[value] = true;
				cur[k] = value;
				generate_recur (k + 1);
				used[value] = false;
			}
		}
	}
};

vector <vector <int> > Permutation::generate_all (int n)
{
	if (n < 0)
	{
		return vector <vector <int> > ();
	}
	GenerateHelper gen (n);
	gen.generate_recur (0);
	return gen.res;
}

bool Permutation::is_valid(vector <int> const & v)
{
	auto n = (int)(v.size());
	vector <bool> used(n + 1);
	for (int i = 0; i < n; i++)
	{
		if (v[i] < 1 || v[i] > n || used[v[i]])
		{
			return false;
		}
		used[v[i]] = true;
	}
	return true;
}

int64_t Permutation::number_by_object (vector <int> const & v)
{
	auto n = (int) (v.size ());
	vector <bool> used(n+1);
	int64_t o = 1;
	int i;
	int64_t o1 = 0;
	for (i = 1; i < n + 1; i++) {
		o = o * i; used[i] = false;
	}
	for (i = 1; i < n + 1; i++)
	{
		used[v[i-1]] = true;
		o = o / (n + 1 - i);
		for (int y = 1; y < v[i - 1]; y++) if (!used[y]) { if (o1 > INT64_MAX - o) { return INT64_MAX; }  o1 = o1 + o; }
	}
	return o1;
}

vector <int> Permutation::object_by_number (int n, int64_t k)
{
	int i, y , t ;
	int64_t o;	
	vector <int> res;
	vector <bool> used(n + 1);
	o = 1;
	for (i = 1; i < n + 1; i++) { o = o * i; used[i] = false; }
	if (k < 0 || k > o-1) return res;
	for (i = 1; i < n + 1; i++)
	{
		o = o / (n + 1 - i);
		t = 1;
		for (y = 1; y < n + 1; y++) if (k >= o) { k = k - o; t++; }
		for (y = 1; y < n + 1; y++) { if (!used[y]) { t = t - 1; if (t == 0) break; } }
		res.push_back(y);
		used[y] = true;
	}
	return res;
}

bool Permutation::prev (vector <int> & v)
{
	int64_t k = number_by_object (v);
	auto n = (int) (v.size ());
	int i;
	int64_t o;
	o = 1;
	for (i = 1; i < n + 1; i++) o = o * i;
	k -= 1;
	if (k == -1) { v = object_by_number(n, o-1); return false; }
		v = object_by_number(n, k); return true;
}

bool Permutation::next (vector <int> & v)
{
	int64_t k = number_by_object (v);
	auto n = (int) (v.size ());
	k += 1;
	int i;
	int64_t o;
	o = 1;
	for (i = 1; i < n + 1; i++) o = o * i;
	if (k == o) { v = object_by_number(n, 0); return false; }
	v = object_by_number(n, k); return true;
}

Permutation::~Permutation ()
{
}
