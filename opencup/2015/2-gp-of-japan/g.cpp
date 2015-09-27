struct pt {
  int x, y, z;
  void read() {
    cin >> x >> y >> z;
  }
  bool connected(const pt &other) const {
    int dx = abs(x - other.x);
    int dy = abs(y - other.y);
    int dz = abs(z - other.z);
    return dx + dy + dz == 1;
  }
};

void solve() {
  LL a, b, c, n;
  cin >> a >> b >> c >> n;

  LL res = (a * b + a * c + b * c) * 2LL;
  vector<pt> blocks(n);
  forn(i, n) {
    blocks[i].read();
  }

  LL other = 6 * n;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (blocks[i].connected(blocks[j])) {
        other -= 2;
      }
    }
  }
  res += other;
  forn(i, n) {
    res -= 2 * int(blocks[i].x == 0);
    res -= 2 * int(blocks[i].x == a - 1);
    res -= 2 * int(blocks[i].y == 0);
    res -= 2 * int(blocks[i].y == b - 1);
    res -= 2 * int(blocks[i].z == 0);
    res -= 2 * int(blocks[i].z == c - 1);
  }
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  solve();
  return 0;
}
