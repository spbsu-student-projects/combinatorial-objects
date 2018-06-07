// Author: Olga Badazhkova (olgabadazhkova@mail.ru)
#include <cassert>
#include "dyck_prefix_sum.h"

string DyckPrefixSum::name ()
{
	return "DyckPrefixSum";
}

int const maxN = 70;

vector <vector <int64_t>> init_f()
{
	vector <vector <int64_t> > c(maxN, vector <int64_t>(maxN, 0));
	for (int i = 0; i < maxN; i++)
	{
		c[i][0] = 1;
		for (int j = 1; j <= i; j++)
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
	}
	return c;
}

vector <vector <int64_t>> DyckPrefixSum::C = init_f();

int64_t DyckPrefixSum::total (int n)
{
	if (n > 0 && n < 68){
		if (n == 1) {
			return 1;
		}
		n--;
	    int k;
	    k = n / 2;
	    int64_t ans = 1;
	   /*or(int i=0;i<k;i++){
	        ans = ans * (n - k + 1 + i) / (1 + i);
	    }*/
		ans = C[n][k];
	    return ans;
	}
	else{
	    if(n == 0){
	    return 0;
	    }
	    else{
	    return INT64_MAX;
	    }
	}
}


bool DyckPrefixSum::is_valid (vector <int> const & v)
{
	auto n = (int) (v.size ());
	if(v[0] != 0){
	    return false;
	}
	for(int i = 0; i < n - 1; i++){
		if(abs(v[i] - v[i + 1]) != 1 || v[i] < 0){
		    return false;
		}
	}
	if(v[n - 1] < 0){
	    return false;
	}
	return true;
}

bool DyckPrefixSum::next (vector <int> & v)
{
	auto n = (int) (v.size ());
    if(v[n - 1] == n - 1){
        return false;
    }
    if(v[n - 1] == v[n - 2] - 1){
        v[n - 1] += 2;
        return true;
    }
    for(int i = n - 2; i > 0; i--){
        if(v[i - 1] - 1 == v[i] && v[i + 1] - 1 == v[i]){
            v[i] += 2;
            for(int j = i + 1; j < n; j++){
                if(v[j - 1] == 0){
                    v[j] = 1;
                }
                else{
                    v[j] = v[j - 1] - 1;
                }
            }
			return true;
        }
    }
	return true;
}

bool DyckPrefixSum::prev (vector <int> & v)
{
	auto n = (int) (v.size ());
	vector <int> w(n);
	w[0] = 0;
	for (int i = 1; i < n; i++) {
	    w[i] = 1 - w[i - 1];
	}
    if(w == v){
        return false;
    }
    if(v[n - 1] - 1 == v[n - 2] && v[n - 1] != 1){
        v[n - 1] -= 2;
        return true;
    }
    for(int i = n - 2; i > 0; i--){
        if(v[i + 1] == v[i - 1] && v[i] > 1){
            v[i] -= 2;
            for(int j = i + 1; j < n; j++){
                if(v[j - 1] == 0){
                    v[j] = 1;
                }
                else{
                    v[j] = v[j - 1] + 1;
                }
            }
	    return true;
        }
        
    }
	return true;
}

vector <vector <int> > DyckPrefixSum::generate_all (int n)
{
	if(n <= 0){
	    return vector <vector <int>> ();
	}
	vector <vector <int>> ans;
	vector <int> v(n);
	v[0] = 0;
	for(int i = 1; i < n; i++){
	    v[i] = 1 - v[i - 1];
	}
	ans.push_back(v);
    while(DyckPrefixSum::next(v)){
        ans.push_back(v);
    }
    return ans;
}

vector <int> DyckPrefixSum::object_by_number (int n, int64_t k)
{
	vector <int> v(n);
	v[0] = 0;
	for(int i = 1; i < n; i++){
	    v[i] = 1 - v[i - 1];
	}
	for(int64_t i = 0; i < k; i++){
	    next(v);
	}
	return v;
}

int64_t DyckPrefixSum::number_by_object (vector <int> const & v)
{
	auto n = (int) (v.size ());
	vector <int> w(n);
	w[0] = 0;
	for (int i = 1; i < n; i++) {
		w[i] = 1 - w[i - 1];
	}
	int64_t ans = 0;
	while (v != w) {
		next(w);
		ans++;
	}
	return ans;
}

DyckPrefixSum::~DyckPrefixSum ()
{
}

