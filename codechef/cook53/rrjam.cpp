#include <bits/stdc++.h>
#define forn(i, n) for (int i = 0; i < int(n); ++i)
using namespace std;
typedef long long LL;

int n;
vector<LL> need;

struct node_t;
typedef node_t * pnode;
struct node_t {
  LL x, y;
  pnode l, r;
  node_t() : x(0), y(0), l(0), r(0) {}
  pnode clone() const {
    pnode res = new node_t();
    res->x = x;
    res->y = y;
    res->l = l;
    res->r = r;
    return res;
  }
};

pnode build(pnode &v, int tl, int tr) {
  if (!v) v = new node_t();
  if (tl != tr) {
    int tm = (tl + tr) / 2;
    build(v->l, tl, tm);
    build(v->r, tm + 1, tr);
  }
  return v;
}

LL val(LL x, LL y, int idx) {
  return x + LL(idx) * y;
}

pnode add(pnode v, int tl, int tr, int l, int r, LL x, LL y) {
  if (l > r) return 0;
  if (l == tl && r == tr) {
    pnode nv = v->clone();
    nv->x += x;
    nv->y += y;
    return nv;
  }
  int tm = (tl + tr) / 2;
  pnode nv = v->clone();
  pnode left = add(v->l, tl, tm, l, min(r, tm), x, y);
  LL right_x = x;
  if (l < tm + 1) {
    right_x = val(x, y, tm + 1 - l);
  }
  pnode right = add(v->r, tm + 1, tr, max(l, tm + 1), r, right_x, y);
  if (left) nv->l = left;
  if (right) nv->r = right;
  return nv;
}

LL get(pnode v, int tl, int tr, int idx, LL cur_x = 0, LL cur_y = 0) {
  cur_x += v->x;
  cur_y += v->y;
  if (tl == tr) {
    return cur_x;
  }
  int tm = (tl + tr) / 2;
  if (idx <= tm) {
    return get(v->l, tl, tm, idx, cur_x, cur_y);
  } else {
    return get(v->r, tm + 1, tr, idx, val(cur_x, cur_y, tm + 1 - tl), cur_y);
  }
}

vector<pnode> tree;

int main() {
  // freopen("input.txt", "r", stdin);
  scanf("%d", &n);
  vector<int> a(n), b(n);
  forn(i, n) scanf("%d", &a[i]);
  forn(i, n) scanf("%d", &b[i]);
  need.resize(n);
  forn(i, n) {
    need[i] = max(0LL, LL(b[i]) - a[i]);
  }

  tree.push_back(0);
  build(tree[0], 0, n - 1);
  int m;
  scanf("%d", &m);
  forn(i, m) {
    int l, r, x, y;
    scanf("%d %d %d %d", &l, &r, &x, &y);
    --l, --r;
    tree.push_back(add(tree.back(), 0, n - 1, l, r, x, y));
  }

  for (int i = 0; i < n; ++i) {
    int l = -1, r = m + 1;
    while (r - l > 1) {
      int mid = (l + r) / 2;
      if (get(tree[mid], 0, n - 1, i) >= need[i]) {
        r = mid;
      } else {
        l = mid;
      }
    }
    if (i) printf(" ");
    printf("%d", r == m + 1 ? -1 : r);
  }
  printf("\n");
  return 0;
}