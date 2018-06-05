// Author: Victor Migrin (v-v-m12@mail.ru)

#ifndef FACTORADIC_H_
#define FACTORADIC_H_

#include "combinatorial_object.h"

class Factoradic : public CombinatorialObject {
public:
    Factoradic();

    /// total number of objects of length n,
    /// INT64_MAX if negative or overflow
    int64_t total(int n) override;

    /// lexicographically sorted vector of all objects of length n
    /// empty if negative
    vector<vector<int> > generate_all(int n) override;

    /// validity of given object
    bool is_valid(vector<int> const &v) override;

    /// 0-based lexicographical number of given valid object,
    /// undefined if overflow
    int64_t number_by_object(vector<int> const &v) override;

    /// object of length n with given 0-based lexicographical number,
    /// empty if out of bounds
    vector<int> object_by_number(int n, int64_t k) override;

    /// transform valid object to lexicographically previous object,
    /// true if successful, false and last object if was first
    bool prev(vector<int> &v) override;

    /// transform valid object to lexicographically next object,
    /// true if successful, false and first object if was last
    bool next(vector<int> &v);

    string name() override;

    ~Factoradic();

private:
    const size_t MAX_FACT = 20;
    vector<int64_t> f;

    bool check_min(vector<int> &v);

    bool check_max(vector<int> &v);
};

#endif // FACTORADIC_H
