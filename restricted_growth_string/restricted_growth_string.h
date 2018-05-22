// Author: Mikhail Ivanov (ivanovmihail99@gmail.com)
#ifndef RESTRICTED_GROWTH_STRING_H_
#define RESTRICTED_GROWTH_STRING_H_
#include "combinatorial_object.h"
class RestrictedGrowthString : public CombinatorialObject
{
	// number of ways to finish object with first (n - i) elements fixed with maximum equal to (j - 1) (or -infinity in case of j == 0)
	// d[i][0] equals number of objects of length i
	static vector<vector<int64_t>> d;
public:  

	/// total number of objects of length n,
	/// INT64_MAX if negative or overflow
	int64_t total(int n);

	/// lexicographically sorted vector of all objects of length n
	/// empty if negative
	vector<vector<int>> generate_all(int n);

	/// validity of given object
	bool is_valid(vector<int> const& v);

	/// 0-based lexicographical number of given valid object,
	/// INT64_MAX if overflow
	int64_t number_by_object(vector<int> const& v);

	/// object of length n with given 0-based lexicographical number,
	/// empty if out of bounds
	vector<int> object_by_number(int n, int64_t k);

	/// transform valid object to lexicographically previous object,
	/// true if successful, false and last object if was first
	bool prev(vector<int>& v);

	/// transform valid object to lexicographically next object,
	/// true if successful, false and first object if was last
	bool next(vector<int>& v);

	/// name of combinatorial object
	string name();

	/// destructor
	~RestrictedGrowthString();
};
#endif // RESTRICTED_GROWTH_STRING_H_
