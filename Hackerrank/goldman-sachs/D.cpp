/* 
   /home/rares/ProgrammingContests/
   p.cpp
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

#define MAX 100005
int price[MAX], timp[MAX];;
int pref_max[MAX], suf_max[MAX];

int main() {
    
    int N, Q; cin >> N >> Q;
    for (int i = 0; i < N; i++) {
	scanf("%d", &timp[i]);
    }
    
    for (int i = 0; i < N; i++) {
	scanf("%d", &price[i]);
	if (i > 0)
	    pref_max[i] = max(pref_max[i - 1], price[i]);
	else
	    pref_max[i] = price[i];
    }
    
    suf_max[N - 1] = price[N - 1];
    for (int i = N - 2; i >= 0; i--)
	suf_max[i] = max(suf_max[i + 1], price[i]);
    
    for (int q = 0; q < Q; q++) {
	int t; scanf("%d", &t);
	if (t == 1) {
	    int val; scanf("%d", &val);
	    
	    int minim = 0, maxim = N - 1;
	    int ans = N;
	    while (minim <= maxim) {
		int mid = (minim + maxim) / 2;
		if (pref_max[mid] >= val) {
		    maxim = mid - 1;
		    ans = min(ans, mid);
		} else {
		    minim = mid + 1;
		}
	    }
	    
	    if (ans == N) printf("-1\n");
	    else printf("%d\n", timp[ans]);
	    
	} else if (t == 2) {
	    int val; scanf("%d", &val);
	    
	    int minim = 0, maxim = N - 1;
	    int ans = N;
	    while (minim <= maxim) {
		int mid = (minim + maxim) / 2;
		if (timp[mid] >= val) {
		    maxim = mid - 1;
		    ans = min(ans, mid);
		} else {
		    minim = mid + 1;
		}
	    }
	    if (ans == N) printf("-1\n");
	    else printf("%d\n", suf_max[ans]);
	}
    }
    
    return 0;
}
