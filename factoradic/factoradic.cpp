// Author: Victor Migrin (v-v-m12@mail.ru)

#include "factoradic.h"


Factoradic::Factoradic() {
    f.resize(MAX_FACT + 1);
    f[0] = 1;
    for (int i = 1; i <= MAX_FACT; i++) {
        f[i] = f[i - 1] * i;
    }
}

string Factoradic::name() {
    return "Factoradic";
}

int64_t Factoradic::total(int n) {
    return 0 <= n && n < MAX_FACT ? f[n + 1] : INT64_MAX;
}

vector<vector<int> > Factoradic::generate_all(int n) {
    if (total(n) == INT64_MAX)
        return vector<vector<int> >();
    vector<vector<int> > vec(static_cast<uint64_t>(f[n + 1]));
    vec[0] = vector<int>(static_cast<uint32_t>(n));
    for (int i = 1; i < vec.size(); i++) {
        vec[i] = vec[i - 1];
        next(vec[i]);
    }
    return vec;
}

bool Factoradic::is_valid(vector<int> const &v) {
    auto n = v.size();
    for (size_t i = 0; i < v.size(); i++) {
        if (v[n - i - 1] < 0 || v[n - i - 1] > i + 1)
            return false;
    }
    return true;
}

int64_t Factoradic::number_by_object(vector<int> const &v) {
    int64_t n = 0;
    auto m = v.size();
    for (int i = 1; i <= m; i++) {
        auto product = f[i] * v[m - i];
        if (INT64_MAX - product <= n)
            return INT64_MAX;
        n += product;
    }
    return n;
}

vector<int> Factoradic::object_by_number(int n, int64_t k) {
    if (k < 0)
        return vector<int>();
    vector<int> vec(static_cast<uint32_t>(n));
    for (int i = n; i >= 1; i--) {
        if (i <= MAX_FACT && k >= f[i]) {
            vec[n - i] = int(k / f[i]);
            k -= vec[n - i] * f[i];
        }
    }
    if (k != 0)
        return vector<int>();
    return vec;
}

bool Factoradic::check_min(vector<int> &v) {
    int m = static_cast<int>(v.size());
    for (int i = 1; i <= m; i++) {
        if (v[m - i] > 0)
            return false;
    }
    return true;
}

bool Factoradic::prev(vector<int> &v) {
    auto n = v.size();
    if (v.empty())
        return false;
    if (check_min(v)) {
        for (int i = 1; i <= n; i++)
            v[n - i] = i;
        return false;
    }

    int i = 1;
    while (v[n - i] == 0) {
        v[n - i] = i;
        i++;
    }
    v[n - i]--;
    return true;
}

bool Factoradic::check_max(vector<int> &v) {
    int m = static_cast<int>(v.size());
    for (int i = 1; i <= m; i++) {
        if (v[m - i] < i)
            return false;
    }
    return true;
}

bool Factoradic::next(vector<int> &v) {
    auto n = v.size();
    if (v.empty())
        return false;
    if (check_max(v)) {
        v = vector<int>(n, 0);
        return false;
    }

    int i = 1;
    while (v[n - i] == i) {
        v[n - i] = 0;
        i++;
    }
    v[n - i]++;
    return true;
}

Factoradic::~Factoradic() {}
