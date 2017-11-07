#include "bits/stdc++.h"
using namespace std;

#define MOD 1000000007
#define MAX 10000
typedef long long int lli;

// returns a^x mod p
lli exponent_(lli a, lli x, lli p) {
    lli ans = 1;
    while (x > 0) {
        if (x % 2 == 1)
            ans = (ans * a) % p;
        x /= 2;
        a = (a * a) % p;
    }
    return ans;
}

lli modular_inverse_(lli a, lli b, lli p) {
    return ((a % p) * (exponent_(b, p - 2, p) % p)) % p;
}

// return a % b (positive value)
int mod(int a, int b) {
    return ((a%b) + b) % b;
}

// computes gcd(a,b)
int gcd(int a, int b) {
    while (b) { int t = a%b; a = b; b = t; }
    return a;
}

// computes lcm(a,b)
int lcm(int a, int b) {
    return a / gcd(a, b)*b;
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

// finds all solutions to ax = b (mod n)
vector<int> modular_linear_equation_solver(int a, int b, int n) {
    int x, y;
    vector<int> ret;
    int g = extended_euclid(a, n, x, y);
    if (!(b%g)) {
        x = mod(x*(b / g), n);
        for (int i = 0; i < g; i++)
            ret.push_back(mod(x + i*(n / g), n));
    }
    return ret;
}

// computes b such that ab = 1 (mod n), returns -1 on failure
int mod_inverse(int a, int n) {
    int x, y;
    int g = extended_euclid(a, n, x, y);
    if (g > 1) return -1;
    return mod(x, n);
}

// find z such that  z % m1 = r1, z % m2 = r2.
// Here, z is unique modulo M = lcm(m1, m2).
// Return (z, M).  On failure, M = -1.
pair<int, int> chinese_remainder_theorem(int m1, int r1, int m2, int r2) {
    int s, t;
    int g = extended_euclid(m1, m2, s, t);
    if (r1%g != r2%g) return make_pair(0, -1);
    return make_pair(mod(s*r2*m1 + t*r1*m2, m1*m2) / g, m1*m2 / g);
}

// Chinese remainder theorem: find z such that
// z % m[i] = r[i] for all i.  Note that the solution is
// unique modulo M = lcm_i (m[i]).  Return (z, M). On
// failure, M = -1. Note that we do not require the a[i]'s
// to be relatively prime.
pair<int, int> chinese_remainder_theorem(const vector<int> &m, const vector<int> &r) {
    pair<int, int> ret = make_pair(r[0], m[0]);
    for (int i = 1; i < m.size(); i++) {
        ret = chinese_remainder_theorem(ret.second, ret.first, m[i], r[i]);
        if (ret.second == -1) break;
    }
    return ret;
}

// computes x and y such that ax + by = c
// returns whether the solution exists
bool linear_diophantine(int a, int b, int c, int &x, int &y) {
    if (!a && !b) {
        if (c) return false;
        x = 0; y = 0;
        return true;
    }
    if (!a) {
        if (c % b) return false;
        x = 0; y = c / b;
        return true;
    }
    if (!b) {
        if (c % a) return false;
        x = c / a; y = 0;
        return true;
    }
    int g = gcd(a, b);
    if (c % g) return false;
    x = c / g * mod_inverse(a / g, b / g);
    y = (c - a*x) / b;
    return true;
}

int is_prime[MAX+1];
vector<int> primes;
void calc_primes () {
    for (int i = 2; i <= MAX; i++) is_prime[i] = true;
    for (int i = 2; i*i < MAX; i++) {
        if (!is_prime[i]) continue;
        for (int k = i+i; k <= MAX; k += i)
            is_prime[k] = false;
        primes.push_back(i);
    }
}

lli fact[MAX];
void calculate_factorial() {
	fact[0] = 1;
	for (int i = 1; i < MAX; i++)
		fact[i] = fact[i - 1] * i;
}

// (r choose n) mod p
lli combinatorics_(lli n, lli r, lli p) {
	return (modular_inverse_(fact[n], (fact[r] * fact[n - r]) % p, p)) % p;
}

// pascal's triangle to get exact values for combinatorics.
// n choose k
lli C[MAX];
lli pascal_comb_(lli n, int k) {
	for (int j = 0; j < MAX; j++) C[j] = 0;
	C[0] = 1;  // nC0 is 1
	for (int i = 1; i <= n; i++)
		for (lli j = min(i, k); j > 0; j--)
			C[j] = C[j] + C[j - 1];
	return C[k];
}

// A O(n^2) time and O(n^2) extra space method for Pascal's Triangle
lli pascal_triangle[MAX][MAX];
void make_pascal(int n) {
    for (int line = 0; line < n; line++) {
        for (int i = 0; i <= line; i++) {
            if (line == i || i == 0)
                pascal_triangle[line][i] = 1;
            else
                pascal_triangle[line][i] = pascal_triangle[line-1][i-1] + pascal_triangle[line-1][i];
        }
    }
}

lli binomialCo(int N, int r) {
    lli res = 1;
    r=(r<(N-r))?r:(N-r);
    for(int i = 1; i <= r; i++, N--) {
        res *= N;
        res /= i;
    }
    return res;
}

// we need to multiply the numbers in vector a and those in vector b
// then determine which product is bigger. return true if a > b;
bool compare_product(vector<lli> a, vector<lli> b) {
    // assumes all values in a and b are positive.
    double logA = 0, logB = 0;
    for (int i = 0; i < a.size(); i++) logA += log10(a[i]);
    for (int i = 0; i < b.size(); i++) logB += log10(b[i]);
    if (logA > logB) return true;
    return false;
}

// create list of primitive pythagorean triples
vector<pair<pair<int, int>, int> > pyth;
void pythagorean_triples(int N) {
    for (int i = 1; i <= N; i++) {
        for (int k = 1; k < i; k++) {
            if (gcd(i,k) != 1) continue;
            if (i % 2 == 1 && k % 2 == 1) continue;

            int a = i*i - k*k;
            int b = 2*i*k;
            int c = i*i + k*k;
            pyth.push_back(make_pair(make_pair(a,b), c));
        }
    }
}

int eulerPhiDirect (int n) {
    int result = n;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i] && result % i == 0) {
            result -= result / i;
        }
    }
    return result;
}

// euler totient. with sieve
int eulerPhi[1000];
void eulerSieve (int N) {
    for (int i = 1; i <= N; i++)
        eulerPhi[i] = i;
    for (int i = 1; i <= N; i++) {
        if (is_prime[i]) {
            for (int j = i; j <= N; j += i)
                eulerPhi[j] -= eulerPhi[j] / i;
        }
    }
}

// Fibonacci numbers.
/*      Useful formulas.

    Every positive integer can be represented uniquely as a sum of two or more
    distinct Fibonacci numbers. greedy.

    F(n+1) * F(n-1) - F(n) * F(n) = (-1) ^ n
    F(A+B) = F(A) * F(B+1) + F(A-1) * F(B)

    sum of first n fibonacci numbers = F(n+2) - 1

    gcd(F(n), F(m)) = F(gcd(n, m))
*/
void multiply_fibo(lli F[2][2], lli M[2][2]) {
    lli x = F[0][0] * M[0][0] + F[0][1] * M[1][0];
    lli y = F[0][0] * M[0][1] + F[0][1] * M[1][1];
    lli z = F[1][0] * M[0][0] + F[1][1] * M[1][0];
    lli w = F[1][0] * M[0][1] + F[1][1] * M[1][1];

    F[0][0] = x%MOD;
    F[0][1] = y%MOD;
    F[1][0] = z%MOD;
    F[1][1] = w%MOD;
}

void power_fibo(lli F[2][2], lli n) {
    if (n == 0 || n == 1) return;
    lli M[2][2] = { { 1,1 }, { 1,0 } };

    power_fibo(F, n / 2);
    multiply_fibo(F, F);
    if (n % 2 != 0)
        multiply_fibo(F, M);
}

lli fib(lli n) {
    lli F[2][2] = {{ 1,1 }, { 1,0 }};
    if (n == 0)
        return 0;
    power_fibo(F, n - 1);
    return F[0][0];
}

// the n-th s-gonal number;
lli polygonal_number(int n, int s) {
    return ((s-2) * (n) * (n-1)) / 2 + n;
}

lli catalan_number(int n) {
    lli comb = pascal_comb_(2*n, n);
    return comb / (n+1);
}

// number of ways to partition a set of n objects into k non-empty subsets
lli secStirling[MAX][MAX];
lli second_kind_stirling (int n, int k) { // make sure to initialize secStirling to -1 for all values
    if (secStirling[n][k] >= 0) return secStirling[n][k];
    if (n == 0 && k == 0) return secStirling[n][k] = 1;
    else if (n == 0 || k == 0) return secStirling[n][k] = 0;
    return secStirling[n][k] = k * second_kind_stirling(n - 1, k) + second_kind_stirling(n - 1, k - 1);
}

lli firstStirling[MAX][MAX];
lli first_kind_stirling(int n, int k)  { // initialize firstStirling to -1 for all values
    if (firstStirling[n][k] >= 0) return firstStirling[n][k];
    if (n == 0 && k == 0) return firstStirling[n][k] = 1;
    else if (n == 0 || k == 0) return firstStirling[n][k] = 0;
    return firstStirling[n][k] = (n - 1) * first_kind_stirling(n - 1, k) + first_kind_stirling(n - 1, k - 1);
}

// evaluate (1^m + 2^m + ... + n^m) % MOD


int normal(int n) {
    n %= MOD;
    (n < 0) && (n += MOD);
    return n;
}

int add(int a, int b) { return a + b >= MOD ? a + b - MOD : a + b; }
int sub(int a, int b) { return a - b < 0 ? a - b + MOD : a - b; }
int mul(int a, int b) { return int(a * 1ll * b % MOD); }
int _div(int a, int b) { return modular_inverse_(a, b, MOD); }

int calc(const vector<int>& y, int x) {
    int ans = 0;
    int k = 1;
    for (int j = 1; j < (int)(y.size()); j++) {
        k = mul(k, normal(x - j));
        k = _div(k, normal(0 - j));
    }
    for (int i = 0; i < (int)(y.size()); i++) {
        ans = add(ans, mul(y[i], k));
        if (i + 1 >= y.size()) break;
        k = mul(k, _div(normal(x - i), normal(x - (i + 1))));
        k = mul(k, _div(normal(i - (y.size() - 1)), normal(i + 1)));
    }
    return ans;
}

int power_sum(int n, int k) {
    vector<int> y;
    int sum = 0;
    y.push_back(sum);
    for (int i = 0; i < k + 1; i++) {
        sum = add(sum, exponent_(i + 1, k, MOD));
        y.push_back(sum);
    }
    if (n < y.size()) return y[n];
    return calc(y, n);
}

/*
    Stirling's approximation:
        n! = sqrt(2 * PI * n) * (n/e) ^ n

    n-th harmonic number approximated by ln(n)
*/

int main() {

    return 0;
}