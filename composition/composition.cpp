// Author: Semyon Shestakov (06k8@mail.com)
#define _CRT_SECURE_NO_WARNINGS
#include "composition.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

string Composition::name()
{
	return "Composition";
}

vector <int64_t> init_f()
{
	vector <int64_t> f;
	f.push_back(1);
	f.push_back(1);
	while (true)
	{
		int64_t v = f[f.size() - 1] * (2 * (f.size() - 1) + 1) * 2 / (f.size());
		if (f.size() == 32) v = 916312070471295267;
		if (f.size() == 33) v = 3609714217008132870;
		if (v < f[f.size() - 1])  // overflow
		{
			return f;
		}
		f.push_back(v);
	}
}

vector <int64_t> Composition::f = init_f();

int64_t Composition::total(int n)
{
	return (0 <= n && n < (int)(f.size())) ? f[n] : INT64_MAX;
}

/*int64_t Composition::total(int n)
{
	int64_t t;
	t = 1;
	if ((n > 0) && (n < 35))
	{
		for (int i = 1; i < n; i++) t = t * (2 * n - i) / i;
		return t;
	}
	else
		return INT64_MAX;
}*/

vector <vector <int>> Composition::generate_all(int n)
{
	vector <vector <int>> all;
	int64_t i;
	if (n < 1)
		return vector <vector <int>>();
	else
	{
		vector <vector <int>> all(total(n));
		for (i = 0; i < n - 1; i++) all[0].push_back(0);
		all[0].push_back(n);
		for (i = 1; i < all.size(); i++)
		{
			int p, cur;
			all[i] = all[i - 1];
			p = n - 1;
			cur = all[i][p];
			while (cur == 0)
			{
				p--;
				cur = all[i][p];
			}
			cur = all[i][p];
			all[i][p - 1]++;
			while (p < n - 1)
			{
				all[i][p] = 0;
				p++;
			}
			all[i][p] = cur - 1;
		}
		return all;
	}
}

bool Composition::is_valid(vector <int> const& v)
{
	int n = v.size();
	int s = 0;
	for (int i = 0; i < n; i++)
	{
		if ((v[i] < 0) || (v[i] > n))
			return false;
		else s = s + v[i];
	}
	if (s == n) return true;
	else return false;
}


int64_t Composition::number_by_object(vector <int> const & v)
{
	vector <int> k;
	int64_t c = 0;
	if (k == v) return c;
	int n = v.size();
	vector <vector <int>> all(total(n));
	all = generate_all(n);
	while ((all[c] != v) && (c <= INT64_MAX)) c++;
	if (all[c] == v) return c;
	else return INT64_MAX;
}

vector <int> Composition::object_by_number(int n, int64_t k)
{
	if (n == 0) return vector <int>();
	if ((k < 0) || (k >= total(n))) return vector <int>();
	else
	{
		vector <vector <int>> all(total(n));
		all = generate_all(n);
		int64_t c = 0;
		while (c != k) c++;
		return all[c];
	}
}

bool Composition::prev(vector <int> & v)
{
	auto n = (int)(v.size());
	int64_t k = number_by_object(v);
	if (k == 0)
	{
		v = object_by_number(n, total(n) - 1);
		return false;
	}
	v = object_by_number(n, k - 1);
	return true;
}

bool Composition::next(vector <int> & v)
{
	auto n = (int)(v.size());
	auto k = number_by_object(v);
	if (k + 1 == total(n))
	{
		v = object_by_number(n, 0);
		return false;
	}
	v = object_by_number(n, k + 1);
	return true;
}

Composition::~Composition() {}
