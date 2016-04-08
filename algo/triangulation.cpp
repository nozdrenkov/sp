#include <bits/stdc++.h>

typedef long long LL;

using namespace std;

struct Vec {
  int x, y;
  Vec() : x(0), y(0) {}
  Vec(int x, int y) : x(x), y(y) {}
  Vec operator - (const Vec &other) const {
    return Vec(x - other.x, y - other.y);
  }
  LL cross(const Vec &other) const {
    return LL(x) * other.y - LL(y) * other.x;
  }
};

typedef array<int, 3> Triangle;

int sign(LL x) {
  if (x < 0) return -1;
  if (x > 0) return +1;
  return 0;
}

bool contains(const Vec &a, const Vec &b, const Vec &c, const Vec &p) {
  int s0 = sign((b - a).cross(p - a));
  int s1 = sign((c - b).cross(p - b));
  int s2 = sign((a - c).cross(p - c));
  return !(min({ s0, s1, s2 }) == -1 && max({ s0, s1, s2 }) == +1);
}

bool convex(const Vec &a, const Vec &b, const Vec &c) {
  return sign((b - a).cross(c - a)) > 0;
}

// O(n ^ 2)
vector<Triangle> triangulate(const vector<Vec> &a) {
  const int n = a.size();
  if (n < 3) return {};

  int vx_cnt = n;

  vector<int> in_poly(n, true), in_ears(n, false);
  vector<int> prev(n), next(n);
  for (int i = 0; i < n; ++i) {
    prev[i] = (i - 1 + n) % n;
    next[i] = (i + 1) % n;
  }

  auto is_ear = [&](int id) {
    if (!convex(a[prev[id]], a[id], a[next[id]])) return false;
    for (int i = 0; i < n; ++i) {
      if (in_poly[i]) {
        if (i != id && i != prev[id] && i != next[id]) {
          if (contains(a[prev[id]], a[id], a[next[id]], a[i])) {
            return false;
          }
        }
      }
    }
    return true;
  };

  queue<int> q;
  
  auto update_status = [&](int x) {
    bool ear = is_ear(x);
    if (!in_ears[x] && ear) {
      q.push(x);
    }
    in_ears[x] = ear;
  };

  for (int i = 0; i < n; ++i) {
    update_status(i);
  }

  vector<Triangle> ans;

  while (vx_cnt > 3) {
    assert(q.size() > 0);

    int id = q.front(); q.pop();
    if (!in_ears[id]) continue;

    int pr = prev[id];
    int nx = next[id];
    ans.push_back({ pr, id, nx });

    prev[nx] = pr;
    next[pr] = nx;
    in_poly[id] = false;
    in_ears[id] = false;
    vx_cnt--;

    update_status(pr);
    update_status(nx);
  }

  Triangle last;
  int pos = 0;
  for (int i = 0; i < n; ++i) {
    if (in_poly[i]) {
      last[pos++] = i;
    }
  }
  assert(pos == 3);

  ans.push_back(last);
  return ans;
}
