#include <bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < n; ++i)
typedef long double LD;

using namespace std;

const int oo = 1e9;
const int maxn = 201;
const int maxt = 1001;

int n, m, p;
int len[maxn][maxn];
int people[maxn][maxn];
vector<int> g[maxn];

void read() {
  scanf("%d %d %d", &n, &m, &p);
  forn(i, m) {
    int u, v; scanf("%d %d", &u, &v); --u, --v;
    g[u].push_back(v); g[v].push_back(u);
    int d, x; scanf("%d %d", &d, &x);
    len[u][v] = len[v][u] = d;
    people[u][v] = people[v][u] = x;
  }
}

int dist[maxn][maxn];
void fw() {
  forn(i, n) {
    forn(j, n) {
      dist[i][j] = len[i][j];
      if (len[i][j] == 0) {
        dist[i][j] = oo;
      }
    }
  }
  forn(i, n) {
    dist[i][i] = 0;
  }
  forn(k, n) {
    forn(i, n) {
      forn(j, n) {
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }
}

int dp[maxn][maxt];
void calc_dp() {
  memset(dp, -1, sizeof(dp));
  dp[0][0] = 0;
  
  vector<int> order(n);
  forn(i, n) {
    order[i] = i;
  }
  sort(order.begin(), order.end(), [](int u, int v) {
    return dist[u] < dist[v];
  });
  
  for (int time = 0; time <= p; ++time) {
    for (int u : order) {
      for (int prev : g[u]) {
        if (time - len[prev][u] >= 0) {
          int prev_dp = dp[prev][time - len[prev][u]];
          if (prev_dp != -1) {
            int nval = prev_dp + people[prev][u];
            dp[u][time] = max(dp[u][time], nval);
          }
        }
      }
    }
  }
}

LD calc_ans() {
  LD ans = 0;
  for (int time = 0; 2 * time <= p; ++time) {
    forn(u, n) {
      for (int v : g[u]) {
        if (dp[u][time] != -1) {
          LD cur = dp[u][time] * 2;
          LD mid = p - 2 * time;
          cur += mid / LD(len[u][v]) * LD(people[u][v]);
          ans = max(cur, ans);
        }
      }
    }
  }
  return ans;
}

int main() {
  //freopen("input.txt", "r", stdin);
  read();
  fw();
  calc_dp();
  cout << fixed << setprecision(15) << calc_ans() << endl;
  return 0;
}