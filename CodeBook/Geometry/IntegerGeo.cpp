
struct PT {
    LL x, y;
    PT() {}
    PT(LL x, LL y) : x(x), y(y) {}
    PT(const PT &p) : x(p.x), y(p.y) {}
    bool operator == (PT other) const {
     return (x == other.x) && (y == other.y); }
    PT operator + (const PT &p)  const { return PT(x + p.x, y + p.y); }
    PT operator - (const PT &p)  const { return PT(x - p.x, y - p.y); }
    PT operator * (LL c)         const { return PT(x*c, y*c); }
};

LL dot(PT p, PT q) { return p.x*q.x + p.y*q.y; }
LL dist2(PT p, PT q) { return dot(p - q, p - q); }
LL cross(PT p, PT q) { return p.x*q.y - p.y*q.x; }


// determine if lines from a to b and c to d are parallel or collinear
inline bool lines_parallel(PT a, PT b, PT c, PT d) {
    return cross(b - a, c - d) == 0;
}

inline bool lines_collinear(PT a, PT b, PT c, PT d) {
    return lines_parallel(a, b, c, d)
        && cross(a - b, a - c) == 0
        && cross(c - d, c - a) == 0;
}

// determine if line segment from a to b intersects with
// line segment from c to d
inline bool segments_intersect(PT a, PT b, PT c, PT d) {
    if (lines_collinear(a, b, c, d)) {
        if (a == c || a == d ||
            b == c || b == d) return true;
        if (dot(c - a, c - b) > 0 && dot(d - a, d - b) > 0 && dot(c - b, d - b) > 0)
            return false;
        return true;
    }
    LL c1 = cross(d - a, b - a);
    LL c2 = cross(c - a, b - a);
    if ((c1 > 0 && c2 > 0) || (c1 < 0 && c2 < 0)) return false;

    c1 = cross(a - c, d - c);
    c2 = cross(b - c, d - c);
    if ((c1 > 0 && c2 > 0) || (c1 < 0 && c2 < 0)) return false;
    return true;
}
