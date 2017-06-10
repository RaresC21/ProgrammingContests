#include <bits/stdc++.h>
using namespace std;

#define MAX 100005
int met[MAX];

int main() {

    int N, K; cin >> N >> K;

    queue<pair<int, string> > q;
    string kk = to_string(K);
    q.push(make_pair(K % N, kk));
    while (true) {
	int num = q.front().first;
	string s = q.front().second;
	q.pop();
	
	if (met[num]) continue;
	met[num] = true;

	
	if (num == 0) {
	    cout << s << "\n";
	    break;
	}

	q.push(make_pair((num * 10) % N, s + '0'));
	q.push(make_pair((num * 10 + K) % N, s + kk));
    }
        
    return 0;
}
