#include <bits/stdc++.h>

using namespace std;

struct node;
typedef node* pnode;

struct node {
  pnode l, r, p;
  int rev, val, func;
  node() : l(0), r(0), p(0), rev(0), val(0), func(0) {}
  bool left() const {
    return this && p && p->l == this;
  }
  bool root() const {
    return !p || p->l != this && p->r != this;
  }
  int get() {
    return this ? func : 0;
  }
  void push() {
    if (this && rev) {
      swap(l, r);
      if (l) l->rev ^= 1;
      if (r) r->rev ^= 1;
      rev = 0;
    }
  }
  void upd() {
    if (this) {
      func = max(max(l->get(), r->get()), val);
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
  p->upd(), x->upd();
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

void access(pnode x) {
  pnode last = 0;
  for (pnode v = x; v; v = v->p) {
    splay(v);
    v->r = last;
    last = v;
    v->upd();
  }
  splay(x);
}

void make_root(pnode x) {
  access(x);
  x->rev ^= 1;
}

void link(pnode x, pnode y) {
  make_root(x);
  access(y);
  x->p = y;
}

void upd(pnode x, int val) {
  splay(x);
  x->val += val;
  x->upd();
}

int get(pnode x, pnode y) {
  make_root(x);
  access(y);
  return y->get();
}

const int N = 1e5 + 100;
node tree[N];

void read() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    u--, v--;
    link(tree + u, tree + v);
  }
}

void process() {
  int q;
  scanf("%d", &q);
  while (q--) {
    char t;
    int u, v;
    scanf(" %c %d %d", &t, &u, &v);
    if (t == 'I') {
      upd(tree + u - 1, v);
    } else {
      printf("%d\n", get(tree + u - 1, tree + v - 1));
    }
  }
}

int main() {
  read();
  process();
}