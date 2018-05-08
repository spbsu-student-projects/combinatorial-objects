// Author: Ivan Kazmenko (gassa@mail.ru)
#ifndef __LYNDON_WORD_H__
#define __LYNDON_WORD_H__
#include "combinatorial_object.h"
class LyndonWord : public CombinatorialObject
{
public:
	/// total number of objects of length n
	/// undefined if negative or overflow
	int64_t total (int n);

	/// lexicographically sorted vector of all objects of length n
	/// undefined if negative
	vector <vector <int> > generate_all (int n);

	/// validity of given object
	bool is_valid (vector <int> const & v);

	/// 0-based lexicographical number of given object,
	/// undefined if not a valid object or overflow
	int64_t number_by_object (vector <int> const & v);

	/// object of length n with given 0-based lexicographical number,
	/// undefined if out of bounds
	vector <int> object_by_number (int n, int64_t k);

	/// transform to lexicographically previous object,
	/// true if successful, false and undefined state if was first
	bool prev (vector <int> & v);

	/// transform to lexicographically next object,
	/// true if successful, false and undefined state if was last
	bool next (vector <int> & v);

	/// name of combinatorial object
	string name ();

	/// destructor
	~LyndonWord ();
};
#endif // __LYNDON_WORD_H__
