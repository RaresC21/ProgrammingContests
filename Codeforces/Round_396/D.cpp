#include <bits/stdc++.h>
using namespace std;

#define MAX 200005
int parent[MAX];
int rank_[MAX];

void make_set(int a) {
    parent[a] = a;
    rank_[a] = 0;
}

int find_set(int a) {
    if (a != parent[a])
	parent[a] = find_set(parent[a]);
    return parent[a];
}

void merge(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a == b) return;
    if (rank_[a] > rank_[b])
	parent[b] = a;
    else
	parent[a] = b;
    if (rank_[a] == rank_[b])
	rank_[b]++;
}

bool same(int a, int b) {
    return find_set(a) == find_set(b);
}

map<string, int> to_int;

int main() {

    int N, M, Q;
    cin >> N >> M >> Q;
    for (int i = 0; i < N; i++) {
	string s; cin >> s;
	to_int[s] = i;
	make_set(i);
	make_set(i + N);
    }

    for (int i = 0; i < M; i++) {
	int t; cin >> t;
	string s1, s2; cin >> s1 >> s2;
	int a = to_int[s1];
	int b = to_int[s2];
	if (t == 1) {
	    if (same(a, b + N) || same(b, a + N)) cout << "NO\n";
	    else {
		cout << "YES\n";
		merge(a, b);
		merge(a + N, b + N);
	    }
	} else {
	    if (same(a, b) || same(a + N, b + N)) cout << "NO\n";
	    else {
		cout << "YES\n";
		merge(a, b + N);
		merge(b, a + N);
	    }
	}
    }

    for (int i = 0; i < Q; i++) {
	string s1, s2; cin >> s1 >> s2;
	int a = to_int[s1];
	int b = to_int[s2];

	if (same(a, b) || same(a + N, b + N)) {
	    cout << "1\n";
	} else if (same(a, b + N) || same(b, a + N)) {
	    cout << "2\n";
	} else {
	    cout << "3\n";
	}
    }
    
    return 0;
}
