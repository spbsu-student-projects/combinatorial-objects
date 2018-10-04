// Author: Matvei Zhukov (matzhukov2000@gmail.com)
#ifndef PARTITION_H_
#define PARTITION_H_
#include "combinatorial_object.h"

using std::pair;
using std::make_pair;

class Partition : public CombinatorialObject
{
	static vector <uint64_t> f;  // number of partitions
	static vector<vector<uint64_t>> h;  //number of partitons with parts smaller than k and n < 405
public:

	/// total number of objects of length n,
	/// INT64_MAX if negative or overflow
	int64_t total(int n);

	/// lexicographically sorted vector of all objects of length n
	/// empty if negative
	vector<vector<int>> generate_all(int n);

	/// validity of given object
	bool is_valid(vector<int> const& v);

	/// 0-based lexicographical number of given valid object
	/// undefined if overflow
	int64_t number_by_object(vector<int> const& v);

	/// object of length n with given 0-based lexicographical number,
	/// empty if out of bounds
	vector<int> object_by_number(int n, int64_t k);

	/// transform valid object to lexicographically previous object,
	/// true if successful, false and first if was first
	bool prev(vector<int>& v);

	/// transform valid object to lexicographically next object,
	/// true if successful, false and last if was last
	bool next(vector<int>& v);

	/// name of combinatorial object
	string name();

	/// destructor
	~Partition();

	///number of partitons with parts smaller than k
	uint64_t hbig(pair<int, int> p); 
};
#endif // PARTITION_H_
