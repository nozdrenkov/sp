void solve() {
  int n; cin >> n;
  set<int> xx, yy;

  vi ans;
  forn(i, n * n) {
    int x, y;
    cin >> x >> y;
    if (!xx.count(x) && !yy.count(y)) {
      xx.insert(x);
      yy.insert(y);
      ans.push_back(i + 1);
    }
  }
  cout << ans << endl;
}

int main() {

  solve();

  return 0;
}
