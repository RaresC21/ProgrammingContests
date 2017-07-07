#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define MAX 101
int K;
lli fact[MAX];
int can[MAX][MAX];
int amnt[MAX];

lli solve() {
    memset(can, 0, sizeof(can));
    memset(amnt, 0, sizeof(amnt));
    
    string s, t;
    cin >> s >> t;

    int N = s.size();
    int block = s.size() / K;
    for (int i = 0; i < block; i++) {
	for (int k = 0; k < K; k++) {
	    int cur = i * K + k;
	    for (int j = 0; j < K; j++) {
		int cc = i * K + j;
		if (s[cur] == t[cc]) {
		    can[k][j] ++;
		}
	    }
	}
    }
    
    
    vector<int> to[MAX], from[MAX];
    for (int i = 0; i < K; i++) {
	for (int k = 0; k < K; k++) {
	    if (can[i][k] == block) {
		to[i].pb(k);
		from[k].pb(i);
	    }
	}
    }


    int total = 0;
    long long ans = 1LL;
    for (int i = 0; i < K; i++) {
	int sz = to[i].size();
	if (sz == 0) return 0;
	
	if (amnt[sz]) {
	    amnt[sz] --;
	    continue;
	}
	ans *= fact[sz];
	total += sz;
	amnt[sz] = sz - 1;
    }
    for (int i = 0; i < MAX; i++)
	if (amnt[i] != 0) return 0;
    
    lli check = 1LL;
    for (int i = 0; i < K; i++) {
	int sz = from[i].size();
	if (sz == 0) return 0;
	
	if (amnt[sz]) {
	    amnt[sz] --;
	    continue;
	}
	check *= fact[sz];
	amnt[sz] = sz - 1;
    }

    if (check != ans) return 0;
    
    for (int i = 0; i < MAX; i++)
	if (amnt[i] != 0) return 0;
    
    return ans;
}

int main() {

    fact[0] = 1;
    for (int i = 1; i < MAX; i++)
	fact[i] = fact[i - 1] * 1LL * i;

    while (scanf("%d", &K) == 1) {
	cout << solve() << "\n";
    }
    
    return 0;
}
