#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

int main() {
  int n; cin >> n;
  int a = 1, b = 1;
  for (int i = 0; i < n; ++i) {
    (a *= 27) %= mod;
    (b *= 7) %= mod;
  }
  cout << (a - b + mod) % mod << endl;
  return 0;
}