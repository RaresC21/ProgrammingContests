/* 
   /home/rares/ProgrammingContests/Codeforces/Educational_27/
   C.cpp
*/

/*

  If at any point in time there are more than 2 tv shows playing, then the answer is "NO"

  SLOW, but possibly useful to know:
  One way to do this is to keep an array where index i will keep information about how many 
  tv shows are playing. For each reange given, increment each value by one. If it ever becomes
  greater than 2, answer is NO, otherwise, it's YES.
  However, we need O(M) time to update the array for each range, for a running time of O(MN)
  where M is the range of values that tv shows can start and end at. 
  Since M = 10^9 and N = 10^5, this is not fast enough

  AC:
  Note that the changes only occur whenever a tv show begins or ends. These are really the 
  only times which we care about. So we keep a vector of all of these events and traverse 
  the events in chronological order. We also keep a counter of the number of tv shows currently
  on air. 
  There may be more than one tv show that starts at the same time. So we add in all of these
  tv shows. Then we check if the current number of tv shows is greater than 2. Only afterwards, 
  can we take out all of the tv shows that ended at that same period in time. 
  Move on the next event and repeat. 

 */

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

vector<pair<int, int> > event;

int main() {
    
    int N; cin >> N;
    for (int i = 0; i < N; i++) {
	int l, r; cin >> l >> r;
	event.pb(mp(l, 1));
	event.pb(mp(r, 2));
    }

    sort(event.begin(), event.end());

    int cur = 0;
    int tv_shows = 0;
    while (cur < event.size()) {
	int pos = event[cur].first;
	while (cur < event.size() &&
	       event[cur].second == 1 && event[cur].first == pos) {
	    cur++;
	    tv_shows ++;
	}

	if (tv_shows > 2) {
	    cout << "NO\n";
	    return 0;
	}
	
	while (cur < event.size() &&
	       event[cur].second == 2 && event[cur].first == pos) {
	    cur++;
	    tv_shows --;
	}
    }

    cout << "YES\n";
    
    return 0;
}
