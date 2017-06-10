/*

  People are either part of group A, or group B. All people of the same group are friends. People of different groups are enemies.
  Given queries to make people friends, or enemies, or determine if they are friends or enemies.

  Solution: Get rid of the idea of making enemies. One way to think about it, is when two people become friends, draw an edge with value 1 between them. Otherwise, draw an edge with value 0 between them.
  We will use DSU for this, so there are no edges. However, we can use a similar idea. For each peron x, there are two versions of him. Person x and x + N, which are opposites of each other.
  If x and y are enemies, they are actually friends with the opposite of the other. so x is friends with y + N, and y is friends with x + N.

 */

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

bool friends(int a, int b) {
    return find_set(a) == find_set(b);
}

int main() {

    int N; cin >> N;
    for (int i = 1; i <= 2 * N; i++)
	make_set(i);

    int c, x, y; cin >> c >> x >> y;
    while (c != 0) {

	if (c == 1) {
	    if (friends(x, y + N) || friends(y, x + N)) cout << "-1\n";
	    else {
		merge(x, y);
		merge(x + N, y + N);
	    }
	} else if (c == 2) {
	    if (friends(x, y) || friends(x + N, y + N)) cout << "-1\n";
	    else {
		merge(x, y + N);
		merge(y, x + N);
	    }
	} else if (c == 3) {
	    if (friends(x, y) || friends(x + N, y + N)) cout << "1\n";
	    else cout << "0\n";
	} else {
	    if (friends(x + N, y) || friends(x, y + N)) cout << "1\n";
	    else cout << "0\n";
	}
	
	cin >> c >> x >> y;
    }
    
    return 0;
}
