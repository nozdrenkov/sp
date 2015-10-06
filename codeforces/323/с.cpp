#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

int gcd(int a, int b) {
  while (b) {
    a %= b;
    swap(a, b);
  }
  return a;
}

vector<int> calcMaxLen(const vector<int> &f) {
  auto zero = find(f.begin(), f.end(), 0);
  if (zero == f.end()) {
    return vector<int>();
  }
  const int n = f.size();
  vector<int> dp(n);
  if (f[n - 1]) {
    for (int i = 0; i < n; ++i) {
      if (f[i] == 0) {
        dp[n - 1] = i + 1;
        break;
      }
    }
  }
  for (int i = n - 2; i >= 0; --i) {
    if (f[i]) {
      dp[i] = dp[i + 1] + 1;
    }
  }
  return dp;
}

int n;
vector<int> a;
vector< vector<int> > lengths;

vector<int> calcFunc(int period) {
  vector<int> mx(n);
  vector<int> res(n);
  for (int i = 0; i < n; ++i) {
    if (i - period >= 0) {
      mx[i] = mx[i - period];
    } else {
      mx[i] = a[i];
      for (int j = i; j < n; j += period) {
        mx[i] = max(mx[i], a[j]);
      }
    }
    res[i] = int(a[i] >= mx[i]);
  }
  return res;
}

int main() {
  // freopen("input.txt", "r", stdin);

  scanf("%d", &n);
  a.resize(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  lengths.resize(n);
  for (int len = 1; len < n; ++len) {
    lengths[gcd(n, len)].push_back(len);
  }
  
  LL ans = 0;
  for (int period = 1; period < n; ++period) {
    const auto &lens = lengths[period];
    if (lens.size()) {
      auto f = calcFunc(period);
      auto maxlen = calcMaxLen(f);
      if (maxlen.empty()) {
        for (int len : lens) {
          ans += n;
        }
      } else {
        vector<int> cnt(n + 100);
        for (int mxlen : maxlen) {
          cnt[mxlen]++;
        }
        vector<LL> pref(cnt.size() + 1);
        for (int i = 0; i < cnt.size(); ++i) {
          pref[i + 1] = pref[i] + cnt[i];
        }
        auto sum = [pref](int l, int r) {
          return pref[r + 1] - pref[l];
        };
        for (int len : lens) {
          ans += sum(len, cnt.size() - 1);
        }
      }
    }
  }

  printf("%I64d\n", ans);
  return 0;
}