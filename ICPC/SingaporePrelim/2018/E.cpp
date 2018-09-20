/*
  Credits: Matthew Fahrbach
  https://open.kattis.com/problems/gridgame
*/

#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;

bool FindMatch(int i, const vvi &w, vi &mr, vi &mc, vi &seen) {
  for (int j = 0; j < w[i].size(); j++) {
    if (w[i][j] && !seen[j]) {
      seen[j] = true;
      if (mc[j] < 0 || FindMatch(mc[j], w, mr, mc, seen)) {
        mr[i] = j;
        mc[j] = i;
        return true;
      }
    }
  }
  return false;
}

int BipartiteMatching(const vvi &w, vi &mr, vi &mc) {
  mr = vi(w.size(), -1);
  mc = vi(w[0].size(), -1);

  int ct = 0;
  for (int i = 0; i < w.size(); i++) {
    vi seen(w[0].size());
    if (FindMatch(i, w, mr, mc, seen)) ct++;
  }
  return ct;
}

int main() {
  int n, a[33][33];
  cin >> n;
  set<int> entries;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> a[i][j];
      entries.insert(a[i][j]);
    }
  }
  int ans = 0;
  for (auto val : entries) { // note brute force here instead of binary search.
    vvi w(n, vi(n));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (a[i][j] >= val) w[i][j] = 1;
      }
    }
    vi mr, mc;
    int ct = BipartiteMatching(w, mr, mc);
    if (ct >= n) ans = val;
  }
  cout << ans << endl;
  return 0;
}
