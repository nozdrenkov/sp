bool solve() {
  int n; cin >> n;
  vi a(2000);
  forn(i, n) {
    int l, r;
    cin >> l >> r;
    for (int i = l; i <= r; ++i) {
      a[i] = 1;
    }
  }
  vi pref(2001);
  forn(i, 2000) {
    pref[i + 1] = pref[i] + a[i];
  }
  for (int r = 10; r < 2000; ++r) {
    int l = r - 180 + 1;
    if (l >= 0) {
      int sum = pref[r + 1] - pref[l];
      if (sum > 90) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  puts(solve() ? "Yes" : "No");
  return 0;
}
