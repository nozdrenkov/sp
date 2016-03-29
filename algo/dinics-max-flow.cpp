typedef long long LL;

struct Edge {
  int u, v;
  LL flow, cap;
  Edge() {}
  Edge(int u, int v, LL cap) : u(u), v(v), flow(0), cap(cap) {}
};

class DinicMaxFlow {
  int n, s, t;
  LL flow;
  vector< vector<int> > g;
  vector<int> used, start, dist;

  bool bfs() {
    start.assign(n, 0);
    dist.assign(n, -1);
    dist[s] = 0;
    queue<int> q;
    q.push(s);
    while (q.size()) {
      int u = q.front();
      q.pop();
      for (int id : g[u]) {
        auto &e = edges[id];
        if (e.flow < e.cap && dist[e.v] == -1) {
          dist[e.v] = dist[u] + 1;
          q.push(e.v);
        }
      }
    }
    return dist[t] != -1;
  }

  LL dfs(int u, LL fl = -1) {
    if (fl == -1) used.assign(n, false);
    used[u] = true;
    if (u == t) return fl;
    for (int &i = start[u]; i < g[u].size(); ++i) {
      int id = g[u][i];
      auto &e = edges[id];
      int v = e.v;
      if (dist[v] == dist[u] + 1 && !used[v] && e.flow < e.cap) {
        LL can = e.cap - e.flow;
        LL df = dfs(v, fl == -1 ? can : min(can, fl));
        if (df > 0) {
          edges[id    ].flow += df;
          edges[id ^ 1].flow -= df;
          return df;
        }
      }
    }
    return 0;
  }

public:
  vector<Edge> edges;
  
  DinicMaxFlow(int n) : n(n) { g.resize(n); }

  int add(int u, int v, LL cap) {
    int idx = edges.size();
    g[u].push_back(idx);
    edges.emplace_back(u, v, cap);
    g[v].push_back(idx ^ 1);
    edges.emplace_back(v, u, 0);
    return idx;
  }

  LL calc(int ss, int tt) {
    s = ss, t = tt, flow = 0;
    while (bfs()) {
      while (LL add = dfs(s)) {
        flow += add;
      }
    }
    return flow;
  }
};