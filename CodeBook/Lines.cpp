
/*
A 2D line is expressed in the form Ax + By + C = 0. All lines can be
"normalized" to a canonical form by insisting that the y-coefficient
equal 1 if it is non-zero. Otherwise, we set the x-coefficient to 1.
If B is non-zero, then we have the common case where the slope = -A
after normalization.
*/

/* this struct only available with
    typedef pair<double, double> PT
    #define x first
    #define y second
*/

struct line {
  double a, b, c;
  line(): a(0), b(0), c(0) {} //invalid or uninitialized line
  line(const double & A, const double & B, const double & C) {
    a = A;
    b = B;
    c = C;
    if (!EQ(b, 0)) {
      a /= b; c /= b; b = 1;
    } else {
      c /= a; a = 1; b = 0;
    }
  }

  line(const double & slope, const PT & p) {
    a = -slope;
    b = 1;
    c = slope * p.x - p.y;
  }

  line(const PT & p, const PT & q): a(0), b(0), c(0) {
    if (EQ(p.x, q.x)) {
      if (EQ(p.y, q.y)) return; //invalid line
      //vertical line
      a = 1;
      b = 0;
      c = -p.x;
      return;
    }
    a = -(p.y - q.y) / (p.x - q.x);
    b = 1;
    c = -(a * p.x) - (b * p.y);
  }

  bool operator == (const line & l) const {
    return EQ(a, l.a) && EQ(b, l.b) && EQ(c, l.c);
  }

  bool operator != (const line & l) const {
    return !(*this == l);
  }

  //whether the line is initialized and normalized
  bool valid() const {
    if (EQ(a, 0)) return !EQ(b, 0);
    return EQ(b, 1) || (EQ(b, 0) && EQ(a, 1));
  }

  bool horizontal() const { return valid() && EQ(a, 0); }
  bool vertical() const { return valid() && EQ(b, 0); }

  double slope() const {
    if (!valid() || EQ(b, 0)) return NaN; //vertical
    return -a;
  }

  //solve for x, given y
  //for horizontal lines, either +inf, -inf, or nan is returned
  double x(const double & y) const {
    if (!valid() || EQ(a, 0)) return NaN; //invalid or horizontal
    return (-c - b * y) / a;
  }

  //solve for y, given x
  //for vertical lines, either +inf, -inf, or nan is returned
  double y(const double & x) const {
    if (!valid() || EQ(b, 0)) return NaN; //invalid or vertical
    return (-c - a * x) / b;
  }

  //returns whether p exists on the line
  bool contains(const PT & p) const {
    return EQ(a * p.x + b * p.y + c, 0);
  }

  //returns whether the line is parallel to l
  bool parallel(const line & l) const {
    return EQ(a, l.a) && EQ(b, l.b);
  }

  //returns whether the line is perpendicular to l
  bool perpendicular(const line & l) const {
    return EQ(-a * l.a, b * l.b);
  }

  //return the parallel line passing through PT p
  line parallel(const PT & p) const {
    return line(a, b, -a * p.x - b * p.y);
  }

  //return the perpendicular line passing through PT p
  line perpendicular(const PT & p) const {
    return line(-b, a, b * p.x - a * p.y);
  }
};

//should we consider barely touching segments an intersection?
const bool TOUCH_IS_INTERSECT = true;

//does [l, h] contain m?
//precondition: l <= h
bool contain(const double & l, const double & m, const double & h) {
  if (TOUCH_IS_INTERSECT) return LE(l, m) && LE(m, h);
  return LT(l, m) && LT(m, h);
}

//does [l1, h1] overlap with [l2, h2]?
//precondition: l1 <= h1 and l2 <= h2
bool overlap(const double & l1, const double & h1,
             const double & l2, const double & h2) {
  if (TOUCH_IS_INTERSECT) return LE(l1, h2) && LE(l2, h1);
  return LT(l1, h2) && LT(l2, h1);
}

//intersection of line l1 and line l2, each in ax + by + c = 0 form
//returns: -1, if lines do not intersect,
//          0, if there is exactly one intersection PT, or
//         +1, if there are infinite intersection
//in the 2nd case, the intersection PT is optionally stored into p
int line_intersection(const double & a1, const double & b1, const double & c1,
                      const double & a2, const double & b2, const double & c2,
                      PT* p = 0) {
  if (EQ(a1 * b2, a2 * b1))
    return (EQ(a1 * c2, a2 * c1) || EQ(b1 * c2, b2 * c1)) ? 1 : -1;
  if (p != 0) {
    double x=0, y=0;
    x = (b1 * c1 - b1 * c2) / (a2 * b1 - a1 * b2);
    if (!EQ(b1, 0)) y = -(a1 * x + c1) / b1;
    else y = -(a2 * x + c2) / b2;
    *p = PT(x, y);
  }
  return 0;
}

//intersection of line through p1, p2, and line through p2, p3
//returns: -1, if lines do not intersect,
//          0, if there is exactly one intersection PT, or
//         +1, if there are infinite intersections
//in the 2nd case, the intersection PT is oPTionally stored into p
int line_intersection(const PT & p1, const PT & p2,
                      const PT & p3, const PT & p4, PT * p = 0) {
  double a1 = p2.Y - p1.Y, b1 = p1.X - p2.X;
  double c1 = -(p1.X * p2.Y - p2.X * p1.Y);
  double a2 = p4.Y - p3.Y, b2 = p3.X - p4.X;
  double c2 = -(p3.X * p4.Y - p4.X * p3.Y);
  double x = -(c1 * b2 - c2 * b1), y = -(a1 * c2 - a2 * c1);
  double det = a1 * b2 - a2 * b1;
  if (EQ(det, 0))
    return (EQ(x, 0) && EQ(y, 0)) ? 1 : -1;
  if (p != 0) *p = PT(x / det, y / det);
  return 0;
}

PT minim(PT a, PT b) {
  if (MP(a.X, a.Y) < MP(b.X, b.Y)) return a;
  return b;
}
PT maxim(PT a, PT b) {
  if (MP(a.X, a.Y) > MP(b.X, b.Y)) return a;
  return b;
}

//intersection of line segment ab with line segment cd
//returns: -1, if segments do not intersect,
//          0, if there is exactly one intersection PT
//         +1, if the intersection is another line segment
//In case 2, the intersection PT is stored into p
//In case 3, the intersection segment is stored into p and q
int seg_intersection(const PT & a, const PT & b,
                     const PT & c, const PT & d,
                     PT * p = 0, PT * q = 0) {
  PT ab = b - a;
  PT ac = c - a;
  PT cd = d - c;
  double c1 = cross(ab, cd), c2 = cross(ac, ab);
  if (EQ(c1, 0) && EQ(c2, 0)) { //collinear
    double t0 = dot(ac, ab) / norm(ab);
    double t1 = t0 + dot(cd, ab) / norm(ab);
    if (overlap(min(t0, t1), max(t0, t1), 0, 1)) {
      PT res1 = maxim(minim(a, b), minim(c, d));
      PT res2 = minim(maxim(a, b), maxim(c, d));
      if (res1 == res2) {
        if (p != 0) *p = res1;
        return 0; //collinear, meeting at an endPT
      }
      if (p != 0 && q != 0) *p = res1, *q = res2;
      return 1; //collinear and overlapping
    } else {
      return -1; //collinear and disjoint
    }
  }
  if (EQ(c1, 0)) return -1; //parallel and disjoint
  double t = cross(ac, cd) / c1, u = c2 / c1;
  if (contain(0, t, 1) && contain(0, u, 1)) {
    if (p != 0) *p = PT(a.X + t * ab.X, a.Y + t * ab.Y);
    return 0; //non-parallel with one intersection
  }
  return -1; //non-parallel with no intersections
}


//determines the PT on line ax + by + c = 0 that is closest to PT p
//this always lies on the line through p perpendicular to l.
PT closest_PT(const double & a, const double & b, const double & c,
                    const PT & p) {
  if (EQ(a, 0)) return PT(p.X, -c); //horizontal line
  if (EQ(b, 0)) return PT(-c, p.Y); //vertical line
  PT res;
  line_intersection(a, b, c, -b, a, b * p.X - a * p.Y, &res);
  return res;
}

//determines the PT on segment ab closest to PT p
PT closest_PT(const PT & a, const PT & b, const PT & p) {
  if (a == b) return a;
  PT ap = p-a, ab = b-a;
  double t = dot(ap, ab) / norm(ab);
  if (t <= 0) return a;
  if (t >= 1) return b;
  return PT(a.X + t * ab.X, a.Y + t * ab.Y);
}

int main() {
  PT p;
  assert(line_intersection(-1, 1, 0, 1, 1, -3, &p) == 0);
  assert(p == PT(1.5, 1.5));
  assert(line_intersection(PT(0, 0), PT(1, 1), PT(0, 4), PT(4, 0), &p) == 0);
  assert(p == PT(2, 2));

  {
#define test(a,b,c,d,e,f,g,h) seg_intersection(PT(a,b),PT(c,d),PT(e,f),PT(g,h),&p,&q)
    PT p, q;
    //intersection is a PT
    assert(0 == test(-4, 0, 4, 0, 0, -4, 0, 4));   assert(p == PT(0, 0));
    assert(0 == test(0, 0, 10, 10, 2, 2, 16, 4));  assert(p == PT(2, 2));
    assert(0 == test(-2, 2, -2, -2, -2, 0, 0, 0)); assert(p == PT(-2, 0));
    assert(0 == test(0, 4, 4, 4, 4, 0, 4, 8));     assert(p == PT(4, 4));

    //intersection is a segment
    assert(1 == test(10, 10, 0, 0, 2, 2, 6, 6));
    assert(p == PT(2, 2) && q == PT(6, 6));
    assert(1 == test(6, 8, 14, -2, 14, -2, 6, 8));
    assert(p == PT(6, 8) && q == PT(14, -2));

    //no intersection
    assert(-1 == test(6, 8, 8, 10, 12, 12, 4, 4));
    assert(-1 == test(-4, 2, -8, 8, 0, 0, -4, 6));
    assert(-1 == test(4, 4, 4, 6, 0, 2, 0, 0));
    assert(-1 == test(4, 4, 6, 4, 0, 2, 0, 0));
    assert(-1 == test(-2, -2, 4, 4, 10, 10, 6, 6));
    assert(-1 == test(0, 0, 2, 2, 4, 0, 1, 4));
    assert(-1 == test(2, 2, 2, 8, 4, 4, 6, 4));
    assert(-1 == test(4, 2, 4, 4, 0, 8, 10, 0));
  }
    assert(PT(2.5, 2.5) == closest_PT(-1, -1, 5, PT(0, 0)));
    assert(PT(3, 0)     == closest_PT(1, 0, -3, PT(0, 0)));
    assert(PT(0, 3)     == closest_PT(0, 1, -3, PT(0, 0)));

    assert(PT(3, 0)  == closest_PT(PT(3, 0), PT(3, 3), PT(0, 0)));
    assert(PT(2, -1) == closest_PT(PT(2, -1), PT(4, -1), PT(0, 0)));
    assert(PT(4, -1) == closest_PT(PT(2, -1), PT(4, -1), PT(5, 0)));

    line l(2, -5, -8);
    line para = line(2, -5, -8).parallel(PT(-6, -2));
    line perp = line(2, -5, -8).perpendicular(PT(-6, -2));
    assert(l.parallel(para) && l.perpendicular(perp));
    assert(l.slope() == 0.4);
    assert(para == line(-0.4, 1, -0.4)); //-0.4x+1y-0.4=0
    assert(perp == line(2.5, 1, 17));    //2.5x+1y+17=0
}