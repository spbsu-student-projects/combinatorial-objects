// Author: Nikita Karagodin (nikitus20@gmail.com)
#define _CRT_SECURE_NO_WARNINGS
#include "subset.h"
#include <algorithm>
#include <iostream>
using namespace std;

string Subset::name()
{
	return "Subset";
}

int64_t Subset::total(int n)
{
	if ((n>-1)&&(n<63))
        return 1LL << n ;
    else
        return INT64_MAX;
}

bool add_1_to_ith_position(int i, vector<int>& v)
{
    if (i < 0)
        return false;
    if(v[i]==0)
    {
        v[i]=1;
        return true;
    }
    else
    {
        v[i]=0;
        return add_1_to_ith_position(i-1, v);
    }

}



bool reduce_1_to_ith_position(int i, vector<int>& v)
{
    if (i < 0)
        return false;
    if(v[i]==1)
    {
        v[i]=0;
        return true;
    }
    else
    {
        v[i]=1;
        return reduce_1_to_ith_position(i-1, v);
    }
}




vector<vector<int>> Subset::generate_all(int n)
{

	if (n < 0)
	{
		return vector <vector <int> > ();
	}
	vector<vector<int>> all(1LL << n);
	    if (n==0)
	        return  vector<vector<int> > (1, vector<int>(0));
        else
        {
            for(int i=0; i<n; i++)
                all[0].push_back(0);
            for(int i=1;i< (1LL << n); i++)
            {
                all[i]=all[i-1];
                int j=n-1;
                while(all[i][j]==1)
                {
                    all[i][j]=0;
                    j=j-1;
                }
                all[i][j]=1;

            }

            return all;

        }

}

bool Subset::is_valid(vector<int> const& v)
{
	int n = v.size();
	for (int i = 0; i < n; i++)
	{
		if ((v[i] < 0) || (v[i] > 1))
			return false;
	}
	return true;
}






int64_t Subset::number_by_object(vector<int> const& v)
{
	int n=v.size();
	int64_t ans=0;
	for(int  i=0; i<n; i++)
        if(v[i]==1)
        {
            if(n-i-1>=63)
                return INT64_MAX;
            else
                ans=ans+ (1LL << (n-i-1));
        }

	return ans;
}

vector<int> Subset::object_by_number(int n, int64_t k)
{
    int j=0;
	if((k<0)||((n<63)&&(k>((1LL << n) - 1))))
        return vector<int> ();
    vector<int> ans;
    while(k>0)
    {
        ans.push_back(k%2);
        k=k/2;
        j++;
    }
    for(int i=0 ;i<n-j;i++)
        ans.push_back(0);
    reverse(ans.begin(),ans.end());
    return ans;



}

bool Subset::prev(vector<int>& v)
{
       return reduce_1_to_ith_position(v.size()-1,v);
}

bool Subset::next(vector<int>& v)
{
       return add_1_to_ith_position(v.size()-1,v);

}


Subset::~Subset(){}
