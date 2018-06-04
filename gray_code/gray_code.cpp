// Author: Victor Migrin (v-v-m12@mail.ru)

#include "gray_code.h"
#include <algorithm>

typedef unsigned int ui;
typedef unsigned long long ull;

string GrayCode::name() {
    return "GrayCode";
}

int64_t GrayCode::total(int n) {
    return 0 <= n && n < 63 ? (1 << n) : INT64_MAX;
}


vector<int> bin2Vec(int64_t n) {
    vector<int> vec;
    for (; n; n >>= 1)
        vec.push_back(static_cast<int>(n & 1));
    std::reverse(vec.begin(), vec.end());
    return vec;
}

int64_t vec2Bin(vector<int> const & vec) {
    int64_t p = 1, n = 0;
    for (int i = static_cast<int>(vec.size() - 1); i >= 0; i--) {
        auto d = vec[i] * p;
        if (INT64_MAX - d <= n)
            return INT64_MAX;
        n += d;
        p <<= 1;
    }
    return n;
}

vector<vector<int> > GrayCode::generate_all(int n) {
    if (n < 0)
        return vector<vector<int> >();
    auto pow_n = total(n);
    vector<vector<int> > code(static_cast<ull>(pow_n));
    for (int i = 0; i < pow_n; i++) {
        int x = i ^ (i >> 1);
        auto tmp = bin2Vec(x);
        code[i].resize(static_cast<ui>(n));
        for (int j = 0; j < tmp.size(); j++)
            code[i][n - tmp.size() + j] = tmp[j];
    }
    return code;
}

bool GrayCode::is_valid(vector<int> const &v) {
    for (auto it: v) {
        if (it != 0 && it != 1)
            return false;
    }
    return true;
}

int64_t GrayCode::number_by_object(vector<int> const &v) {
    int64_t g = vec2Bin(v), n = 0;
    if (v.size() > 63 && g == INT64_MAX)
        return INT64_MAX;
    for (; g; g >>= 1)
        n ^= g;
    return n;
}

vector<int> GrayCode::object_by_number(int n, int64_t k) {
    int log_k = 0;
    int64_t k1 = k;
    while (k1 > 0) {
        log_k++;
        k1 >>= 1;
    }
    if (log_k > n || k < 0)
        return vector<int>();
    k ^= k >> 1;
    vector<int> vec(static_cast<ui>(n));
    auto tmp = bin2Vec(k);
    for (int j = 0; j < tmp.size(); j++)
        vec[n - tmp.size() + j] = tmp[j];
    return vec;
}

bool GrayCode::prev(vector<int> &v) {
    if (v.empty())
        return false;
    if (v == vector<int>(v.size(), 0)) {
        v = vector<int>(v.size(), 0);
        v[0] = 1;
        return false;
    }
    return true;
}

bool GrayCode::next(vector<int> &v) {
    if (v.empty())
        return false;
    if (v[0] == 1 && vector<int>(v.begin() + 1, v.end()) == vector<int>(v.size() - 1, 0)) {
        v = vector<int>(v.size(), 0);
        return false;
    }
    return true;
}

GrayCode::~GrayCode() {}