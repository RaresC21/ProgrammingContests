#include <bits/stdc++.h>

using namespace std;

string feeOrUpfront(int n, int k, int x, int d, vector <int> p) {
    double fee = 0;
    for (int cur : p) {
        fee += max(k * 1.0, 1.0 * (x * 1.0 / 100.0) * 1.0 * cur);
    }
    
    if (fee > d) return "upfront";
    return "fee";
    
}

int main() {
    int q;
    cin >> q;
    for(int a0 = 0; a0 < q; a0++){
        int n;
        int k;
        int x;
        int d;
        cin >> n >> k >> x >> d;
        vector<int> p(n);
        for(int p_i = 0; p_i < n; p_i++){
	    cin >> p[p_i];
        }
        string result = feeOrUpfront(n, k, x, d, p);
        cout << result << endl;
    }
    return 0;
}
