//Author: Matvei Zhukov (matzhukov2000@gmail.com)
#include <algorithm>
#include <cassert>
#include <cmath>
#include "partition.h"

string Partition::name()
{
	return "PartitionNumber";
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

bool maxi = true;

int mini;

vector <int64_t> tot;

int64_t Partition::total(int n)
{
	if (n < 0)
	{
		return 0;
	}
	if (maxi)
	{
		mini = n;
		maxi = false;
		tot.resize(n + 10);
		tot[0] = 1;
	}
	if (tot[n] != 0)
	{
		return tot[n];
	}
	else
	{

		int64_t res = 0;
		for (int q = 1; (3 * q*q - q) / 2 <= n; q++)
		{
			int a = n - (3 * q*q - q) / 2;
			int b = n - (3 * q*q + q) / 2;
			int64_t j1;
			int64_t j2;
			if (tot[a] != 0)
			{
				j1 = tot[a];
			}
			else
			{
				j1 = total(a);
				tot[a] = j1;
			}
			if (b >= 0)
			{
				if (tot[b] != 0)
				{
					j2 = tot[b];
				}
				else
				{
					j2 = total(b);
					tot[b] = j2;
				}
			}
			else
			{
				j2 = 0;
			}
			res = res + pow(-1,q+1)*(j1+j2);
		}
		if (mini == n)
		{
			maxi = true;
		}
		return res;
	}
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
			if (ans[i] > 1 & ans[i + 1] <= 1 & unfixed)
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
	bool unfixed = true;
	vector <int> ans = v;
	for (int i = 1; i < k-1; i++)
	{
		if (ans[i] < ans[i - 1] & ans[i] != 0 & ans[i + 1] != 0)
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
	return all[k]; 
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
