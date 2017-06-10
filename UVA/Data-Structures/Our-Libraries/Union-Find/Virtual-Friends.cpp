#include <bits/stdc++.h>
using namespace std;

#define MAX 100005
int parent[MAX];
int sz[MAX];
int rank_[MAX];
map<string, int> mp;

void make_set(int a) {
    if (parent[a] == 0) {
	parent[a] = a;
	sz[a] = 1;
	rank_[a] = 0;
    }
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
    if (rank_[a] > rank_[b]) {
	parent[b] = a;
	sz[a] += sz[b];
    } else {
	parent[a] = b;
	sz[b] += sz[a];
    }
    if (rank_[a] == rank_[b])
	rank_[b] ++;
}

int get_size(int a) {
    return sz[find_set(a)];
}

int main() {

    int T; cin >> T;
    while (T--) {
	memset(parent, 0, sizeof(parent));
	mp.clear();
	
	int cnt = 1;
	int N; cin >> N;
	for (int i = 0; i < N; i++) {
	    string s1, s2; cin >> s1 >> s2;
	    if (mp.count(s1) == 0) mp[s1] = cnt++;
	    if (mp.count(s2) == 0) mp[s2] = cnt++;

	    int a = mp[s1];
	    int b = mp[s2];
	    
	    make_set(a); make_set(b);
	    merge(a, b);
	    
	    printf("%d\n", get_size(a));
	}
    }
    
    return 0;
}
