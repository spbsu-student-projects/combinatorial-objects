#ifndef LABELED_TREE_H_
#define LABELED_TREE_H_
#include "combinatorial_object.h"
class LabeledTree : public CombinatorialObject
{
	static int64_t ndeg (int n, int deg);
public:
	/// total number of objects of length n
	/// INT64_MAX if negative or overflow
	int64_t total (int n);

	/// lexicographically sorted vector of all objects of length n
	/// empty if negative or overflow
	vector <vector <int> > generate_all (int n);

	/// validity of given object
	bool is_valid (vector <int> const & v);

	/// 0-based lexicographical number of given valid object,
	/// INT64_MAX if overflow
	int64_t number_by_object (vector <int> const & v);

	/// object of length n with given 0-based lexicographical number,
	/// empty if out of bounds
	vector <int> object_by_number (int n, int64_t k);

	/// transform valid object to lexicographically previous object,
	/// true if successful, false and last if was first
	bool prev (vector <int> & v);

	/// transform valid object to lexicographically next object,
	/// true if successful, false and first if was last
	bool next (vector <int> & v);

	/// name of combinatorial object
	string name ();

	/// destructor
	~LabeledTree ();
};
#endif // LABELED_TREE_H_
