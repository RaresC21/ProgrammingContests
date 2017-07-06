#include <bits/stdc++.h>
using namespace std;

#define EPS 1e-9
#define pb push_back
#define mp make_pair
const int MAX = 50;
const double acc = 0.5;
double D;
int L;

double pos[12], R[12], G[12];
double start_[12][MAX];
double dp[12][MAX][2];
int can_reach[12][12];

// return speed you should slow down to 
inline double slow_acc(double p1, double p2, double t1, double t2) {
    double d = p2 - p1;
    double t = t2 - t1;
    return (d - 0.5 * acc * t * t) / t;
}

// return amount of time you should spend at speed 0
inline double wait_acc(double p1, double p2, double t1, double t2) {
    double d = p2 - p1;
    double dt = t2 - t1;
    double t = sqrt(2 * d / acc);

    if (t > dt) return -1;
    return dt - t;
}

inline double get_time(double v0, double d) {
    return 2 * (sqrt(v0 * v0 + d) - v0);
}

inline bool in_green(double t, int indx) {
    int minim = 1, maxim = MAX;
    int ans = -1;
    while (minim <= maxim) {
	int mid = (minim + maxim) / 2;
	if (t >= start_[indx][mid]) {
	    minim = mid + 1;
	    ans = max(ans, mid);
	} else {
	    maxim = mid - 1;
	}
    }

    if (ans == -1) return false;
    return start_[indx][ans] + G[indx] >= t;
}

inline bool check(int l, int r, double start_time, double speed) {
    for (int i = r; i >= l; i--) {
	double t = start_time + get_time(speed, pos[i] - pos[l - 1]);
	if (!in_green(t, i))
	    return false;
    }
    return true;
}

inline double get_speed(double v0, double t) {
    return v0 + acc * t;
}

// return speed with which you reach goal
inline double hit(int i, int k, double t1, double t2, double cur_speed) {
    double slow = slow_acc(pos[i], pos[k], t1, t2);
    if (slow > cur_speed) return -1;
    if (slow < 0) {
	// must wait
	double wait = wait_acc(pos[i], pos[k], t1, t2);
	if (wait == -1) return -1;
	if (check(i + 1, k - 1, t1 + wait, 0)) {
	    return acc * (t2 - t1 - wait);
	} else {
	    return -1;
	}
    }
    if (check(i + 1, k - 1, t1, slow)) {
	double s = get_speed(slow, t2 - t1);
	return s;
    }
    return -1;
}

int main() {
    
    int tt = 0;
    while (scanf("%lf%d", &D, &L) == 2) {
	memset(can_reach, -1, sizeof(can_reach));
	
	for (int i = 1; i <= L; i++) {
	    scanf("%lf%lf%lf", &pos[i], &R[i], &G[i]);
	    for (int k = 1; k < MAX; k++)
		start_[i][k] = R[i] * k + G[i] * (k - 1);
	}

	if (L == 0) {
	    printf("%.3lf\n", get_time(0, D));
	    continue;
	}
	
	// init DP
	for (int i = 1; i <= L; i++) {
	    for (int k = 1; k < MAX; k++) {
		dp[i][k][0] = hit(0, i, 0, start_[i][k], 0);
		dp[i][k][1] = hit(0, i, 0, start_[i][k] + G[i], 0);
	    }
	}

	double ans = 1e18;
	if (check(1, L, 0, 0)) {
	    ans = get_time(0, D);
	    printf("%.3lf\n", ans);
	    continue;
	}
	
	for (int i = 1; i <= L; i++) {
	    for (int k = 1; k < MAX; k++) {
		for (int j = 0; j < 2; j++) {
		    if (dp[i][k][j] == -1) continue;
		    double t1 = start_[i][k];
		    if (j == 1) t1 += G[i];

		    if (t1 > ans) break;
		    
		    for (int a = i + 1; a <= L; a++) {
			for (int b = 1; b < MAX; b++) {
			    for (int c = 0; c < 2; c++) {
				double t2 = start_[a][b];
				if (c == 1) t2 += G[a];

				if (t2 > ans) break;
				

				double h = hit(i, a, t1, t2, dp[i][k][j]);
				if (h == -1)
				    dp[a][b][c] == -1;
				else {
				    dp[a][b][c] = max(dp[a][b][c], h);
				}
			    }
			}
		    }
		    
		    if (check(i + 1, L, t1, dp[i][k][j])) {
			double dt = get_time(dp[i][k][j], D - pos[i]);
			ans = min(ans, t1 + dt);
		    }
		}
	    }
	}
	printf("%.3lf\n", ans);
    }

    return 0;
}
