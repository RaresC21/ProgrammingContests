// ONLY REASON I AM USING #define int IS BECAUSE TEMPLATE GIVEN DURING
// HACKERRANK CONTEST WAS ALREADY IMPLEMENTED WITH int

#include <bits/stdc++.h>
using namespace std;
#define int long long
int buyMaximumProducts(int n, int k, vector <int> a) {
    vector<pair<int, int> > v;
    for (int i = 0; i < a.size(); i++) {
        v.push_back(make_pair(a[i], i + 1));
    }
    sort(v.begin(), v.end());
    
    int amnt = 0;
    for (int i = 0; i < v.size(); i++) {
        int get = k / v[i].first;
        get = min(get, v[i].second);
        
        amnt += get;
        k -= get * v[i].first;
    }
    
    return amnt;
}

#undef int
int main() {
#define int long long
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int arr_i = 0; arr_i < n; arr_i++){
       cin >> arr[arr_i];
    }
    int k;
    cin >> k;
    int result = buyMaximumProducts(n, k, arr);
    cout << result << endl;
    return 0;
}
