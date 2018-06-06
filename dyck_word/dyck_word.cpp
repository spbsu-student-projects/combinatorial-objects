//Author: Konstantin Chelpanov chelpkostya@yandex.ru
#include <algorithm>
#include <cassert>
#include "dyck_word.h"

string DyckWord::name()
{
      return "DyckWord";
}




struct GenerateHelper
{
      vector <vector <int> > res;
      int n;
      vector <int> cur;

      GenerateHelper (int n) : n (n), cur (n) {}

      void generate_recur(int open, int close)
      {
            if ((open+close == n) && (open==close))
                  {
                        res.push_back (cur);
                        return;
                  }

            cur[open+close]=0;
            if (open<n/2)
            {
                  generate_recur(open+1,close);
            }
            cur[open+close]=1;
            if (open>close)
            {
                  generate_recur(open,close+1);
            }
      }
};

vector <vector<int>>  DyckWord::generate_all(int n)
{
      if (n<0)
      {
            return vector <vector <int> > ();
      }
      GenerateHelper gen (n);
	gen.generate_recur (0,0);
	return gen.res;
}








bool is_valid (vector <int> const & v)
{
      auto n=(int)(v.size());
      int delta=0;
      for (int i=0;i<n;i++)
      {
        if (v[i]==0)
        {
            delta+=1;
        }
        if (v[i]==1)
        {
            delta-=1;
        }
        if (delta<0)
        {
            return false;
        }
    }
    if (delta==0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int64_t DyckWord::total(int n)
{
    return (0 <= n  && n<(int)(f.size())) ? f[n][0] : INT64_MAX;
}

int64_t DyckWord::number_by_object (vector <int> const & v)
{
      auto n=(int)(v.size());
      int d=0;
      int64_t number=0;
      for (int i=0;i<n;i++)
      {
            if (v[i]==0)
            {
                  d+=1;
            }
            else
            {
                  number+=f[n-1-i][d+1];
                  d-=1;
            }
      }
      return number;
}

vector <int> DyckWord::object_by_number (int n, int64_t k)
{
      if (n%2!=0||k>=total(n)||k<0)
      {
            return vector <int> ();
      }
      vector <int> ans(n);
      int d=0;
      for (int i=0; i<n; i++)
      {
            if (f[n-1-i][d+1]>k)
            {
                  ans[i]=0;
                  d++;
            }
            else
            {
                  k-=f[n-1-i][d+1];
                  ans[i]=1;
                  d--;
            }

      }
      return ans;
}

bool DyckWord::next(vector <int> & v)
{
	auto n=(int)(v.size());

	bool unfixed=true;

	int open=0;
	int close=0;
	int k=-1;
	for (int i=n-1;i>=0;--i)
	{
		if (v[i]==0)
		{
			open++;
			if (close>open)
			{
				k=i;
				break;
			}
		}
		else
		{
			close++;
		}
	}

	if (k==-1)
	{
		unfixed=false;
		for (int i=0;i<=open-1;i++)
		{
			v[i]=0;
		}
		for (int i=0;i<=close-1;i++)
		{
			v[i+open]=1;
		}
	}

	else
	{
		v[k]=1;
		for (int i=1;i<=open;i++)
		{
			v[k+i]=0;
		}
		for (int i=1;i<=(close-1);i++)
		{
			v[k+open+i]=1;
		}
	}
	return unfixed;
}

bool DyckWord::prev(vector <int> & v)

{
	auto n=(int)(v.size());

	bool unfixed=true;

	int open=0;
	int close=0;
	int k=-1;
	for (int i=n-1;i>=0;--i)
	{
		if (v[i]==0)
		{
			open++;
		}
		if (v[i]==1)
		{
			close++;
			if (open>0)
			{
				k=i;
				break;
			}
		}
	}
	if (k==-1)
	{
		unfixed=false;
		for (int i=0;i<=open-1;i++)
		{
			v[2*i]=0;
		}
		for (int i=0;i<=close-1;i++)
		{
			v[2*i+1]=1;
		}
	}
	else
	{
		v[k]=0;
		for (int i=1;i<=close-open+1;i++)
		{
			v[k+i]=1;
		}
		v.resize(k+close-open+2);
		for (int i=1;i<=(open-1);i++)
		{
		    v.push_back(0);
		    v.push_back(1);
		}
	}
	return unfixed;
}









bool DyckWord::is_valid(vector <int> const & v)
{
    return ::is_valid(v);
}

DyckWord::~DyckWord()
{
}

vector <vector <int64_t>> init_f()
{

      vector <vector <int64_t>> f(201,vector<int64_t>(101));
      int n;
      int d;
      f[0][0]=1;
      
      for (n=1;n<=100;n++)
           for (d=0;d<=n;d++)
            {
                 if (INT64_MAX-f[n-1][d+1]>((d == 0) ? 0 : f[n-1][d-1]))
                 f[n][d]=f[n-1][d+1] + ((d == 0) ? 0 : f[n-1][d-1]);
                 else
                 f[n][d]=INT64_MAX;
            }
      return f;
}

vector <vector<int64_t>> DyckWord::f = init_f ();
