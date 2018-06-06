// Author: Olga Badazhkova (olgabadazhkova@mail.ru)
#include <cassert>
#include "left_factors.h"

string LeftFactors::name ()
{
	return "LeftFactors";
}

int64_t LeftFactors::total (int n)
{
	if (n > 0 && n < 67){
	    int k;
	    k = n / 2;
	    int ans = 1;
	    for(int i=0;i<k;i++){
	        ans = ans * (n - k + 1 + i) / (1 + i);
	    }
	    return ans;
	}
	else{
	    return INT64_MAX;
	}
}


bool LeftFactors::is_valid (vector <int> const & v)
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

bool LeftFactors::next (vector <int> & v)
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
}

bool LeftFactors::prev (vector <int> & v)
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
        }
        return true;
    }
}

vector <vector <int> > LeftFactors::generate_all (int n)
{
	vector <vector <int>> ans;
	vector <int> v(n);
	v[0] = 0;
	for(int i = 1; i < n; i++){
	    v[i] = 1 - v[i - 1];
	}
	ans.push_back(v);
    while(LeftFactors::next(v)){
        ans.push_back(v);
    }
    return ans;
}

vector <int> LeftFactors::object_by_number (int n, int64_t k)
{
	vector <int> v(n);
	v[0] = 0;
	for(int i = 1; i < n; i++){
	    v[i] = 1 - v[i - 1];
	}
	bool l;
	for(int i = 0; i < k; i++){
	    l = LeftFactors::next(v);
	}
	return v;
}

int64_t LeftFactors::number_by_object (vector <int> const & v)
{
	auto n = (int) (v.size ());
	vector <int> w(n);
	w[0] = 0;
	for (int i = 1; i < n; i++) {
		w[i] = 1 - w[i - 1];
	}
	bool l;
	int ans = 0;
	while (v != w) {
		l = LeftFactors::next(w);
		ans++;
	}
	return ans;
}

LeftFactors::~LeftFactors ()
{
}
