void solve() {
  int n; cin >> n;
  vi a(n); cin >> a;
  int used = 0;
  int cnt = 0;
  while (true) {
    forn(i, a.size()) {
      if (used >= a[i] && a[i] != -1) {
        ++used;
        a[i] = -1;
      }
    }
    if (used == n) break;
    ++cnt;
    for (int i = a.size() - 1; i >= 0; --i) {
      if (used >= a[i] && a[i] != -1) {
        ++used;
        a[i] = -1;
      }
    }
    if (used == n) break;
    ++cnt;
  }

  cout << cnt << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  solve();
  return 0;
}