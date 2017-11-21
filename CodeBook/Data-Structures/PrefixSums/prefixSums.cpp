#include <bits/stdc++.h>
using namespace std;

class PrefixSums {
private:
    vector<int> v;
    vector<int> prefix;
public:
    PrefixSums(vector<int> v) : v(v) {
        prefix.resize(v.size());
        prefix[0] = v[0];
        for (int i = 1; i < v.size(); i++) {
            prefix[i] = prefix[i - 1] + v[i];
        }
    }

    int query(int a, int b) {
        if (b == 0) return prefix[a];
        return prefix[a] - prefix[b - 1];
    }
};