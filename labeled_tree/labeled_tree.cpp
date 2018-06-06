#include <algorithm>
#include <cassert>
#include "labeled_tree.h"

string LabeledTree::name(){
	return "LabeledTree";
}

bool is_valid(vector <int> const & v){
	auto n = (int) (v.size ());
	if(n == 0) return false;
	for(int i = 2; i < n; i++)
		if(v[i] > n || v[i] < 1) return false;
	if(v[0] || (n > 0 && v[1])) return false;
	return true;
}

int64_t LabeledTree::total(int n){
	if(n < 0) return INT64_MAX;
	return ndeg(n, n - 2);
}


vector <vector <int> > LabeledTree::generate_all(int n){
	if(total(n) == INT64_MAX || n == 0){
		vector <vector <int>> res (0);
		return res;
	}
	vector <vector <int>> res;
	vector <int> v (n);
	v[0] = 0; v[1] = 0;
	for(int i = 2; i < n; i++) v[i] = 1;
	res.push_back(v);
	while(1){
		int i = n - 1;
		while(v[i] == n){
			v[i] = 1;
			i--;
		}

		if(i < 2) break;
		v[i]++;
		res.push_back(v);
	}

	return res;
}

bool LabeledTree::is_valid(vector <int> const & v){
	return ::is_valid (v);
}

int64_t LabeledTree::number_by_object(vector <int> const & v){
	auto n = (int) (v.size ());
	if(n == 0) return v[1];

	int64_t res = 0;
	int64_t m = 1;
	for(int i = n - 1; i > 1; i--){
		if((v[i] - 1) && ( (m > INT64_MAX / (v[i] - 1)) || (res > INT64_MAX - (v[i] - 1) * m) ) ) return INT64_MAX;
		res += (v[i] - 1) * m;
		if(m > INT64_MAX / n) m = INT64_MAX;
		else m *= n;
	}

	return res;
}

vector <int> LabeledTree::object_by_number(int n, int64_t k){
	if(k < 0 || k >= total(n) || n <= 0){
		vector <int> v(0);
		return v;
	}

	vector <int> v(n);
	v[0] = 0;
	if(n > 1) v[1] = 0;

	int i = n - 1;
	while(i > 1){
		v[i] = (k % n + 1);
		k = (k - k % n) / n;
		i--;
	}

	return v;
}

bool LabeledTree::prev(vector <int> & v){
	auto n = (int) (v.size ());
	int i = n - 1;
	while(v[i] == 1){
		v[i] = n;
		i--;
	}

	if(i >= 2) v[i]--;
	return i >= 2;
}

bool LabeledTree::next(vector <int> & v){
	auto n = (int) (v.size ());
	int i = n - 1;
	while(v[i] == n){
		v[i] = 1;
		i--;
	}

	if(i >= 2) v[i]++;
	return i >= 2;
}

int64_t LabeledTree::ndeg(int n, int deg){
	if(n < 0) return INT64_MAX;
	if(deg == 0) return 1;
	if(n == 1) return 1;
	if(n == 0) return 0;
	int64_t _ndeg = ndeg(n, deg / 2);
	if((_ndeg > sqrt(INT64_MAX) && !(deg % 2)) || (_ndeg * sqrt(n) > sqrt(INT64_MAX))) return INT64_MAX;
	if(deg % 2) return n * _ndeg * _ndeg;
	return _ndeg * _ndeg;
}


LabeledTree::~LabeledTree(){
}
