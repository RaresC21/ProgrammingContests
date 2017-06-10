#include <bits/stdc++.h>
using namespace std;

#define MAX 100005
int parent[MAX];
int rank_[MAX];

int find_set(int a) {
    if (a != parent[a])
	parent[a] = find_set(parent[a]);
    return parent[a];
}

void make_set(int a) {
    parent[a] = a;
    rank_[a] = 0;
}

void merge(int a, int b) {
    int root_a = find_set(a);
    int root_b = find_set(b);
    if (root_a == root_b) return;
    if (rank_[root_a] > rank_[root_b])
	parent[root_b] = root_a;
    else
	parent[root_a] = root_b;
    if (rank_[root_a] == rank_[root_b])
	rank_[root_b] ++;
}

int main() {

    int T; scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
	int N; scanf("\n%d\n", &N);
	for (int i = 1; i <= N; i++)
	    make_set(i);

	string s;
	int good = 0, bad = 0;
	while (true) {
	    if (!getline(cin, s) || s.empty()) break;
	    char c; int x, y;
	    sscanf(s.c_str(), "%c %d %d", &c, &x, &y);
	    
	    if (c == 'c') merge(x, y);
	    else if (find_set(x) == find_set(y)) {
		good ++;
	    } else {
		bad ++;
	    }
	}
	if (t != 1) printf("\n");
	printf ("%d,%d\n", good, bad);
    }
    
    return 0;
}
