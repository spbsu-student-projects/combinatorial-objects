// Author: Dmitry Yartsev (jarcev.v.2017@list.ru)
#include <cassert>
#include "young_diagram.h"

using namespace std;

const int64_t INF = INT64_MAX;
const int MAXN = 68;

string YoungDiagram::name ()
{
	return "YoungDiagram";
}

static vector<vector<int64_t> > init_c ()
{
	vector<vector<int64_t> > c(MAXN);
	for (int i = 0; i < MAXN; i++) c[i].resize(MAXN);
	for (int i = 1; i < MAXN; i++) c[0][i] = 0;
	for (int i = 0; i < MAXN; i++) c[i][0] = 1;
	for (int n = 1; n < MAXN; n++)
        for (int k = 1; k < MAXN; k++)
        {
            c[n][k] = c[n-1][k]+c[n-1][k-1];
        }
    return c;
}

vector<vector <int64_t> > YoungDiagram::c = init_c ();

int64_t YoungDiagram::total (int n)
{
	return (0 <= n && n < MAXN / 2) ? c[2*n][n] : INT64_MAX;
}

bool YoungDiagram::is_valid (vector <int> const & v)
{
	auto n = (int) (v.size ());
	if (v[0] > n || v[0] < 0) return false;
	for (int i = 1; i < n; i++)
	{
		if (v[i] > v[i-1] || v[i] < 0)
		{
			return false;
		}
	}
	return true;
}

int64_t YoungDiagram::number_by_object (vector <int> const & v)
{
	auto n = (int) (v.size ());
	if (n == 0) return 0;
	int64_t res = 0;
	int i = 0;
	while (v[i] > 0 && i < n)
    {
        res += c[n-i+v[i]-1][v[i]-1];
        i++;
    }
	return res;
}

vector <int> YoungDiagram::object_by_number (int n, int64_t k)
{
	vector <int> res(n);
	if (k < 0 || total (n) <= k)
	{
		return vector <int> ();
	}
    int h = n;
	for (int i = 0; i < n; i++)
    {
        while (h > 0 && c[n-i+h-1][h-1] > k) h--;
        res[i] = h;
        k -= (h == 0 ? 0: c[n+h-i-1][h-1]);
    }
	assert (k == 0);
	return res;
}

bool YoungDiagram::prev (vector <int> & v)
{
	auto n = (int) (v.size ());
	if (n == 0) return false;
	int i = n-1;
	while (i > 0 && v[i] == 0) i--;
	if (i == 0 && v[i] == 0)
	if (i == 0 && v[0] == 0)
    {
        for (int j = 0; j < n; j++) v[j] = n;
        return false;
    }
	v[i]--;
	for (int j = i+1; j < n; j++) v[j] = v[i];
	return true;
}

bool YoungDiagram::next (vector <int> & v)
{
	auto n = (int) (v.size ());
	if (n == 0) return false;
	int i = n-1;
	while (i > 0 && v[i] == v[i-1]) i--;
	if (i == 0 && v[0] >= n)
    {
        for (int j = 0; j < n; j++) v[j] = 0;
        return false;
    }
    v[i]++;
    for (int j = i+1; j < n; j++) v[j] = 0;
    return true;
}

vector <vector <int> > YoungDiagram::generate_all (int n)
{
	if (n < 0)
	{
		return vector <vector <int> > ();
	}
	vector<int> cur(n);
	vector<vector<int> > res;
	res.push_back(cur);
	while (next(cur))
    {
        res.push_back(cur);
    }
	return res;
}

YoungDiagram::~YoungDiagram ()
{
}
