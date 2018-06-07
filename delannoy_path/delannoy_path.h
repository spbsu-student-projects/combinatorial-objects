// Author: Babenko Mikhail (misha-babenko@yandex.ru)
#ifndef DELANNOY_PATH_H_
#define DELANNOY_PATH_H_
#include <cstdint>
#include <iostream>
#include <vector>

#include "combinatorial_object.h"

class DelannoyPath : public CombinatorialObject
{
public:
  // maximum size of grid for which paths fit into INT64
  static int max_n;

  // number of dellanoy paths from (0, 0) to (n, k) grid
  static vector<vector<int64_t>> dnk;

  /// total number of objects of length n,
  /// INT64_MAX if negative or overflow
  virtual int64_t total (int n);

  /// lexicographically sorted vector of all objects of length n
  /// empty if negative
  virtual vector <vector <int> > generate_all (int n);

  /// validity of given object
  virtual bool is_valid (vector <int> const & v);

  /// 0-based lexicographical number of given valid object,
  /// INT64_MAX is number is overflow
  virtual int64_t number_by_object (vector <int> const & v);

  /// object of length n with given 0-based lexicographical number,
  /// empty if out of bounds
  virtual vector <int> object_by_number (int n, int64_t k);

  /// transform valid object to lexicographically previous object,
  /// true if successful, false and last state if was first
  virtual bool prev (vector <int> & v);

  /// transform valid object to lexicographically next object,
  /// true if successful, false and first state if was last
  virtual bool next (vector <int> & v);

  /// name of combinatorial object
  virtual string name ();

  /// virtual destructor
  virtual ~DelannoyPath();
};
#endif // DELANNOY_PATH_H_
