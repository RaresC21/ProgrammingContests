#include <bits/stdc++.h>
using namespace std;

#define MAX 100005
int arr[MAX];

vector<string> ans;

bool cmp(string& a, string& b) {
    return a.size() > b.size();
}

int main() {

    string s;
    cin >> s;
    int N = s.size();
    
    int sum = 0;
    for (int i = 0; i < N; i++) {
	arr[i] = (s[i] - '0') % 3;
	sum = (sum + arr[i]) % 3;
    }

    if (sum % 3 == 0) {
	cout << s << "\n";
	return 0;
    }

    map<int, int> have;
    bool found = false;
    for (int i = 1; i < N; i++) {
	int cur_sum = (sum - arr[i] + 3) % 3;
	if (cur_sum == 0) {
	    for (int k = 0; k < s.size(); k++)
		if (k != i)
		    cout << s[k];
	    cout << "\n";
	    return 0;
	}	
	int need = cur_sum;
	if (have.count(need) && !found) {
	    string sol = "";
	    for (int k = 0; k < N; k++)
		if (k != i && k != have[need]) sol = sol + s[k];
	    ans.push_back(sol);
	    found = true;
	}
	
	have[arr[i]] = i;
    }

    int cur_sum = (sum - arr[0] + 3) % 3;    
    int need = cur_sum;
    bool bad = true;
    string sol = "";
    if (have[need] || cur_sum == 0) {
	int amnt = 0;
	for (int i = 1; i < N; i++) {
	    if (cur_sum != 0 && have[need] == i) continue;
	    if (s[i] == '0' && bad) continue;
	    bad = false;
	    sol = sol + s[i];
	    amnt++;
	}
	ans.push_back(sol);
    }

    sort(ans.begin(), ans.end(), cmp);
    if (ans.size() != 0 && ans[0].size() != 0) {
	cout << ans[0] << "\n";
	return 0;
    }
	
    for (int i = 1; i < N; i++) {
	if (s[i] == '0') {
	    cout << "0\n";
	    return 0;
	}
    }
    
    cout << "-1\n";
    
    return 0;
}
