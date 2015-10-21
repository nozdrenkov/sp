#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

struct vec_t {
  int x, y;
  vec_t() {}
  vec_t(int x, int y) : x(x), y(y) {}
  void read() {
    scanf("%d %d", &x, &y);
  }
  bool operator < (const vec_t &other) {
    return tie(x, y) < tie(other.x, other.y);
  }
  bool operator == (const vec_t &other) {
    return tie(x, y) == tie(other.x, other.y);
  }
  vec_t operator - (const vec_t &other) const {
    return vec_t(x - other.x, y - other.y);
  }
  LL cross(const vec_t &b) const {
    return LL(x) * b.y - LL(y) * b.x;
  }
  double distTo(const vec_t &other) const {
    double a = abs(x - other.x);
    double b = abs(y - other.y);
    if (a > b) swap(a, b);
    return sqrt(2.0) * a + b - a;
  }
};

template<class T>
vector<T> convex_hull(vector<T> a) {
  if (a.size() < 3) {
    return a;
  }
  sort(a.begin(), a.end());
  int n = a.size(), k = 0;
  vector<T> st(n * 2);
  for (int i = 0; i < n; ++i) {
    while (k > 1 && (st[k - 1] - st[k - 2]).cross(a[i] - st[k - 2]) >= 0) {
      --k;
    }
    st[k++] = a[i];
  }
  for (int i = n - 2, r = k; i >= 0; --i) {
    while (k > r && (st[k - 1] - st[k - 2]).cross(a[i] - st[k - 2]) >= 0) {
      --k;
    }
    st[k++] = a[i];
  }
  st.resize(k - 1);
  return st;
}

pair<int, int> get(const vector<vec_t> &a) {
  int ii = 0, jj = 0;
  double ans = 0;
  for (int i = 0; i < a.size(); ++i) {
    int l = i, r = i + a.size();
    while (r - l > 2) {
      int m1 = (l + l + r) / 3;
      int m2 = (l + r + r) / 3;
      double f1 = a[i].distTo(a[m1 % a.size()]);
      double f2 = a[i].distTo(a[m2 % a.size()]);
      if (f1 > f2) {
        r = m2;
      } else {
        l = m1;
      }
    }
    int idx = l;
    double mx = a[i].distTo(a[l % a.size()]);
    for (int j = l + 1; j <= r; ++j) {
      double d = a[i].distTo(a[j % a.size()]);
      if (d > mx) {
        mx = d;
        idx = j;
      }
    }
    if (mx > ans) {
      ans = mx;
      ii = i;
      jj = idx % a.size();
    }
  }
  return make_pair(ii, jj);
}

int n;
vector<vec_t> a;

void read() {
  scanf("%d", &n);
  a.resize(n);
  for (int i = 0; i < n; ++i) {
    a[i].read();
  }
}

void process() {
  auto hull = convex_hull(a);
  auto res = get(hull);
  int u = find(a.begin(), a.end(), hull[res.first]) - a.begin();
  int v = find(a.begin(), a.end(), hull[res.second]) - a.begin();
  if (u > v) {
    swap(u, v);
  }
  printf("%d %d\n", u + 1, v + 1);
}

int main() {
  // freopen("input.txt", "r", stdin);
  read();
  process();
  return 0;
}