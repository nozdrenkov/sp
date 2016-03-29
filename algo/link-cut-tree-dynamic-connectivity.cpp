#include <bits/stdc++.h>

using namespace std;

struct node;
typedef node * pnode;

struct node {
  pnode l, r, p;
  node() : l(0), r(0), p(0) {}
  int rev;
  bool root() const {
    return !p || p->l != this && p->r != this;
  }
  bool left() const {
    return this && p && p->l == this;
  }
  void push() {
    if (this && rev) {
      swap(l, r);
      if (l) l->rev ^= 1;
      if (r) r->rev ^= 1;
      rev = 0;
    }
  }
};

void connect(pnode x, pnode p, bool left) {
  if (x) x->p = p;
  (left ? p->l : p->r) = x;
}

void rotate(pnode x) {
  pnode p = x->p;
  pnode g = p->p;
  pnode l = x->l;
  pnode r = x->r;
  bool xleft = x->left();
  bool pleft = p->left();
  bool proot = p->root();
  connect(xleft ? r : l, p, xleft);
  connect(p, x, !xleft);
  if (proot) x->p = g;
  else connect(x, g, pleft);
}

void splay(pnode x) {
  while (!x->root()) {
    pnode p = x->p;
    pnode g = p->p;
    g->push();
    p->push();
    x->push();
    if (!p->root()) rotate(x->left() ^ p->left() ? x : p);
    rotate(x);
  }
  x->push();
}

pnode access(pnode x) {
  pnode last = 0;
  for (pnode v = x; v; v = v->p) {
    splay(v);
    v->r = last;
    last = v;
  }
  splay(x);
  return last;
}

void make_root(pnode x) {
  access(x);
  x->rev ^= 1;
}

void link(pnode u, pnode v) {
  make_root(u);
  access(v);
  u->p = v;
}

void cut(pnode u, pnode v) {
  make_root(u);
  access(v);
  v->l->p = 0;
  v->l = 0;
}

bool connected(pnode u, pnode v) {
  if (u == v) return true;
  access(u);
  access(v);
  return u->p != 0;
}

pnode lca(pnode x, pnode y) {
  access(x);
  return access(y);
}

const int N = 1e5 + 100;
node tree[N];

int main() {
  int n;
  scanf("%d", &n);
  while (true) {
    char op;
    scanf(" %c", &op);
    if (op == 'E') break;
    int u, v;
    scanf("%d %d", &u, &v);
    if (op == 'C') {
      link(tree + u, tree + v);
    } else if (op == 'D') {
      cut(tree + u, tree + v);
    } else {
      puts(connected(tree + u, tree + v) ? "YES" : "NO");
      fflush(stdout);
    }
  }
}
