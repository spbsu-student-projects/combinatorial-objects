// Author: Babenko Mikhail (misha-babenko@yandex.ru)
#include <cassert>
#include <string>
#include <algorithm>
#include "delannoy_path.h"

int DelannoyPath::max_n = 26;

static int64_t safe_add(int64_t a, int64_t b) 
{
  if (a > 0 && b > INT64_MAX - a)
    return INT64_MAX;
  return a + b;
}

static int64_t safe_mult(int64_t a, int64_t b)
{
  if (a == 0 || b == 0)
    return 0;
  if (a > INT64_MAX / b)
    return INT64_MAX;
  return a * b;
}

static int64_t calc_dnk(int n, int k)
{
  int64_t c1 = 1, c2 = 1, res = 0, p = 1;

  if (n < 0 || k < 0)
    return 0;

  if (n <= DelannoyPath::max_n && k <= DelannoyPath::max_n)
    return DelannoyPath::dnk[n][k];

  for (int i = 0; i <= std::min(n, k); i++)
  {
    res = safe_add(res, safe_mult(c1, safe_mult(c2, p)));
    p = safe_mult(p, 2);
    c1 = safe_mult(c1, (n - i)) / (i + 1);
    c2 = safe_mult(c2, (k - i)) / (i + 1);
  }

  return res;
}

static vector<vector<int64_t>> precalc_dnk( int n )
{
  vector<vector<int64_t>> res(n + 1, vector<int64_t>(n + 1, 0));
  res[0][0] = 1;
  
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= n; j++)
    {
      if (i == 0 && j == 0)
        continue;
      if (i > 0)
        res[i][j] += res[i - 1][j];
      if (j > 0)
        res[i][j] += res[i][j - 1];
      if (i > 0 && j > 0)
        res[i][j] += res[i - 1][j - 1];
    }

  return res;
}

vector<vector<int64_t>> DelannoyPath::dnk = precalc_dnk(DelannoyPath::max_n);

string DelannoyPath::name()
{
  return "DelannoyPath";
}

int64_t DelannoyPath::total(int n)
{
  if (n % 2 == 1)
    return 0;
  if (n == 0)
    return 1;
  if (n / 2 > max_n || n < 0)
    return INT64_MAX;

  return dnk[n / 2][n / 2];
}

static void generate_all_nk(int n, int k, vector<vector<int>> & res, int ind)
{
  if (n == 0 && k == 0)
    return;
  
  if (n >= 1)
  {
    for (int i = 0; i < calc_dnk(n - 1, k); i++)
      res[(int)(ind + i)].push_back(1);
    generate_all_nk(n - 1, k, res, ind);
  }

  if (k >= 1)
  {
    for (int i = 0; i < calc_dnk(n, k - 1); i++)
      res[(int)(ind + calc_dnk(n - 1, k) + i)].push_back(2);
    generate_all_nk(n, k - 1, res, (int)(ind + calc_dnk(n - 1, k)));
  }

  if (n >= 1 && k >= 1)
  {
    for (int i = 0; i < calc_dnk(n - 1, k - 1); i++)
      res[(int)(ind + calc_dnk(n - 1, k) + calc_dnk(n, k - 1) + i)].push_back(3);
    generate_all_nk(n - 1, k - 1, res, (int)(ind + calc_dnk(n - 1, k) + calc_dnk(n, k - 1)));
  }
}

vector<vector<int>> DelannoyPath::generate_all(int n)
{
  if (n % 2 == 1 || n < 0)
    return vector<vector<int>>();

  vector<vector<int>> res((int)total(n));

  generate_all_nk(n / 2, n / 2, res, 0);
  for (auto & i : res)
    while ((int)i.size() < n)
      i.push_back(0);

  return res;
}

bool DelannoyPath::is_valid(vector<int> const& v)
{
  if (v.size() % 2 == 1)
    return false;

  int n = (int)v.size() / 2;
  int cx = 0, cy = 0;

  bool is_tail = false;
  for (int i = 0; i < (int)v.size(); i++)
  {
    if (v[i] == 1)
      cx += 1;
    else if (v[i] == 2)
      cy += 1;
    else if (v[i] == 3)
      cx += 1, cy += 1;
    else if (v[i] == 0)
      is_tail = true;
    else
      return false;

    if (is_tail && v[i] != 0)
      return false;
  }

  if (cx != n || cy != n)
    return false;

  return true;
}

int64_t DelannoyPath::number_by_object(vector<int> const& v)
{
  int cx, cy;
  cx = cy = (int)v.size() / 2;

  int64_t res = 0;
  for (auto & i : v)
  {
    if (i == 1)
    {
      cx--;
    }
    if (i == 2)
    {
      res = safe_add(res, calc_dnk(cx - 1, cy));
      cy--;
    }
    if (i == 3)
    {
      res = safe_add(res, safe_add(calc_dnk(cx - 1, cy), calc_dnk(cx, cy - 1)));
      cx--;
      cy--;
    }
    if (i == 0)
      break;
  }

  return res;
}

vector<int> DelannoyPath::object_by_number(int n, int64_t k)
{
  if (n < 0 || n % 2 == 1 || k >= total(n) || k < 0)
    return vector<int>();

  vector<int> res;
  int cx = 0, cy = 0;

  while (cx != n / 2 || cy != n / 2)
  {
    int64_t d1, d2;

    d1 = calc_dnk(n / 2 - cx - 1, n / 2 - cy);
    if (k < d1)
    {
      res.push_back(1);
      k -= 0;
      cx++;
      continue;
    }
    d2 = calc_dnk(n / 2 - cx, n / 2 - cy - 1);
    if (k < d1 + d2)
    {
      res.push_back(2);
      k -= d1;
      cy++;
      continue;
    }
    res.push_back(3);
    k -= d1 + d2;
    cx++, cy++;
  }

  for (int i = (int)res.size(); i < n; i++)
    res.push_back(0);

  return res;
}

bool DelannoyPath::prev(vector<int>& v)
{
  static int last_zero = 0;

  int n = (int)v.size() / 2;
  int pos = (int)v.size() - 1;
  int cx = n, cy = n;

  if ((int)v.size() > last_zero && v[last_zero] == 0)
    pos = last_zero;

  while (pos >= 0)
  {
    if (v[pos] == 0)
      pos--, last_zero = pos;
    else if (v[pos] == 1)
      pos--, cx--;
    else if (v[pos] == 2)
      if (cx == n)
        pos--, cy--;
      else
        break;
    else
      break;
  }

  if (pos < 0)
  {
    for (int i = 0; i < n; i++)
      v[i] = 3, v[i + n] = 0;
    return false;
  }
  else
  {
    if (v[pos] == 2)
      v[pos] = 1, cy--, cx++;
    else
      v[pos] = 2, cx--;

    for (int i = pos + 1; i < (int)v.size(); i++)
      if (cx != n && cy != n)
        v[i] = 3, cx++, cy++;
      else if (cy != n)
        v[i] = 2, cy++;
      else if (cx != n)
        v[i] = 1, cx++;
      else
        v[i] = 0;
  }
  return true;
}

bool DelannoyPath::next(vector<int>& v)
{
  static int last_zero = 0;

  int n = (int)v.size() / 2;
  int pos = (int)v.size() - 1;
  int cx = n, cy = n;

  if ((int)v.size() > last_zero && v[last_zero] == 0)
    pos = last_zero;
  
  while (pos >= 0)
  {
    if (v[pos] == 0)
      pos--;
    else if (v[pos] == 1)
      if (cy == n)
        pos--, cx--;
      else
        break;
    else if (v[pos] == 2)
      if (cx == n)
        pos--, cy--;
      else
        break;
    else
      pos--, cx--, cy--;
  }

  if (pos < 0)
  {
    for (int i = 0; i < n; i++)
      v[i] = 1, v[i + n] = 2;
    return false;
  }
  else
  {
    if (v[pos] == 1)
      v[pos] = 2, cx--, cy++;
    else
      v[pos] = 3, cx++;
    for (int i = pos + 1; i < (int)v.size(); i++)
      if (cx != n)
        v[i] = 1, cx++;
      else if (cy != n)
        v[i] = 2, cy++;
      else
        v[i] = 0;
  }
  return true;
}

DelannoyPath::~DelannoyPath()
{
}
