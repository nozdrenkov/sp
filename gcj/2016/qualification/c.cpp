#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

LL divisor(LL x) {
  if (x < 2) return 0;
  for (LL d = 2; d * d <= x; ++d) {
    if (x % d == 0) {
      return d;
    }
  }
  return 0;
}

inline int bit(LL mask, int i) {
  return (mask >> i) & 1;
}

LL divs[20];

string conv(LL mask, int n) {
  string ans(n, '0');
  for (int i = 0; i < n; ++i) {
    ans[i] += bit(mask, i);
  }
  return ans;
}

bool check(LL s, int n) {
  if (bit(s, 0) == 0 || bit(s, n - 1) == 0) {
    return false;
  }
  for (int base = 2; base <= 10; ++base) {
    LL num = 0;
    for (int i = 0; i < n; ++i) {
      num *= base;
      num += bit(s, i);
    }
    LL d = divisor(num);
    if (d == 0) {
      return false;
    }
    divs[base] = d;
  }
  return true;
}

void solve() {
  int n, cnt;
  cin >> n >> cnt;
  for (int x = 0; x < (1 << n) && cnt; ++x) {
    if (check(x, n)) {
      cout << conv(x, n);
      for (int base = 2; base <= 10; ++base) {
        cout << " " << divs[base];
      }
      cout << endl;
      cnt--;
    }
  }
}

int main() {
  freopen("output.txt", "w", stdout);
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    cout << "Case #" << i + 1 << ":" << endl;
    cerr << i + 1 << endl;
    solve();
  } 
  cerr << "Ready!" << endl;
}
