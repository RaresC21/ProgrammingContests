#include <bits/stdc++.h>
using namespace std;

#define MAX 104000
int lps[MAX];

void longest_prefix_suffix(const string& pattern) {
    lps[0] = lps[1] = 0;
    int m = pattern.size();

    for (int i = 2; i <= m; i++) {
        int j = lps[i - 1];
        while (true) {
            if (pattern[j] == pattern[i - 1]) {
                lps[i] = j + 1;
                break;
            }
            if (j == 0) {
                lps[i] = 0;
                break;
            }
            j = lps[j];
        }
    }
}

int main() {

    string s; cin >> s;
    longest_prefix_suffix(s);

    string nope = "Just a legend\n";

    if (lps[s.size()] == 0) {
        cout << nope;
        return 0;
    }

    int ans = 0;
    for (int i = 2; i < s.size() - 1; i++) {
        if (lps[i] == lps[s.size()]) {
            ans = lps[i];
            break;
        }
    }

    if (ans == 0) {
        if (lps[lps[s.size()]] == 0) {
            cout << nope;
            return 0;
        } else
            ans = lps[lps[s.size()]];
    }

    for (int i = 0; i < ans; i++)
        cout << s[i];
    cout << "\n";

    return 0;
}