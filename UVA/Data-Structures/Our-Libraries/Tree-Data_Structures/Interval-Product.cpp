#include <bits/stdc++.h>
using namespace std;

#define MAX 100005

class Fenwick {
private:
    int BIT[MAX];
    int N;
    
public:
    Fenwick(int N) : N(N) {
	memset(BIT, 0, sizeof(BIT));
    }

    void update(int x, int val) {
	for (; x <= N; x += x & -x)
	    BIT[x] += val;
    }

    int query(int x) {
	int sum = 0;
	for (; x > 0; x -= x & -x)
	    sum += BIT[x];
	return sum;
    }
};

int arr[MAX];

int main() {

    int N, K;
    while (cin >> N >> K) {
	Fenwick *zero = new Fenwick(N);
	Fenwick *neg = new Fenwick(N);
	for (int i = 1; i <= N; i++) {
	    cin >> arr[i];
	    if (arr[i] == 0)
		zero->update(i, 1);
	    else if (arr[i] < 0)
		neg->update(i, 1);
	}
	
	for (int i = 1; i <= K; i++) {
	    char c; cin >> c;
	    if (c == 'C') {
		int indx, val; cin >> indx >> val;
		if (val == 0) {
		    if (arr[indx] < 0) neg->update(indx, -1);
		    if (arr[indx] != 0) zero->update(indx, 1);
		} else if (val < 0) {
		    if (arr[indx] == 0) zero->update(indx, -1);
		    if (arr[indx] >= 0) neg->update(indx, 1);
		} else {
		    if (arr[indx] < 0) neg->update(indx, -1);
		    if (arr[indx] == 0) zero->update(indx, -1);
		}
		arr[indx] = val;
	    } else {
		int l, r; cin >> l >> r;
		int num_zeros = zero->query(r) - zero->query(l - 1);
		if (num_zeros != 0) {
		    cout << '0';
		} else {
		    int num_neg = neg->query(r) - neg->query(l - 1);
		    if (num_neg % 2 == 0)
			cout << '+';
		    else
			cout << '-';
		}
	    }
	}
	cout << "\n";
    }
    
    return 0;
}
