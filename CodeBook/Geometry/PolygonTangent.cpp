
/*
  Polygon is given in clockwise order.
  second = true/false. gives one tangent and the other
*/

int nxt(int i, int num_v) { return (i + 1) % num_v; }
int prev(int i, int num_v) { return (i - 1 + num_v) % num_v; }

int dir(const PT& p, const PT& q, const PT& r, bool second) {
  if (!second) return cross(q-p,r-p) >= -eps;
  return cross(q-p,r-p) <= eps;
}

bool is_tangent(const vector<PT>& polygon, int indx, const PT& p, bool second) {
  int sz = polygon.size();
  int a = nxt(indx, sz);
  int b = prev(indx, sz);
  if (dir(p, polygon[indx], polygon[a], second) &&
      dir(p, polygon[indx], polygon[b], second))
    return true;
  return false;
}

int find_tangent(const vector<PT>& polygon, PT p, bool second) {
  int sz = polygon.size();
  int AA = 1, BB = sz - 1;
  if (is_tangent(polygon, 0, p, second)) return 0;

  while (AA <= BB) {
    int CC = (AA + BB) / 2;

    if (is_tangent(polygon, CC, p, second)) return CC;
    if (is_tangent(polygon, AA, p, second)) return AA;
    int c = dir(p, polygon[CC], polygon[nxt(CC, sz)], second);
    int a = dir(p, polygon[AA], polygon[nxt(AA, sz)], second);

    if (a != c) {
      if (!c) AA = nxt(CC, sz);
      else BB = prev(CC, sz);
    } else {
      if (c == dir(p, polygon[AA], polygon[CC], second)) AA = nxt(CC, sz);
      else BB = prev(CC, sz);
    }
  }
  return -1;
}
