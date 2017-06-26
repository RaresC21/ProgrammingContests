#include <bits/stdc++.h>
using namespace std;

const int MAX = 1000006;
bool met[MAX];
int div_[MAX];

bool have[MAX];
int solution[MAX];
int calculate[MAX][20];

int calc(int a, int n) {
    if (calculate[a][n] != 0) return calculate[a][n];
    long long ans = 1;
    for (int i = 0; i < n; i++) {
	if (ans > MAX / a) return calculate[a][n] = MAX;
	ans *= a;
    }
    return calculate[a][n] = ans;
}

int root(int n, int amnt) {
    int minim = 1, maxim = n;
    int ans = 1;
    while (minim <= maxim) {
	int x = (minim + maxim) / 2;
	if (calc(x, amnt) <= n) {
	    minim = x + 1;
	    ans = max(ans, x);
	} else {
	    maxim = x - 1;
	}
    }
    return ans;
}

int main() {

    div_[1] = 1;
    for (int i = 2; i < MAX; i++) {
	if (met[i]) continue;
	for (int k = i; k < MAX; k += i) {
	    met[k] = true;
	    div_[k] = i;
	}
    }

    int N; cin >> N;
    int Q; cin >> Q;
    int x;
    for (int i = 0; i < N; i++) {
	scanf("%d", &x);
	have[x] = true;
    }

    for (int q = 0; q < Q; q++) {
	int xx; scanf("%d", &xx);
	x = xx;
	if (solution[x] == 1) {
	    printf("YES\n");
	    continue;
	} else if (solution[x] == -1) {
	    printf("NO\n");
	    continue;
	}
	
	vector<int> d;
	while (x > 1) {
	    d.push_back(div_[x]);
	    x /= div_[x];
	}

	bool good = false;
	for (int i = 0; i < d.size() && !good; i++) {
	    for (int k = 0; k < i && !good; k++) {
		x = xx;
		int cur = x / (d[i] * d[k]);
		if (cur == 1) {
		    printf("YES\n");
		    good = true;
		    break;
		}

		int amnt = 2;
		int original = cur;
		while (cur > 1 && amnt < 20) {
		    if (have[cur]) {
			printf("YES\n");
			good = true;
			break;
		    }

		    while (true && cur > 1 && amnt < 20) {
			int c = root(original, amnt);
			if (c == 1) { cur = 1; break; }
			if (calc(c, amnt) == original) {
			    cur = c;
			    amnt++;
			    break;
			}
			amnt++;
		    }
		}
	    }
	}
	if (!good) {
	    solution[xx] = -1;
	    printf("NO\n");
	} else {
	    solution[xx] = 1;
	}
    }
    
    return 0;
}
