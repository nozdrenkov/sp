#include <bits/stdc++.h>

using namespace std;

const int oo = 1e9;
const int N = 15;
const int K = 15;
const int M = N * N;
const int Q = 100;

int n, k, c, m, q;
struct input_edge_t {
  int u, v, w;
} inpe[M];

int a[Q + 1][N];

void read() {
  scanf("%d %d %d %d", &n, &k, &c, &m);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    --u, --v;
    inpe[i] = { u, v, w };
  }
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    for (int j = 0; j < k; ++j) {
      int cost;
      scanf("%d", &cost);
      a[i + 1][j] = a[i][j] + cost;
    }
  }
}

class mcmf_t {
  int n, s, t, flow, cost;
  struct edge_t {
    int u, v, flow, cap, cost;
    edge_t(int u, int v, int c, int w)
      : u(u), v(v), flow(0), cap(c), cost(w) {}
  };
  vector<edge_t> edges;
  vector<int> dist, prev;
  bool fb() {
    fill(dist.begin(), dist.end(), -1);
    dist[s] = 0;
    for (int run = 1; run; ) {
      run = 0;
      for (int i = 0; i < edges.size(); ++i) {
        int u = edges[i].u;
        int v = edges[i].v;
        if (dist[u] != -1 && edges[i].flow < edges[i].cap) {
          if (dist[v] == -1 || dist[v] > dist[u] + edges[i].cost) {
            dist[v] = dist[u] + edges[i].cost;
            prev[v] = i;
            run = 1;
          }
        }
      }
    }
    return dist[t] != -1;
  }
  void relax() {
    int val = oo;
    for (int v = t; v != s; v = edges[prev[v]].u) {
      val = min(val, edges[prev[v]].cap - edges[prev[v]].flow);
    }
    for (int v = t; v != s; v = edges[prev[v]].u) {
      cost += val * edges[prev[v]].cost;
      edges[prev[v] ^ 0].flow += val;
      edges[prev[v] ^ 1].flow -= val;
    }
    flow += val;
  }
public:
  mcmf_t(int n) : n(n) {
    dist.assign(n, -1);
    prev.assign(n, -1);
  }
  pair<int, int> calc(int ss, int tt) {
    s = ss, t = tt, flow = 0, cost = 0;
    while (fb()) {
      relax();
    }
    return make_pair(flow, cost);
  }
  void add_edge(int u, int v, int c, int w) {
    edges.emplace_back(u, v, c, +w);
    edges.emplace_back(v, u, 0, -w);
  }
};

int cur[K];

int get(int l, int r) {
  mcmf_t mcmf(n + k + 2);
  const int s = n + k;
  const int t = s + 1;
  int need = 0;
  for (int i = 0; i < k; ++i) {
    cur[i] = a[r + 1][i] - a[l][i];
    need += !!cur[i];
  }
  for (int i = 0; i < m; ++i) {
    int task = inpe[i].v;
    mcmf.add_edge(inpe[i].u, n + inpe[i].v, 1, inpe[i].w * cur[task]);
  }
  for (int i = 0; i < n; ++i) {
    mcmf.add_edge(s, i, 1, 0);
  }
  for (int i = 0; i < k; ++i) {
    if (cur[i] > 0) {
      mcmf.add_edge(i + n, t, 1, 0);
    }
  }
  auto ans = mcmf.calc(s, t);
  return ans.first == need ? ans.second : oo;
}

int dp[Q + 1];
void process() {
  fill(dp, dp + Q + 1, oo);
  dp[0] = 0;
  for (int r = 0; r < q; ++r) {
    for (int l = 0; l <= r; ++l) {
      dp[r + 1] = min(dp[r + 1], get(l, r) + c + dp[l]);
    }
  }
  printf("%d\n", dp[q]);
}

int main() {
  //freopen("input.txt", "r", stdin);
  read();
  process();
  return 0;
}