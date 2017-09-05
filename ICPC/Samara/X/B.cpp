#include <bits/stdc++.h>
using namespace std;

int main() {

    string target = "happiness";
    string s; cin >> s;

    if (s.size() < target.size()) {
        cout << "YES\n";
        cout << "1 2\n";
        return 0;
    }

    int a = -1, b = -1;
    for (int i = 0; i <= s.size() - target.size(); i++) {
        int k = 0;
        for (k = 0; k < target.size(); k++) {
            if (target[k] != s[i + k]) break;
        }
        if (k >= target.size()) {
            if (a == -1) a = i;
            else if (b == -1) b = i;
            else {
                cout << "NO\n";
                return 0;
            }
        }
    }

    if (a == -1 && b == -1) {
        for (int i = 0; i < s.size(); i++) {
            for (int j = i + 1; j < s.size(); j++) {
                bool good = true;
                swap(s[i], s[j]);
                for (int k = 0; k <= min((int)s.size() - 9, j); k++) {
                    if (s.substr(k, 9) == target) {
                        good = false;
                        break;
                    }
                }
                swap(s[i], s[j]);
                if (good) {
                    cout << "YES\n";
                    cout << i + 1 << " " << j + 1 << "\n";
                    return 0;
                }
            }
        }
        cout << "NO\n";
    } else if(a != -1 && b == -1) {
        cout << "YES\n";
        cout << a + 1 << " " << a + 2 << "\n";
    } else {
        cout << "YES\n";
        cout << a + 1 << " " << b + 2 << "\n";
    }

    return 0;
}