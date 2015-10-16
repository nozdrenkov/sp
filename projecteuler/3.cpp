// https://projecteuler.net/problem=3
// ans = 6857

#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

LL num = 600851475143;

int main() {
  LL ans = 0;
  for (LL d = 2; d * d <= num; ++d) {
    if (num % d == 0) {
      ans = max(ans, d);
      while (num % d == 0) {
        num /= d;
      }
    }
  }
  if (num > 1) {
    ans = max(ans, num);
  }
  cout << ans << endl;
  return 0;
}