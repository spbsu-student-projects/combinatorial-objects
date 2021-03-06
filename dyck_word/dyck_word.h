//Author: Konstantin Chelpanov chelpkostya@yandex.ru
#ifndef DYCK_WORD_H_INCLUDED
#define DYCK_WORD_H_INCLUDED
#include "combinatorial_object.h"

class DyckWord: public CombinatorialObject
{
	static vector <vector<int64_t>> f;
public:
	/// total number of Dyck words of length n,
	/// INT64_MAX if negative or odd or overflow
	int64_t total (int n);

	/// lexicographically sorted vector of all Dyck words of length n
	/// empty if negative or odd
	vector<vector<int>> generate_all(int n);

	/// validity of given object
	bool is_valid (vector <int> const & v);

	/// 0-based lexicographical number of given valid object,
	/// undefined if overflow
	int64_t number_by_object (vector <int> const & v);

	/// object of length n with given 0-based lexicographical number,
	/// empty if out of bounds or if n is odd
	vector <int> object_by_number (int n, int64_t k);

	/// transform valid object to lexicographically previous object,
	/// true if successful, false and last object if was first
	bool prev (vector <int> & v);

	/// transform valid object to lexicographically next object,
	/// true if successful, false and first object if was last
	bool next (vector <int> & v);

	/// name of combinatorial object
	string name();

    /// destructor
	~DyckWord();

};


#endif // DYCK_WORD_H_INCLUDED
