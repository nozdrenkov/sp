#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int oo = 1e9;
const int mod = 99990001;

struct num_t {
  int a, b;
  num_t() : a(1), b(0) {}
  void add(int x) {
    b += x;
    if (b >= mod) {
      b -= mod;
    }
  }
  void mul(int x) {
    a = (a * 1LL * x) % mod;
    b = (b * 1LL * x) % mod;
  }
  int get(int x) const {
    return ((a * 1LL * x) % mod + b) % mod;
  }
};

struct edge_t {
  int u, v, w;
  edge_t() {}
  edge_t(int u, int v, int w) : u(u), v(v), w(w) {}
};

int rnd() {
  return (rand() << 16) ^ rand();
}

struct node_t;
typedef node_t * pnode;

struct node_t {
  int val, mn, sz, pr;
  num_t num;
  pnode l, r, par;
  node_t(int val)
      : val(val), mn(val), sz(1), pr(rnd()), l(0), r(0), par(0) {}
  int size() const {
    return this ? sz : 0;
  }
  int min() const {
    return this ? mn : oo;
  }
  void upd() {
    if (this) {
      sz = l->size() + 1 + r->size();
      mn = std::min(val, std::min(l->min(), r->min()));
      if (l) l->par = this;
      if (r) r->par = this;
      par = 0;
    }
  }
  void out() {
    if (this) {
      l->out();
      cout << val << " ";
      r->out();
    }
  }
  pnode root() {
    pnode v = this;
    while (v->par) {
      v = v->par;
    }
    return v;
  }
  int index() {
    pnode v = this;
    int idx = v->l->size();
    while (v->par) {
      if (v->par->r == v) {
        idx += v->par->l->size() + 1;
      }
      v = v->par;
    }
    return idx;
  }
  friend void split(pnode t, pnode &l, pnode &r, int k) {
    if (t == 0) l = r = 0;
    else if (t->l->size() + 1 > k)
      split(t->l, l, t->l, k), r = t;
    else
      split(t->r, t->r, r, k - t->l->size() - 1), l = t;
    l->upd(), r->upd();
  }
  friend void merge(pnode l, pnode r, pnode &t) {
    if (l == 0) t = r;
    else if (r == 0) t = l;
    else if (l->pr < r->pr)
      merge(l->r, r, l->r), t = l;
    else
      merge(l, r->l, r->l), t = r;
    t->upd();
  }
};


int n;
vector< vector<int> > g;
vector<edge_t> edges;

void read() {
  cin >> n;
  edges.resize(n - 1);
  g.resize(n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    --u, --v;
    edges[i] = edge_t(u, v, w);
    g[u].push_back(v);
    g[v].push_back(u);
  }
}

int timer = 0;
vector<int> tin, tout;
vector<pnode> open, close;
pnode tree = 0;

bool ancestor(int anc, int v) {
  return tin[anc] <= tin[v] && tout[v] <= tout[anc];
}

void dfs(int u, int prev = -1) {
  tin[u] = timer++;
  open[u] = new node_t(u);
  merge(tree, open[u], tree);
  for (int i = 0; i < g[u].size(); ++i) {
    int v = g[u][i];
    if (v != prev) {
      dfs(v, u);
    }
  }
  tout[u] = timer++;
  close[u] = new node_t(u);
  merge(tree, close[u], tree);
}

void init() {
  timer = 0;
  tin.assign(n, 0);
  tout.assign(n, 0);
  open.resize(n);
  close.resize(n);
  dfs(0);
}

int remove(int e) {
  int u = edges[e].u;
  int v = edges[e].v;
  if (!ancestor(u, v)) swap(u, v);

  pnode t = open[v]->root();
  int l = open[v]->index();
  int r = close[v]->index();
  num_t num = t->num;

  pnode t1, mid, t2;
  split(t, mid, t2, r + 1);
  split(mid, t1, mid, l);
  merge(t1, t2, t);
  
  int res = num.get(edges[e].w);

  pnode small = t, big = mid;
  if (small->size() > big->size() ||
      small->size() == big->size() &&
      small->min() > big->min()) {
    swap(small, big);
  }

  small->num = num;
  small->num.mul(res);

  big->num = num;
  big->num.add(res);

  return res;
}

void process() {
  for (int i = 0; i < n - 1; ++i) {
    int e; cin >> e; --e;
    cout << remove(e) << endl;
  }
}

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false);
  read();
  init();
  process();
  return 0;
}