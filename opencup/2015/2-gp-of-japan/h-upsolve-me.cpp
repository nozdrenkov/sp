#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> Pt;
#define prev prev_ms
#define all(a) a.begin(), a.end()
#define X first
#define Y second

const int oo = 1e9;

double sqr(double x) {
  return x * x;
}

double distance(const Pt &a, const Pt &b) {
  double d = sqrt(sqr(a.X - b.X) + sqr(a.Y - b.Y));
  return d;
}

bool double_equal(double a, double b) {
  return fabs(a - b) < 1e-9;
}

struct Edge {
  int from, to, flow, cap;
  double cost;
  Edge() {}
  Edge(int from, int to, int cap, double cost) :
    from(from), to(to), flow(0), cap(cap), cost(cost) {}
};

vector<Edge> edges;

int n, s, t;

vector<double> dist;
vector<int> prev;

bool fb() {
  prev.assign(n, -1);
  dist.assign(n, oo);
  dist[s] = 0;
  for (int run = 1, it = 1; run; ++it) {
    run = 0;
    for (int id = 0; id < edges.size(); ++id) {
      auto &e = edges[id];
      if (!double_equal(dist[e.from], oo)) {
        if (e.flow < e.cap) {
          if (dist[e.to] > dist[e.from] + e.cost) {
            dist[e.to] = dist[e.from] + e.cost;
            prev[e.to] = id;
            run = 1;
            assert(it < n);
          }
        }
      }
    }
  }
  return !double_equal(dist[t], oo);
}

double relax() {
  double ans = 0;
  int flow = oo;
  for (int v = t; v != s; v = edges[prev[v]].from) {
    flow = min(flow, edges[prev[v]].cap - edges[prev[v]].flow);
  }
  for (int v = t; v != s; v = edges[prev[v]].from) {
    ans += flow * edges[prev[v]].cost;
    edges[prev[v] ^ 0].flow += flow;
    edges[prev[v] ^ 1].flow -= flow;
  }
  return ans;
}

void add(int from, int to, int cap, double cost) {
  // cerr << from << " " << to << " " << cap << " " << cost << endl;
  edges.emplace_back(from, to, cap, cost);
  edges.emplace_back(to, from, 0, -cost);
}

double calc(int ss, int tt) {
  s = ss, t = tt;
  double ans = 0;
  while (fb()) {
    ans += relax();
  }
  return ans;
}

int main() {
  // freopen("input.txt", "r", stdin);
  int m;
  scanf("%d", &m);
  Pt sp;
  cin >> sp.X >> sp.Y;

  double ans = 0;
  vector<Pt> pts;
  vector<Pt> from(m), to(m);
  for (int i = 0; i < m; ++i) {
    cin >> from[i].X >> from[i].Y;
    cin >> to[i].X >> to[i].Y;
    ans += distance(from[i], to[i]);
  }

  map<Pt, int> inp, out;
  for (auto &pt : from) {
    out[pt]++;
    pts.push_back(pt);
  }
  for (auto &pt : to) {
    inp[pt]++;
    pts.push_back(pt);
  }
  sort(all(pts));
  pts.erase(unique(all(pts)), pts.end());

  auto idx = [pts](const Pt &p) {
    return lower_bound(all(pts), p) - pts.begin();
  };

  const int s = pts.size();
  const int t = s + 1;

  for (const auto &u : pts) {
    if (inp[u] > out[u]) {
      add(s, idx(u), inp[u] - out[u], 0);
    }
    if (inp[u] < out[u]) {
      add(idx(u), t, out[u] - inp[u], 0);
    }
    if (inp[u] > out[u]) {
      for (const auto &v : pts) {
        if (out[v] > inp[v]) {
          add(idx(u), idx(v), 1, distance(u, v));
        }
      }
    }
  }

  cout.setf(ios::fixed);
  cout.precision(15);

  n = t + 1;
  ans += calc(s, t);
  cout << ans << endl;
  return 0;
}