struct edge_t {
  int u, v, f, cap;
  edge_t() {}
  edge_t(int u, int v, int c) : u(u), v(v), f(c), cap(c) {}
};

class dinic_mf_t {
  int n, s, t, flow;
  vvi g;
  vi start, dist, used;
  bool bfs() {
    start.assign(n, 0);
    dist.assign(n, -1); dist[s] = 0;
    queue<int> q; q.push(s);
    while (q.size()) {
      int u = q.front(); q.pop();
      for (int id : g[u]) {
        int v = edges[id].v;
        int f = edges[id].f;
        if (f > 0 && dist[v] == -1) {
          dist[v] = dist[u] + 1;
          q.push(v);
        }
      }
    }
    return dist[t] != -1;
  }

  int dfs(int u, int fl = -1) {
    if (fl == -1) used.assign(n, false); used[u] = true;
    if (u == t) return fl;
    for (int &i = start[u]; i < g[u].size(); ++i) {
      int id = g[u][i];
      int v = edges[id].v;
      int f = edges[id].f;
      if (f > 0 && !used[v] && dist[v] == dist[u] + 1) {
        int df = dfs(v, fl == -1 ? f : min(f, fl));
        if (df > 0) {
          edges[id].f -= df;
          edges[id ^ 1].f += df;
          return df;
        }
      }
    }
    return 0;
  }

public:
  vector<edge_t> edges;
  dinic_mf_t(int n) : n(n) {
    g.resize(n);
  }
  void add_edge(int u, int v, int c) {
    g[u].pb(edges.size()); edges.emplace_back(u, v, c);
    g[v].pb(edges.size()); edges.emplace_back(v, u, 0);
  }
  int calc(int ss, int tt) {
    s = ss, t = tt, flow = 0;
    while (bfs()) {
      while (int add = dfs(s)) {
        flow += add;
      }
    }
    return flow;
  }
};

void solve() {
  int n; cin >> n;
  const int s = 2 * n;
  const int t = 2 * n + 1;
  dinic_mf_t mf(2 * n + 2);
  forn(i, n) {
    mf.add_edge(s, i, 1);
    mf.add_edge(n + i, t, 1);
  }
  forn(i, n) {
    int k; cin >> k;
    vi adj(k); cin >> adj;
    forn(j, k) {
      mf.add_edge(i, n + adj[j], 1);
    }
  }
  cout << n - mf.calc(s, t) << endl;
}