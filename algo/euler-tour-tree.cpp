#include <bits/stdc++.h>

using namespace std;

struct node;
typedef node * pnode;

struct node {
  int u, v, sz, pr;
  pnode l, r, p;
  node() {}
  node(int u, int v) : u(u), v(v), sz(1), pr(rand()), l(0), r(0), p(0) {}
  int size() const {
    return this ? sz : 0;
  }
  void upd() {
    if (this) {
      sz = l->size() + 1 + r->size();
      p = 0;
      if (l) l->p = this;
      if (r) r->p = this;
    }
  }
  friend void merge(pnode l, pnode r, pnode &t) {
    if (l == 0) t = r;
    else if (r == 0) t = l;
    else if (l->pr < r->pr)
      merge(l, r->l, r->l), t = r;
    else
      merge(l->r, r, l->r), t = l;
    t->upd();
  }
  friend void split(pnode t, pnode &l, pnode &r, int x) {
    if (!t) return void(l = r = 0);
    if (t->l->size() + 1 > x)
      split(t->l, l, t->l, x), r = t;
    else
      split(t->r, t->r, r, x - t->l->size() - 1), l = t;
    l->upd(), r->upd();
  }
  friend pnode root(pnode v) {
    while (v->p) v = v->p;
    return v;
  }
  friend int index(pnode v) {
    int idx = v->l->size();
    while (v->p) {
      if (v == v->p->r) {
        idx += v->p->l->size() + 1;
      }
      v = v->p;
    }
    return idx;
  }
};

const int N = 1e5 + 100;
map<int, pnode> g[N];

pnode tree(int v) {
  if (g[v].empty()) return 0;
  return root(g[v].begin()->second);
}

// (A)[v->..](B) ==> [v->..](B)(A)
void expose(int v) {
  if (g[v].empty()) return;
  pnode edge = g[v].begin()->second;
  pnode l, r;
  split(root(edge), l, r, index(edge));
  merge(r, l, l);
}

// (uuuuu) [u->v] (vvvvv) [v->u]
void link(int u, int v) {
  expose(u);
  expose(v);
  pnode e1 = new node(u, v);
  pnode e2 = new node(v, u);
  pnode t = 0;
  merge(t, tree(u), t);
  merge(t, e1, t);
  merge(t, tree(v), t);
  merge(t, e2, t);
  g[u][v] = e1;
  g[v][u] = e2;
}

// (tree) [u->v] (subtree) [v->u] (tree)
void cut(int u, int v) {
  int l = index(g[u].find(v)->second);
  int r = index(g[v].find(u)->second);
  if (l > r) swap(l, r);
  pnode t = tree(u), mid, right, del;
  split(t, t, right, r + 1);
  split(t, t, del, r);
  delete del;
  split(t, t, mid, l + 1);
  split(t, t, del, l);
  delete del;
  merge(t, right, t);
  g[u].erase(v);
  g[v].erase(u);
}

bool check(int u, int v) {
  if (u == v) return true;
  pnode uu = tree(u);
  pnode vv = tree(v);
  if (!uu) return false;
  return uu == vv;
}

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
      link(u, v);
    } else if (op == 'D') {
      cut(u, v);
    } else {
      puts(check(u, v) ? "YES" : "NO");
      fflush(stdout);
    }
  }
}