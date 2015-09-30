void solve() {
  int n, m; cin >> n >> m;
  int w, h; cin >> w >> h;
  vvi pieces(n, vi(w));
  cin >> pieces;
  vvi cuts(m, vi(w));
  cin >> cuts;
  vi cut = cuts[0];
  for (auto &cur : cuts) {
    forn(i, w) {
      cut[i] = max(cut[i], cur[i]);
    }
  }
  for (auto &piece : pieces) {
    forn(i, w) {
      piece[i] = min(piece[i], h - cut[i]);
    }
    cout << piece << endl;
  }
}

int main() {

  ios_base::sync_with_stdio(false);
  solve();

  return 0;
}
