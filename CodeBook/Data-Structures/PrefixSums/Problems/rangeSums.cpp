/*
SPOJ RANGESUM

Operation 1 : Op1( l, r )
You are given 2 integers l and r. ( 1 <= l <= r <= current size of the array ). 
You need to return the sum of all the elements with indices between l and r ( both inclusive )

Operation 2 : Op2( x )
You are given a single integer x ( |x| <= 109 ). Add this element to the beginning of the array. 
After this operation, x will now become a1, the old a1 will now become a2, and so on. 
The size of the array will increase by 1.
*/

/*
    Solution:
        reverse the array, then adding elements with operation 2 is just appending elements to the end.
        We can update prefix sums in O(1) this way. 
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long
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

    void add(int val) {
        prefix.push_back(prefix.back() + val);
    }
};

#undef int
int main() {
#define int long long

    int N; cin >> N;
    vector<int> v(N);
    for (int i = N - 1; i >= 0; i--) {
        cin >> v[i];
    }

    PrefixSums* pref = new PrefixSums(v);

    int Q; cin >> Q;
    while (Q--) {
        int t; cin >> t;
        if (t == 1) {
            int a, b; cin >> a >> b;
            a = N - a;
            b = N - b;
            cout << pref->query(a, b) << "\n";
        } else {
            int x; cin >> x;
            pref->add(x);
            N++;
        }
    }

    return 0;
}