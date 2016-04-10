#include <bits/stdc++.h>

using namespace std;

int n;
string s;

const int N = 10;
int dist[1 << N];

int conv(const string &u) {
  int mask = 0;
  for (int i = 0; i < n; ++i) {
    if (u[i] == '+' || u[i] == '1') {
      mask |= 1 << i;
    }
  }
  return mask;
}

string conv(int x) {
  string ans(n, '0');
  for (int i = 0; i < n; ++i) {
    ans[i] += (x >> i) & 1;
  }
  return ans;
}

int get() {
  cin >> s;
  n = s.size();
  memset(dist, -1, sizeof(dist));

  const int st = conv(s);
  const int fn = (1 << n) - 1;
  dist[st] = 0;

  queue<int> q;
  q.push(st);

  while (q.size()) {
    int u = q.front();
    q.pop();

    if (u == fn) {
      return dist[u];
    }
    string uu = conv(u);
    for (int len = 1; len <= n; ++len) {
      string vv = uu;
      reverse(vv.begin(), vv.begin() + len);
      for (int i = 0; i < len; ++i) {
        vv[i] = (int(vv[i] - '0') ^ 1) + '0';
      }
      int v = conv(vv);
      if (dist[v] == -1) {
        dist[v] = dist[u] + 1;
        q.push(v);
      }
    }
  }
}

int main() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    printf("Case #%d: %d\n", i + 1, get());
  }
}
