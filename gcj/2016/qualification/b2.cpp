#include <bits/stdc++.h>

using namespace std;

const int N = 111;

int dp[N][2];

void upd(int &x, int y) {
  if (x == -1 || y < x) {
    x = y;
  }
}

void solve() {
  memset(dp, -1, sizeof(dp));
  string s;
  cin >> s;
  const int n = s.size();
  dp[0][0] = dp[0][1] = 0;
  for (int i = 0; i < n; ++i) {
    if (s[i] == '+') {
      upd(dp[i + 1][1], dp[i][1]);
      upd(dp[i + 1][0], dp[i][1] + 1);
    } else {
      upd(dp[i + 1][0], dp[i][0]);
      upd(dp[i + 1][1], dp[i][0] + 1);
    }
  }
  cout << dp[n][1] << endl;
}

int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    cout << "Case #" << i << ": ";
    solve();
  }
}

