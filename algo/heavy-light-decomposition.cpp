#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < n; ++i)

const int oo = 1e9;
const int N = 1e5 + 100;
const int K = 17;

class SegmTree {
  int n, *t;
  void upd(int v, int tl, int tr, int idx, int val) {
    if (tl == tr) {
      t[v] = val;
      return;
    }
    int tm = (tl + tr) / 2;
    if (idx <= tm)
      upd(2 * v + 1, tl, tm, idx, val);
    else
      upd(2 * v + 2, tm + 1, tr, idx, val);
    t[v] = max(t[2 * v + 1], t[2 * v + 2]);
  }
  int get(int v, int tl, int tr, int l, int r) {
    if (l > r) return -oo;
    if (l == tl && r == tr) return t[v];
    int tm = (tl + tr) / 2;
    int v1 = get(2 * v + 1, tl, tm, l, min(r, tm));
    int v2 = get(2 * v + 2, tm + 1, tr, max(l, tm + 1), r);
    return max(v1, v2);
  }
public:
  void init(int n) {
    this->n = n;
    t = new int[4 * n]();
  }
  void upd(int i, int v) {
    upd(0, 0, n - 1, i, v);
  }
  int get(int l, int r) {
    return get(0, 0, n - 1, l, r);
  }
} st[N];

int n, q;
vector<int> g[N];
int x[N];

int par[N], sz[N], up[N][K], tin[N], tout[N], T;
// int mx[N];

void dfs(int u, int p) {
  tin[u] = T++;
  par[u] = p;
  sz[u] = 1;
  //mx[u] = -1;
  for (int v : g[u]) {
    if (v != p) {
      dfs(v, u);
      sz[u] += sz[v];
      //if (mx[u] == -1 || sz[v] > sz[mx[u]]) {
      //  mx[u] = v;
      //}
    }
  }
  tout[u] = T++;
}

int ancestor(int a, int v) {
  return tin[a] <= tin[v] && tout[v] <= tout[a];
}

int lca(int u, int v) {
  for (int l = K - 1; l >= 0; --l) {
    if (!ancestor(up[u][l], v)) {
      u = up[u][l];
    }
  }
  return ancestor(u, v) ? u : par[u];
}

int no[N], pos[N];
int len[N], top[N], cnt;

void hld(int u, int p) {
  if (u == p || 2 * sz[u] <= sz[p]) // if (u != mx[p])
    no[u] = cnt, top[cnt] = u, ++cnt;
  else
    no[u] = no[p];
  pos[u] = len[no[u]]++;
  for (int v : g[u]) {
    if (v != p) {
      hld(v, u);
    }
  }
}

int query_up(int u, int p) {
  int ans = -oo;
  while (no[u] != no[p]) {
    ans = max(ans, st[no[u]].get(0, pos[u]));
    u = par[top[no[u]]];
  }
  return max(ans, st[no[u]].get(pos[p], pos[u]));
}

void update(int u, int val) {
  st[no[u]].upd(pos[u], val);
}

int query(int u, int v) {
  int p = lca(u, v);
  int v1 = query_up(u, p);
  int v2 = query_up(v, p);
  return max(v1, v2);
}

void build() {
  dfs(0, 0);
  forn(v, n) up[v][0] = par[v];
  forn(k, K - 1) {
    forn(v, n) {
      up[v][k + 1] = up[up[v][k]][k];
    }
  }
  hld(0, 0);
  forn(i, cnt) {
    st[i].init(len[i]);
  }
}

void read() {
  scanf("%d", &n);
  forn(i, n - 1) {
    int u, v; scanf("%d %d", &u, &v);
    g[u - 1].push_back(v - 1);
    g[v - 1].push_back(u - 1);
  }
}

void process() {
  scanf("%d", &q);
  while (q--) {
    char t; scanf(" %c", &t);
    int u, v; scanf("%d %d", &u, &v);
    if (t == 'I') {
      update(u - 1, x[u - 1] += v);
    }
    else {
      printf("%d\n", query(u - 1, v - 1));
    }
  }
}

int main() {
  //freopen("input.txt", "r", stdin);
  read();
  build();
  process();
  return 0;
}
