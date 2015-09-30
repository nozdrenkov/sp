struct edge_t {
  int u, v, w;
  void read() {
    scanf("%d %d %d", &u, &v, &w);
    --u, --v;
  }
};

int n, m, k;
vvi g;
vector<edge_t> edges;
vi path(k);

vi dijkstra(int s) {
  vi dist(g.size(), -1);
  dist[s] = 0;

  priority_queue< pii, vector<pii>, greater<pii> > q;
  q.push(mp(0, s));

  while (q.size()) {
    int u = q.top().Y;
    int d = q.top().X;
    q.pop();

    if (dist[u] != d) continue;

    for (int id : g[u]) {
      int v = edges[id].u == u ? edges[id].v : edges[id].u;
      int d = edges[id].w;
      if (dist[v] == -1 || dist[v] > dist[u] + d) {
        dist[v] = dist[u] + d;
        q.push(mp(dist[v], v));
      }
    }
  }

  return dist;
}

void read() {
  scanf("%d %d %d", &n, &m, &k);
  forn(i, k) {
    int x; scanf("%d", &x);
  }
  g.resize(n);
  edges.resize(m);
  forn(i, m) {
    edges[i].read();
    g[edges[i].u].push_back(i);
    g[edges[i].v].push_back(i);
  }
}

void solve() {
  read();
  vi d1 = dijkstra(0);
  vi d2 = dijkstra(n - 1);
  int cnt = 0;
  for (auto &edge : edges) {
    int u = edge.u;
    int v = edge.v;
    cnt += d1[u] + edge.w + d2[v] == d1[n - 1] ||
           d1[v] + edge.w + d2[u] == d1[n - 1];
  }
  puts(cnt > k - 1 ? "yes" : "no");
}