//Author: Matvei Zhukov (matzhukov2000@gmail.com)

#include <algorithm>
#include <cassert>
#include <cmath>
#include "partition.h"
#include <map>

using namespace std;

map <pair<int, int>, uint64_t> mp;

static vector <uint64_t> init_f()
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
			uint64_t bla = j1 + j2;
			if (q % 2 == 1)
			{
				res = res + bla;
			}
			else
			{
				res = res - bla;
			}
		}
		if (res < f[f.size() - 1] || res > INT64_MAX)  // overflow
		{
			return f;
		}
		f.push_back(res);
	}
}

vector <uint64_t> Partition::f = init_f();

static vector<vector<uint64_t>> init_h() {
	vector<vector<uint64_t>> h;
	vector<uint64_t> h0;
	h0.push_back(1);
	h.push_back(h0);
	int p = 1;
	while (p < 21) {
		for (int i = 0; i < p; i++) {
			for (int j = i + 1; j <= p; j++) {
				h[i].push_back(h[i][i]);
			}
		}
		vector<uint64_t> h1 = h0;
		h1[0] = 0;
		for (int i = 1; i <= p; i++) {
			h1.push_back(h1[i - 1] + h[p - i][i]);
		}
		h.push_back(h1);
		p++;
	}
	return h;
}

vector<vector<uint64_t>> Partition::h = init_h();

uint64_t Partition::hbig(pair<int, int> p) {
	if (p.second > p.first) {
		return hbig(make_pair(p.first, p.first));
	}
	if (p.first < 21) {
		return h[p.first][p.second];
	}
	if (p.second == 0) {
		return 0;
	}
	if (mp[p]) {
		return mp[p];
	}
	uint64_t a = hbig(make_pair(p.first - p.second, p.second));
	uint64_t b = hbig(make_pair(p.first, p.second - 1));
	if ((a == INT64_MAX) || (b == INT64_MAX)) {
		mp[p] = INT64_MAX;
		return INT64_MAX;
	}
	mp[p] = a + b;
	return mp[p];
}

string Partition::name()
{
	return "Partition";
}

int64_t Partition::total(int n)
{
	int k = f.size();
	return (0 <= n && n < k) ? f[n] : INT64_MAX;
}

vector<int> first(int n) {
	vector<int> ans(n);
	for (int i = 0; i < n; i++) {
		ans[i] = 1;
	}
	return ans;
}

vector<int> last(int n) {
	vector<int> ans(n);
	ans[0] = n;
	for (int i = 1; i < n; i++) {
		ans[i] = 0;
	}
	return ans;
}

static vector <int> nextel(vector <int> v)
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

static vector <int> prevel(vector <int> v)
{
	auto k = (int)(v.size());
	int m = 0;
	vector <int> ans = v;
	for (int i = 1; i < k - 1; i++)
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

int64_t Partition::number_by_object(vector <int> const & v)
{
	int n = v.size();
	int k = v[0];
	if ((n == 1) || (k == 1)) {
		return 0;
	}
	if (k == n) {
		if (k >= 406) {
			return INT64_MAX;
		}
		return total(n)-1;
	}
	vector <int> v1(n-k);
	for (int i = 0; i < n - k; i++) {
		v1[i] = v[i + 1];
	}
	uint64_t a = hbig(make_pair(n, k - 1));
	uint64_t b = number_by_object(v1);
	if ((a == INT64_MAX) || (b == INT64_MAX)) {
		return INT64_MAX;
	}
	return a+b;
}

vector <int> Partition::object_by_number(int n, int64_t k)
{
	if ((k < 0) || (k > hbig(make_pair(n, n))-1)) {
		vector <int> kek;
		return kek;
	}
	if (k == 0) {
		vector<int> h(n);
		for (int i = 0; i < n; i++) {
			h[i] = 1;
		}
		return h;
	}
	vector<int> h;
	int left_side = 2; 
	while (k>hbig(make_pair(n,left_side))-1) {
		left_side++;
	}
	if (left_side == n) {
		h.push_back(left_side);
		for (int i = 1; i < n; i++) {
			h.push_back(0);
		}
		return h;
	}
	vector<int> h0;
	for (int i = 0; i < left_side - 1; i++) {
		h0.push_back(0);
	}
	h.push_back(left_side);
	int64_t s = hbig(make_pair(n, left_side - 1));
	vector<int> t = object_by_number(n - left_side, k - s);
	h.insert(h.end(), t.begin(), t.end());
	h.insert(h.end(), h0.begin(), h0.end());
	return h;
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
		if (v[v.size()-1] == 1)
		{
			v = last(k);
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
		v = first(n);
		return false;
	}
	v = prevel(v);
	return true;
}

Partition::~Partition()
{
}
