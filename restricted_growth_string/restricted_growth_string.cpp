// Author: Mikhail Ivanov (ivanovmihail99@gmail.com)
#define _CRT_SECURE_NO_WARNINGS
#include "restricted_growth_string.h"
#include <algorithm>
#include <iostream>
using namespace std;

string RestrictedGrowthString::name()
{
	return "RestrictedGrowthString";
}

int64_t RestrictedGrowthString::total(int n)
{
	return (0 <= n && n < (int)(d.size())) ? d[n][0] : INT64_MAX;
}

void fill_all(int n, int m, vector<int>& t, vector<vector<int>>& all)
{
	if (n == 0)
		all.push_back(t);
	else
	{
		int mm = m + 2;
		for (int i = 0; i < mm; ++i)
		{
			t.push_back(i);
			fill_all(n - 1, max(m, t.back()), t, all);
			t.pop_back();
		}
	}
}

vector<vector<int>> RestrictedGrowthString::generate_all(int n)
{
	vector<vector<int>> all;
	vector<int> t;
	if (total(n) < INT32_MAX)
		fill_all(n, -1, t, all);
	return all;
}

bool RestrictedGrowthString::is_valid(vector<int> const& v)
{
	int n = v.size();
	int m = -1;
	for (int i = 0; i < n; ++i)
	{
		if ((v[i] < 0) || (v[i] > m + 1))
			return false;
		else if (v[i] > m)
			m = v[i];
	}
	return true;
}

bool cautious_addition(int64_t a, int64_t b, int64_t& c)
{
	c = a + b;
	return c >= a;
}

bool cautious_multiplication(int64_t a, int64_t b, int64_t& c)
{
	c = a * b;
	return (b == 0) || (((c / b) == a) && ((c % b) == 0));
}

vector<vector<int64_t>> initialize_d()
{
	const int initMAX = 1000002;
	vector<vector<int64_t>> d(1, vector<int64_t>(initMAX, 1));
	int i = 0;
	while (d.back().size())
	{
		++i;
		bool cautious = true;
		d.push_back(vector<int64_t>());
		for (int j = 0; cautious; ++j)
		{
			int64_t temp = 0;
			if (cautious = (((((int)d.size()) > i - 1) && (((int)d[i - 1].size()) >= (j + 2)) && cautious_multiplication(d[i - 1][j], j, temp)) && cautious_addition(temp, d[i - 1][j + 1], temp)))
				d[i].push_back(temp);
		}
	}
	while (d.back().size() == 0)
		d.pop_back();
	return d;
}

int64_t RestrictedGrowthString::number_by_object(vector<int> const& v)
{
	int m = -1, n = v.size();
	bool cautious = true;
	int64_t ans = 0;
	for (int i = 0; cautious && (i < n); ++i)
	{
		int64_t temp = 0;
		cautious = ((v[i] == 0) || ((((int)d.size()) > n - i - 1) && (((int)d[n - i - 1].size()) > (m + 1)) && cautious_multiplication(d[n - i - 1][m + 1], v[i], temp))) &&
			cautious_addition(temp, ans, ans);
		m = max(m, v[i]);
	}
	if (cautious)
		return ans;
	else
		return INT64_MAX;
}

vector<int> RestrictedGrowthString::object_by_number(int n, int64_t k)
{
	if ((total(n) <= k) || (k < 0))
		return vector<int>();
	vector<int> ans;
	int m = -1;
	for (int i = 0; i < n; ++i)
	{
		if ((((int)d.size()) > (n - i - 1)) && (((int)d[n - i - 1].size()) > (m + 1)))
		{
			ans.push_back(std::min(k / d[n - i - 1][m + 1], ((int64_t)m + 1)));
			k -= d[n - i - 1][m + 1] * ans.back();
		}
		else
			ans.push_back(0);
		m = max(m, ans.back());
	}
	return ans;
}

bool RestrictedGrowthString::prev(vector<int>& v)
{
	int p = -1, pm = -1, m = -1, n = v.size();
	for (int i = 0; i < n; ++i)
	{
		if (v[i])
		{
			p = i;
			pm = m;
		}
		m = max(m, v[i]);
	}
	if (p == -1)
	{
		for (int i = 0; i < n; ++i)
			v[i] = i;
		return false;
	}
	else
	{
		--v[p];
		pm -= p;
		for (int i = p + 1; i < n; ++i)
			v[i] = pm + i;
		return true;
	}
	return false;
}

bool RestrictedGrowthString::next(vector<int>& v)
{
	int p = -1, m = -1, n = v.size();
	for (int i = 0; i < n; ++i)
	{
		if (v[i] <= m)
			p = i;
		m = max(m, v[i]);
	}
	if (p == -1)
	{
		v = vector<int>(n, 0);
		return false;
	}
	else
	{
		++v[p];
		for (int i = p + 1; i < n; ++i)
			v[i] = 0;
		return true;
	}
}

vector<vector<int64_t>> RestrictedGrowthString::d = initialize_d();

RestrictedGrowthString::~RestrictedGrowthString(){}
