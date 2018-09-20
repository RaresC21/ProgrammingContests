#include <bits/stdc++.h>
using namespace std;

#define int long long

#define LL long long
#define VI vector<int>
#define VLL vector<LL>
#define mp make_pair
#define pb push_back
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
#define A first
#define B second
#define io ios_base::sync_with_stdio(false)

const int INF = 1e9;
const int MOD = 1e6 + 7;
const int MAX = 2e5 + 10;

VI mods = {29, 34483};

LL fact[2][MAX];
#define ll LL

vector<ll> factorials[2], inverse_factorials[2];

ll powmod(ll b, ll e, int indx) {
  ll p = mods[indx];
  ll ans = 1;
  while (e) {
    if (e % 2) ans = (ans * b) % p;
    b = (b * b) % p;
    e /= 2;
  }
  return ans;
}

void GetFactorials(int indx) {
  ll p = mods[indx];
  factorials[indx].resize(p);
  inverse_factorials[indx].resize(p);
  factorials[indx][0] = 1;
  inverse_factorials[indx][0] = 1;
  for (int i = 1; i < p; i++) {
    factorials[indx][i] = (i * factorials[indx][i - 1]) % p;
    inverse_factorials[indx][i] = powmod(factorials[indx][i], p - 2, indx);
  }
}

ll Binomial(ll n, ll k, int indx) {
  ll p = mods[indx];
  if (n < 0 || k < 0 || k > n) return 0;
  ll tmp = (factorials[indx][n] * inverse_factorials[indx][k]) % p;
  return (tmp * inverse_factorials[indx][n - k]) % p;
}

ll LucasBinomial(ll n, ll k, int indx) {
  ll p = mods[indx];
  ll ans = 1;
  while (n || k) {
    ans = (ans * Binomial(n % p, k % p, indx)) % p;
    n /= p;
    k /= p;
  }
  return ans;
}

int mod(int a, int b) {
  return (a+b) % b;
}

// returns g = gcd(a, b); finds x, y such that d = ax + by
int extended_euclid(int a, int b, int &x, int &y) {
  int xx = y = 0;
  int yy = x = 1;
  while (b) {
    int q = a / b;
    int t = b; b = a%b; a = t;
    t = xx; xx = x - q*xx; x = t;
    t = yy; yy = y - q*yy; y = t;
  }
  return a;
}

// find z such that  z % m1 = r1, z % m2 = r2.
// Here, z is unique modulo M = lcm(m1, m2).
// Return (z, M).  On failure, M = -1.
PII chinese_remainder_theorem(int m1, int r1, int m2, int r2) {
  int s, t;
  int g = extended_euclid(m1, m2, s, t);
  if (r1%g != r2%g) return make_pair(0, -1);
  return mp(mod(s*r2*m1 + t*r1*m2, m1*m2) / g, m1*m2 / g);
}

LL exp(int a, int x, int m) {
  LL ans = 1;
  while (x) {
    if (x % 2) {
      ans = (1LL * ans * a) % m;
    }
    a = (1LL * a * a) % m;
    x /= 2;
  }
  return ans;
}

LL inv(int a, int m) {
  return exp(a, m - 2, m);
}

LL comb(int n, int k) {
  LL a = LucasBinomial(n, k, 0);
  LL b = LucasBinomial(n, k, 1);
  LL ans = chinese_remainder_theorem(mods[0], a, mods[1], b).A;
  return ans;
}

// stars and bars
int f(int n, int k) {
  LL ans = comb(n + k - 1, n - 1);
  return ans;
}

#undef int
int main() {
#define int LL
  io;

  GetFactorials(0);
  GetFactorials(1);
  
  int N, M, K; cin >> N >> M >> K;
  
  int sgn = 1;
  LL ans = 0;
  for (int i = 0; i <= N; i++) {
    if (K - (M+1) * i < 0) break;
    LL a = (comb(N, i) * f(N, K - (M+1) * i)) % MOD;
    ans = (ans + sgn * a + MOD) % MOD;
    sgn *= -1;
  }

  ans %= MOD;
  cout << (ans + MOD) % MOD << "\n";
  
  return 0;
}
