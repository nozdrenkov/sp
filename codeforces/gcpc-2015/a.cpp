namespace solution {

  vi dijkstra(int s, const vector<vector<pii> > &g) {
    vi dist(g.size(), -1); dist[s] = 0;
    priority_queue<pii, vector<pii>, greater<pii> > q; q.push(mp(0, s));
    while (q.size()) {
      int u = q.top().Y;
      int d = q.top().X;
      q.pop();
      if (dist[u] != d) continue;
      for (auto &cur : g[u]) {
        int v = cur.X;
        int d = cur.Y;
        if (dist[v] == -1 || dist[v] > dist[u] + d) {
          q.push(mp(dist[v] = dist[u] + d, v));
        }
      }
    }
    return dist;
  }

  const int maxn = 16;
  int tm[maxn];
  int dist[maxn][maxn];

  int n, all_time, taxi_time;

  void read() {
    int p, m;
    scanf("%d %d %d %d %d", &n, &p, &m, &all_time, &taxi_time);

    vector<pii> places(p);
    bool fl = false;
    forn(i, p) {
      scanf("%d %d", &places[i].X, &places[i].Y);
      if (places[i].X == 0) {
        fl = true;
      }
    }
    if (!fl) {
      places.insert(places.begin(), mp(0, 0));
      ++p;
    }
    sort(all(places));
    forn(i, places.size()) {
      tm[i] = places[i].Y;
    }

    vector< vector<pii> > g(n);
    forn(i, m) {
      int u, v, w;
      scanf("%d %d %d", &u, &v, &w);
      g[u].push_back(mp(v, w));
      g[v].push_back(mp(u, w));
    }

    forn(i, places.size()) {
      vi d = dijkstra(places[i].X, g);
      forn(j, places.size()) {
        dist[i][j] = d[places[j].X];
      }
    }

    n = places.size();
  }

  int dp[1 << maxn][maxn][2];

  int bit(int mask, int i) {
    return (mask >> i) & 1;
  }

  void upd(int &v, int nval) {
    if (v == -1 || v > nval) {
      v = nval;
    }
  }

  void solve() {
    read();
    memset(dp, -1, sizeof(dp));
    dp[1 << 0][0][0] = tm[0];
    for (int mask = 1; mask < (1 << n); ++mask) {
      for (int from = 0; from < n; ++from) {
        if (bit(mask, from)) {
          for (int to = 0; to < n; ++to) {
            if (!bit(mask, to)) {
              int nmask = mask | (1 << to);
              if (dp[mask][from][0] != -1) {
                upd(dp[nmask][to][0], dp[mask][from][0] + tm[to] + dist[from][to]);
                upd(dp[nmask][to][1], dp[mask][from][0] + tm[to] + taxi_time);
              }
              if (dp[mask][from][1] != -1) {
                upd(dp[nmask][to][1], dp[mask][from][1] + tm[to] + dist[from][to]);
              }
            }
          }
        }
      }
    }
    forn(last, n) {
      int tm = dp[(1 << n) - 1][last][0] + dist[last][0];
      if (dp[(1 << n) - 1][last][0] != -1 && tm != -1 && tm <= all_time) {
        puts("possible without taxi");
        return;
      }
    }
    forn(last, n) {
      int tm = dp[(1 << n) - 1][last][1] + dist[last][0];
      if (dp[(1 << n) - 1][last][1] != -1 && tm != -1 && tm <= all_time) {
        puts("possible with taxi");
        return;
      }

    }
    forn(last, n) {
      if (dp[(1 << n) - 1][last][0] != -1 && dp[(1 << n) - 1][last][0] + taxi_time <= all_time) {
        puts("possible with taxi");
        return;
      }
    }

    puts("impossible");
  }
}
int main() {

  solution::solve();

  return 0;
}
