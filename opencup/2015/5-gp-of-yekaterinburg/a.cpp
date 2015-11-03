#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

int sign(LL x) {
  if (x < 0) return -1;
  if (x > 0) return +1;
  return 0;
}

struct vec_t {
  int x, y, id;
  vec_t() {}
  vec_t(int x, int y) : x(x), y(y), id(-1) {}
  vec_t operator - (const vec_t &o) const {
    return vec_t(x - o.x, y - o.y);
  }
  vec_t operator + (const vec_t &o) const {
    return vec_t(x + o.x, y + o.y);
  }
  vec_t operator / (int val) const {
    return vec_t(x / val, y / val);
  }
  LL cross(const vec_t &b) const {
    return LL(x) * b.y - LL(y) * b.x;
  }
  void read() {
    scanf("%d %d", &x, &y);
  }
};

struct triangle_t;
typedef triangle_t * pnode;
struct triangle_t {
  vector<vec_t> a;
  vector<pnode> to;
  triangle_t() {}
  triangle_t(const vec_t &u, const vec_t &v, const vec_t &w) {
    a.resize(3);
    a[0] = u;
    a[1] = v;
    a[2] = w;
  }
  bool contains(const vec_t &p) {
    int mn = +100, mx = -100;
    for (int i = 0; i < 3; ++i) {
      vec_t u = a[(i + 1) % 3] - a[i];
      vec_t v = p - a[i];
      int sg = sign(u.cross(v));
      mn = min(mn, sg);
      mx = max(mx, sg);
    }
    return !(mn == -1 && mx == +1);
  }
  void print() {
    if (a.size()) {
      printf("3");
      if ((a[0] - a[1]).cross(a[2] - a[1]) < 0) {
        swap(a[0], a[2]);
      }
      for (int i = 0; i < 3; ++i) {
        printf(" %d", a[i].id + 1);
      }
    }
    printf("\n");
  }
};

void build(pnode v, const vector<vec_t> &pts) {
  if (pts.empty()) return;
  vec_t o = pts[rand() % pts.size()];
  v->to.push_back(new triangle_t(v->a[0], v->a[1], o));
  v->to.push_back(new triangle_t(v->a[0], o, v->a[2]));
  v->to.push_back(new triangle_t(o, v->a[1], v->a[2]));
  vector<vec_t> partition[3];
  for (auto &p : pts) {
    if (p.id != o.id) {
      int part = 0;
      for (pnode tr : v->to) {
        if (tr->contains(p)) {
          partition[part].push_back(p);
          break;
        }
        ++part;
      }
    }
  }
  for (int i = 0; i < 3; ++i) {
    build(v->to[i], partition[i]);
  }
}

pnode build(vector<vec_t> a) {
  pnode root = new triangle_t();
  root->to.push_back(new triangle_t(a[0], a[1], a[2]));
  root->to.push_back(new triangle_t(a[0], a[3], a[2]));
  a.erase(a.begin(), a.begin() + 4);
  random_shuffle(a.begin(), a.end());
  vector<vec_t> partition[2];
  for (auto &p : a) {
    int part = 0;
    for (pnode tr : root->to) {
      if (tr->contains(p)) {
        partition[part].push_back(p);
        break;
      }
      ++part;
    }
  }
  for (int i = 0; i < 2; ++i) {
    build(root->to[i], partition[i]);
  }
  return root;
}

vec_t o;

void query(pnode root, const vec_t &p) {
  stack<pnode> q;
  q.push(root);
  while (q.size()) {
    pnode u = q.top();
    q.pop();
    if (u->to.empty()) {
      u->print();
      o = (u->a[0] + u->a[1] + u->a[2]) / 3;
      return;
    }
    for (pnode v : u->to) {
      if (v->contains(p)) {
        q.push(v);
        break;
      }
    }
  }
  assert(false);
}

int main() {
  //freopen("input.txt", "r", stdin);
  int n; scanf("%d", &n);
  vector<vec_t> a(n);
  for (int i = 0; i < n; ++i) {
    a[i].read();
    a[i].id = i;
  }
  pnode tree = build(a);
  int w = abs(a[0].x - a[1].x);
  int h = abs(a[0].y - a[3].y);
  vec_t r = a[3];

  int k; scanf("%d", &k);
  vec_t start; start.read();
  query(tree, start); --k;
  while (k--) {
    vec_t sh; sh.read();
    int x = r.x + ((o.x + sh.x + w) % w);
    int y = r.y + ((o.y + sh.y + h) % h);
    query(tree, vec_t(x, y));
  }
  return 0;
}
