//Author: Matvei Zhukov (matzhukov2000@gmail.com)
#include <algorithm>
#include <cassert>
#include <cmath>
#include "partition.h"

string Partition::name()
{
	return "Partition";
}

bool is_valid(vector <int> const & v)
{
	auto n = (int)(v.size());
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		if (i > 0)
		{
			if (v[i] > v[i - 1])
			{
				return false;
			}
		}
		sum = sum + v[i];
	}
	if (sum != n)
	{
		return false;
	}
	return true;
}

int64_t Partition::total(int n)
{
	int k = f.size();
	return (0 <= n && n < k) ? f[n] : INT64_MAX;
}

vector <int> nextel(vector <int> v)
{
	auto k = (int)(v.size());
	int m;
	bool unfixed = true;
	vector <int> ans = v;
	int res = 0;
	for (int i = 0; i < k; i++)
	{
		if (unfixed)
		{
			res = res + ans[i];
		}
		if (!unfixed)
		{
			if (res >= m)
			{
				ans[i] = m;
				res = res - m;
			}
			else
			{
				ans[i] = res;
				res = 0;
			}
		}
		if (i < k - 1)
		{
			if ((ans[i] > 1 && ans[i + 1] <= 1) && unfixed)
			{
				ans[i] = ans[i] - 1;
				m = ans[i];
				unfixed = false;
				res = res - 1;
				res = k - res;
			}
		}
	}
	return ans;
}

vector <int> prevel(vector <int> v)
{
	auto k = (int)(v.size());
	int m = 0;
	vector <int> ans = v;
	for (int i = 1; i < k-1; i++)
	{
		if (ans[i] < ans[i - 1] && (ans[i] != 0 && ans[i + 1] != 0))
		{
			m = i;
		}
	}
	int res = 0;
	for (int i = 0; i <= m; i++)
	{
		res = res + ans[i];
	}
	res++;
	ans[m]++;
	res = k - res;
	int r = k - m - 1;
	int filler = res / r;
	if (filler*r != res)
	{
		filler++;
	}
	for (int i = m + 1; i < k; i++)
	{
		if (res > filler)
		{
			ans[i] = filler;
			res = res - filler;
		}
		else
		{
			ans[i] = res;
			res = 0;
		}
	}
	return ans;
}

vector <vector <int> > Partition::generate_all(int n)
{
	vector < vector <int> > all;
	if (n < 0)
	{
		return all;
	}
	if (n == 0)
	{
		vector<int> kek(0);
		all.push_back(kek);
		return all;
	}
	else
	{
		size_t size = n;
		vector <int> cur(size);
		cur[0] = n;
		vector <int> end(size);
		for (int i = 0; i < n; i++)
		{
			end[i] = 1;
		}
		while (cur != end)
		{
			all.push_back(end);
			end = prevel(end);
		}
		all.push_back(cur);
		return all;
	}
}

bool Partition::is_valid(vector <int> const & v)
{
	return ::is_valid(v);
}

int64_t Partition::number_by_object(vector <int> const & v)
{
	auto n = (int)(v.size());
	auto all = generate_all(n);
	return (int64_t)(std::find(begin(all), end(all), v) - begin(all));
}

vector <int> Partition::object_by_number(int n, int64_t k)
{
	auto all = generate_all(n);
	if (k<0 || k>=all.size())
	{
		vector <int> kek;
		return kek;
	}
	return all[int(k)]; 
}

bool Partition::prev(vector <int> & v)
{
	auto k = (int)(v.size());
	if (k == 0)
	{
		return false;
	}
	else
	{
		size_t size = k;
		vector <int> first(size);
		for (int i = 0; i < k; i++)
		{
			first[i] = 1;
		}
		if (v == first)
		{
			return false;
		}
		v = nextel(v);
		return true;
	}
}

bool Partition::next(vector <int> & v)
{
	auto n = (int)(v.size());
	if (n == 0)
	{
		return false;
	}
	else if (v[0] == n)
	{
		return false;
	}
	v = prevel(v);
	return true;
}

Partition::~Partition()
{
}

vector <uint64_t> init_f()
{
	vector <uint64_t> f;
	f.push_back(1);
	while (true)
	{
		int s = f.size();
		uint64_t res = 0;
		for (int q = 1; (3 * q*q - q) / 2 <= s; q++)
		{
			int a = s - (3 * q*q - q) / 2;
			int b = s - (3 * q*q + q) / 2;
			uint64_t j1 = f[a];
			uint64_t j2;
			if (b >= 0)
			{
				j2 = f[b];
			}
			else
			{
				j2 = 0;
			}
			uint64_t bla = int(pow(-1, q + 1)*(j1 + j2));
			res = res + bla;
		}
		if (res < f[f.size() - 1] || res > INT64_MAX)  // overflow
		{
			return f;
		}
		f.push_back(res);
	}
}

vector <uint64_t> Partition::f = init_f();