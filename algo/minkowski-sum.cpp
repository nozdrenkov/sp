#define forn(i, n) for (int i = 0; i < n; ++i)
#define all(a) a.begin(), a.end()

// comparison by angle
bool by_angle(const vec_t &a, const vec_t &b) {
  return atan2((long double)a.y, a.x) < atan2((long double)b.y, b.x);
}

// comparison by cross products
bool by_angle(const vec_t &a, const vec_t &b) {
  bool fa = a.x > 0 || (a.x == 0 && a.y > 0);
  bool fb = b.x > 0 || (b.x == 0 && b.y > 0);
  return fa == fb ? a.cross(b) > 0 : fa < fb;
}

// a and b should be convex hulls with vertices ordered counterclockwise
vector<vec_t> minkowski_sum(const vector<vec_t> &a, const vector<vec_t> &b) {
  if (a.empty() || b.empty()) {
    return vector<vec_t>();
  }
  vector<vec_t> aa(a.size()), bb(b.size());
  forn(i, a.size()) aa[i] = a[(i + 1) % a.size()] - a[i];
  forn(i, b.size()) bb[i] = b[(i + 1) % b.size()] - b[i];

  auto ma = min_element(all(aa), by_angle);
  rotate(aa.begin(), ma, aa.end());

  auto mb = min_element(all(bb), by_angle);
  rotate(bb.begin(), mb, bb.end());

  vector<vec_t> ans;
  merge(all(aa), all(bb), back_inserter(ans), by_angle);
  partial_sum(all(ans), ans.begin());

  vec_t shift = *min_element(all(a)) +
                *min_element(all(b)) -
                *min_element(all(ans));

  for (auto &v : ans) v = v + shift;
  return ans;
}
