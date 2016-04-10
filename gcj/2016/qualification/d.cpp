#include <bits/stdc++.h>

using namespace std;

string get(string s, int cnt) {
  string ans = s;
  while (cnt--) {
    string t;
    for (char c : ans) {
      if (c == 'G') {
        t += string(s.size(), 'G');
      } else {
        t += s;
      }
    }
    ans = t;
  }
  string res;
  int len = ans.size() / s.size();
  for (int i = 0; i < ans.size(); i += len) {
    res += ans.substr(i, len);
    res += ' ';
  }
  return res;
}

typedef long long LL;

void solve() {
  LL k, c, s;
  cin >> k >> c >> s;
  LL len = 0;
  LL cnt = 1;
  while (c--) {
    cnt *= k;
  }

  LL block = cnt / k;
  vector<LL> ans;
  for (LL i = 0; i < cnt; i += block) {
    ans.push_back(i);
  }
  if (ans.empty() || ans.size() > s) {
    cout << " IMPOSSIBLE" << endl;
    return;
  }
  ans.back() = cnt - 1;
  for (LL x : ans) {
    cout << " " << x + 1;
  }
  cout << endl;
}

int main() {
  //freopen("output.txt", "w", stdout);
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    cout << "Case #" << i << ":";
    solve();
  }
  cerr << "Ready!" << endl;
}
