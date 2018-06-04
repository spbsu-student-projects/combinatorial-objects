// Author: Nikita Karagodin (nikitus20@gmail.com)
#define _CRT_SECURE_NO_WARNINGS
#include "bit_vector.h"
#include <algorithm>
#include <iostream>
using namespace std;

string BitVector::name()
{
	return "BitVector";
}

int64_t BitVector::total(int n)
{
	if ((n>-1)&&(n<63))
        return 1ll << n ;
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




vector<vector<int>> BitVector::generate_all(int n)
{
	vector<vector<int>> all(1ll << n);
	if (n < 0)
	{
		return vector <vector <int> > ();
	}
	else
	    if (n==0)
	        return  vector<vector<int> > (1, vector<int>(0));
        else
        {
            for(int i=0; i<n; i++)
                all[0].push_back(0);
            for(int i=1;i< (1ll << n); i++)
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

bool BitVector::is_valid(vector<int> const& v)
{
	int n = v.size();
	for (int i = 0; i < n; i++)
	{
		if ((v[i] < 0) || (v[i] > 1))
			return false;
	}
	return true;
}






int64_t BitVector::number_by_object(vector<int> const& v)
{
	int n=v.size();
	int ans=0;
	for(int  i=0; i<n; i++)
        if(v[i]==1)
        {
            if(n-1-1>=63)
                return INT64_MAX;
            else
                ans=ans+ (1ll << (n-i-1));
        }

	return ans;
}

vector<int> BitVector::object_by_number(int n, int64_t k)
{
    int j=0;
	if((k<0)||(k>((1ll << n) - 1)))
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

bool BitVector::prev(vector<int>& v)
{
       return reduce_1_to_ith_position(v.size()-1,v);
}

bool BitVector::next(vector<int>& v)
{
       return add_1_to_ith_position(v.size()-1,v);

}


BitVector::~BitVector(){}
