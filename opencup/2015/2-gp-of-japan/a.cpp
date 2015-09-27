void solve() {
  int n, m;
  cin >> n >> m;
  vector<string> a(m);
  cin >> a;

  int pos = -1;
  int ans_err = -1;

  vvi prefE(m, vi(n + 1));
  vvi prefW(m, vi(n + 1));
  forn(i, m) {
    forn(j, n) {
      prefE[i][j + 1] += prefE[i][j] + int(a[i][j] == 'E');
      prefW[i][j + 1] += prefW[i][j] + int(a[i][j] == 'W');
    }
  }

  auto sum = [](const vi &pref, int l, int r) {
    if (l > r) return 0;
    return pref[r + 1] - pref[l];
  };

  for (int k = 0; k <= n; ++k) {
    int err = 0;
    forn(i, m) {
      err += sum(prefE[i], 0, k - 1);
      err += sum(prefW[i], k, n - 1);
    }
    if (pos == -1 || err < ans_err) {
      pos = k;
      ans_err = err;
    }
    //cerr << k << ": " << err << endl;
  }
  cout << pos << " " << pos + 1 << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  solve();
  return 0;
}