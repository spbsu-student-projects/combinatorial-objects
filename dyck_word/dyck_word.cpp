#include <algorithm>
#include <cassert>
#include "dyck_word.h"

string DyckWord::name()
{
      return "DyckWord";
}

bool is_valid (vector <int> const & v)
{
      auto n=(int)(v.size());
      int delta=0;
      for (int i=0;i<n;i++)
      {
        if (v[i]==1)
        {
            delta+=1;
        }
        if (v[i]==0)
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
    return (0 <= n  && n<(int)(d.size())) ? d[0][n] : INT64_MAX;
}

bool DyckWord::is_valid(vector <int> const & v)
{
    return ::is_valid(v);
}

DyckWord::~DyckWord()
{
}
