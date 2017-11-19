// Reduced row echelon form via Gauss-Jordan elimination
// with partial pivoting.  This can be used for computing
// the rank of a matrix.
//
// Running time: O(n^3)
//
// INPUT:    a[][] = an nxm matrix
//
// OUTPUT:   rref[][] = an nxm matrix (stored in a[][])
//           returns rank of a[][]

//           To get basis, we store the indices of the columns in the
//           original matrix.

#include <bits/stdc++.h>
using namespace std;
const double EPSILON = 1e-10;

typedef int T;
typedef vector<T> VT;
typedef vector<VT> VVT;
const int MOD = 2;

bool is_linear_combination(const VVT& A, const vector<int> indx, VT v) {
  for (int i = 0; i < v.size(); i++) {
    if (!v[i]) continue;
    bool good = false;
    for (int k : indx) {
      if (A[i][k]) {
        good = true;
        break;
      }
    }
    if (!good) return false;
  }
  return true;
}

int get_basis(VVT &a, vector<int>& basis_indx) {
  int n = a.size();
  int m = a[0].size();
  int r = 0;
  for (int c = 0; c < m && r < n; c++) {
    int j = r;
    for (int i = r + 1; i < n; i++)
      if (fabs(a[i][c]) > fabs(a[j][c])) j = i;
    if (fabs(a[j][c]) < EPSILON) continue;
    swap(a[j], a[r]);

    T s = a[r][c] % 2; // everything mod 2, so a[r][c] must be equal to 1.
    // change it to::  T s = 1.0 / a[r][c] for normal gaussian
    for (int j = 0; j < m; j++) a[r][j] *= s;
    for (int i = 0; i < n; i++) if (i != r) {
      T t = a[i][c];
      for (int j = 0; j < m; j++) {
        a[i][j] -= t * a[r][j];
        a[i][j] = (a[i][j] + MOD) % MOD;
      }
    }
    basis_indx.push_back(c);
    r++;
  }
  return r;
}

int main() {

  int T; cin >> T;
  for (int t = 1; t <= T; t++) {
    int N, M; cin >> N >> M;
    VVT A(32, VT(N, 0));
    for (int i = 0; i < N; i++) {
      int x; cin >> x;
      VT cur;
      for (int j = 0; j < 32; j++) {
        A[j][i] = x % 2;
        x /= 2;
      }
    }

    VVT original = A;
    vector<int> basis_indx;
    int rank = get_basis(A, basis_indx);
    int free = N - rank;
    long long free_subset = 1;
    long long all = 1;
    for (int k = 0; k < N; k++) all = (all * 2) % 100000007;
    for (int k = 0; k < free; k++) free_subset = (free_subset * 2) % 100000007;

    long long ans = 0;
    for (int i = 0; i < M; i++) {
      int cur; cin >> cur;
      VT v;
      for (int k = 0; k < 32; k++) {
        v.push_back(cur % 2);
        cur /= 2;
      }
      if (is_linear_combination(original, basis_indx, v))
        ans = (ans + free_subset) % 100000007;
    }
    ans = all - ans;
    ans = (ans + 100000007) % 100000007;
    cout << "Case " << t << ": ";
    cout << ans << "\n";
  }

  return 0;
}

