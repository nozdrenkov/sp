struct edge_t {
  int u, v, w;
  edge_t() {}
  edge_t(int u, int v, int w) : u(u), v(v), w(w) {}
  bool operator < (const edge_t &other) const {
    return w < other.w;
  }
  void read() {
    scanf("%d %d %d", &u, &v, &w);
    --u, --v;
  }
};

const int maxn = 555;
int dp[maxn];

void dinit(int n) {
  forn(i, n) {
    dp[i] = i;
  }
}

int dfind(int x) {
  return x == dp[x] ? x : dp[x] = dfind(dp[x]);
}

void dunion(int x, int y) {
  dp[dfind(x)] = dfind(y);
}

void solve() {
  int n, m;
  scanf("%d %d", &n, &m);
  vector<edge_t> edges(m);
  forn(i, m) edges[i].read();
  sort(all(edges));

  vi idx;
  int mst_w = 0;
  dinit(n);
  forn(i, edges.size()) {
    int u = edges[i].u;
    int v = edges[i].v;
    if (dfind(u) != dfind(v)) {
      mst_w += edges[i].w;
      idx.push_back(i);
      dunion(u, v);
    }
  }

  int cnt = 0;
  int sum = 0;
  for (int removed : idx) {
    dinit(n);
    int cur_w = 0;
    forn(i, edges.size()) {
      if (i != removed) {
        int u = edges[i].u;
        int v = edges[i].v;
        if (dfind(u) != dfind(v)) {
          cur_w += edges[i].w;
          dunion(u, v);
        }
      }
    }

    if (cur_w != mst_w) {
      cnt++;
      sum += edges[removed].w;
    }
  }

  printf("%d %d\n", cnt, sum);
}

int main() {

  solve();

  return 0;
}