#include <segTree.cpp>

/*
    Sample solution to:
    Codeforces. Round 448. Problem E. 
*/

int main() {

    int N; cin >> N;
    int Q; cin >> Q;

    vector<double> v(N);
    for (int i = 0; i < N; i++) {
        cin >> v[i];
    }

    SegTree<double> *seg = new SegTree<double>(v, 0.0);

    cout << fixed << setprecision(9);
    for (int q = 0; q < Q; q++) {
        int t; cin >> t;
        if (t == 1) {
            int r1, l1; cin >> l1 >> r1;
            int r2, l2; cin >> l2 >> r2;
            l1--, r1--;
            l2--, r2--;

            double left_ex = seg->query(l1, r1) / (r1 - l1 + 1);
            double right_ex = seg->query(l2, r2) / (r2 - l2 + 1);

            // multiply everyting by (r - l) / (r - l + 1)
            // add (expecation / (r - l + 1))
            seg->update_range(l1, r1, right_ex / (r1 - l1 + 1), (r1 - l1) * 1.0 / (r1 - l1 + 1));
            seg->update_range(l2, r2, left_ex / (r2 - l2 + 1), (r2 - l2) * 1.0 / (r2 - l2 + 1));
        } else {
            int l, r; cin >> l >> r;
            l--, r--;

            cout << seg->query(l, r) << "\n";
        }
    }

    return 0;
}