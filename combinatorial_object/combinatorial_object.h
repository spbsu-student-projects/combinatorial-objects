// Author: Ivan Kazmenko (gassa@mail.ru)
#ifndef COMBINATORIAL_OBJECT_H_
#define COMBINATORIAL_OBJECT_H_
#include <cstdint>
#include <iostream>
#include <vector>

using std::string;
using std::vector;
using std::istream;
using std::ostream;
using std::cin;
using std::cout;

class CombinatorialObject
{
public:
	/// total number of objects of length n,
	/// undefined if negative or overflow
	virtual int64_t total (int n) = 0;

	/// lexicographically sorted vector of all objects of length n
	/// undefined if negative
	virtual vector <vector <int> > generate_all (int n) = 0;

	/// validity of given object
	virtual bool is_valid (vector <int> const & v) = 0;

	/// 0-based lexicographical number of given valid object,
	/// undefined if overflow
	virtual int64_t number_by_object (vector <int> const & v) = 0;

	/// object of length n with given 0-based lexicographical number,
	/// undefined if out of bounds
	virtual vector <int> object_by_number (int n, int64_t k) = 0;

	/// transform valid object to lexicographically previous object,
	/// true if successful, false and undefined state if was first
	virtual bool prev (vector <int> & v) = 0;

	/// transform valid object to lexicographically next object,
	/// true if successful, false and undefined state if was last
	virtual bool next (vector <int> & v) = 0;

	/// check integrity for objects of length n
	void check (int n);

	/// read n vector elements from in_stream, separated by whitespace
	vector <int> input (int n, istream & in_stream = cin);

	/// write space-separated vector elements and a newline to out_stream
	void print (vector <int> const & v, ostream & out_stream = cout);

	/// interact with in_stream and out_stream
	void interact (istream & in_stream = cin, ostream & out_stream = cout);

	/// name of combinatorial object
	virtual string name () = 0;

	/// virtual destructor
	virtual ~CombinatorialObject ();
};
#endif // COMBINATORIAL_OBJECT_H_
