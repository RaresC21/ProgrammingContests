/* 
   /home/rares/ProgrammingContests/Codeforces/Educational_27/
   D.cpp
*/

/*
  Whenever we change the speed limit or our own speed, we need to check if everything is still
  in correct. If we have violated the law, we must "forget" everything from that point back to 
  a time where our current speed would have been correct. We can simply use a stack containing 
  speed limits to implement this. Pop back from the top as long as the limit is lower than our 
  current speed.

  As for the overtake, we can do something similar, only there is no need for a stack. 
  We must forget everything back to a time where overtaking is allowed, so just need to keep 
  count of how many "no overtake" signs we've seen since the last sign that allowed us to overtake.

  You can see the codeforces editorial for a differently worded explanation.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

#define MAX 200005
int dp[MAX];

inline void check_speed(stack<int>& limits, int& ans, int speed) {
    while (limits.size() && speed > limits.top()) {
	ans++;
	limits.pop();
    }
}

inline void clear_stack(stack<int>& s) {
    while(s.size())
	s.pop();
}

int main() {
    
    int N; cin >> N;
    int speed = 0;

    stack<int> limits;
    int overtake_count = 0, ans = 0;
    
    for (int i = 0; i < N; i++) {
	int t; cin >> t;
	if (t == 1) {
	    cin >> speed;
	    check_speed(limits, ans, speed);
	} else if (t == 2) {
	    if (overtake_count) {
		ans += overtake_count;
		overtake_count = 0;
	    } 
	} else if (t == 3) {
	    int l; cin >> l;
	    limits.push(l);
	    check_speed(limits, ans, speed);
	} else if (t == 4) {
	    overtake_count = 0;
	} else if (t == 5) {
	    clear_stack(limits);
	} else if (t == 6) {
	    overtake_count++;
	}
    }

    cout << ans << "\n";
    
    return 0;
}
