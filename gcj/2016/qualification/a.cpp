#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

int get_mask(LL x) {
  int mask = 0;
  while (x) {
    int d = x % 10;
    mask |= 1 << d;
    x /= 10;
  }
  return mask;
}

void solve() {
  int n;
  scanf("%d", &n);
  if (n == 0) {
    puts("INSOMNIA");
    return;
  }
  const int all = (1 << 10) - 1;
  int used = 0;
  for (LL i = 1; i < 10000000; ++i) {
    LL x = i * n;
    used |= get_mask(x);
    if (used == all) {
      cout << x << endl;
      return;
    }
  }
  cerr << "JOPA, MAN!" << endl;
  puts("INSOMNIA");
}

int main() {
  freopen("output.txt", "w", stdout);
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    printf("Case #%d: ", i + 1);
    solve();
  }
}
