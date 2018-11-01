inline double area(double a, double b, const vector<vector<PT> >& v) {
    vector<pair<double, int> > event;
    int cnt = 0;
    for (int i = 0; i < v.size(); i++) {
      for (int k = 0; k < v[i].size(); k++) {
            PT p1 = v[i][k];
            PT p2 = v[i][(k + 1) % v[i].size()];
            if (p1.X > p2.X) swap(p1, p2);
            if (p1.X <= a && p2.X >= b) {
                PT q1, q2;
                line_line(p1, p2, PT(a,0), PT(a,100), q1);
                line_line(p1, p2, PT(b,0), PT(b,100), q2);
                double yy = ((q1.Y + q2.Y) / 2);
                event.pb((mp(yy, i)));
            }
        }
    }

    sort(event.begin(), event.end());
    double ans = 0, amnt = 0;
    set<int> met;
    for (int i = 0; i < event.size(); i++) {
        double yy = event[i].A;
        int t = event[i].B;
        if (met.count(t)) {
            amnt --;
            if (amnt == 0)
                ans += yy;
            met.erase(t);
        } else {
            if (amnt == 0)
                ans -= yy;
            amnt ++;
            met.insert(t);
        }
    }
    return ans * (b - a);
}

double polygon_union_area(const vector<vector<PT> >& v) {
    int N = v.size();
    vector<double> xs;
    vector<pair<PT, PT> > all;
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < v[i].size(); k++) {
            int j = (k + 1) % v[i].size();
            all.pb(mp(v[i][k], v[i][j]));
        }
    }
    for (int i = 0; i < all.size(); i++) {
        xs.pb(all[i].A.X);
        for (int k = 0; k < i; k++) {
            PT p;
            if (line_line(all[i].A, all[i].B, all[k].A, all[k].B, p)) {
                // min and max values coordinates can take on
                if (p.X >= 0 && p.X <= 1000 && p.Y <= 1000 && p.Y >= 0)
                    xs.pb(p.X);
            }
        }
    }
    double ans = 0;
    sort(xs.begin(), xs.end());
    for (int i = 0; i < xs.size() - 1; i++) {
        if (xs[i + 1] - xs[i] < eps) continue;
        ans += area(xs[i], xs[i + 1], v);
    }
    return ans;
}
