
void solve() {
  int n; cin >> n;
  vi a(n); cin >> a;
  int ans = inf;
  forn(i, n) forn(j, n) {
    int val = i < j ? a[j] - a[i] : 9001;
    ans = min(ans, val);
  }
  cout << (ans >= 0 ? "yes" : "no") << endl;
}

int main() {

  solve();

  return 0;
}