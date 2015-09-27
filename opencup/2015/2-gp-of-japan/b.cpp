int to_dir(char c) {
  if (c == '^') return 0;
  if (c == '>') return 1;
  if (c == 'v') return 2;
  if (c == '<') return 3;
  return -1;
}

char buf[5];

struct pt {
  int x, y;
  char dir;
  void read() {
    scanf("%d %d %s", &x, &y, buf);
    dir = buf[0];
  }
};

const int maxn = 3000 + 100;
pt a[maxn];
int n;

int dist(int i, int j) {
  return abs(a[i].x - a[j].x) + abs(a[i].y - a[j].y);
}

void upd(int i, int &val, int idx) {
  if (val == -1 || dist(i, idx) < dist(i, val)) {
    val = idx;
  }
}

int doit(vvi closest, int pos) {
  int ans = 0;
  while (pos != -1) {
    ans++;
    int npos = closest[pos][to_dir(a[pos].dir)];

    int d1 = closest[pos][to_dir('^')];
    if (d1 != -1) closest[d1][to_dir('v')] = closest[pos][to_dir('v')];

    int d2 = closest[pos][to_dir('v')];
    if (d2 != -1) closest[d2][to_dir('^')] = closest[pos][to_dir('^')];

    int d3 = closest[pos][to_dir('>')];
    if (d3 != -1) closest[d3][to_dir('<')] = closest[pos][to_dir('<')];

    int d4 = closest[pos][to_dir('<')];
    if (d4 != -1) closest[d4][to_dir('>')] = closest[pos][to_dir('>')];

    pos = npos;
  }
  return ans;
}

void solve() {
  scanf("%d", &n);
  vvi closest;
  closest.assign(n, vi(4, -1));
  forn(i, n) {
    a[i].read();
  }
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      int u = i, v = j;
      if (a[u].x == a[v].x) {
        if (a[u].y > a[v].y) swap(u, v);
        upd(u, closest[u][to_dir('v')], v);
        upd(v, closest[v][to_dir('^')], u);
      } else if (a[u].y == a[v].y) {
        if (a[u].x > a[v].x) swap(u, v);
        upd(u, closest[u][to_dir('>')], v);
        upd(v, closest[v][to_dir('<')], u);
      }
    }
  }
  int ans = doit(closest, 0);
  for (int i = 1; i < n; ++i) {
    ans = max(ans, doit(closest, i));
  }
  cout << ans << endl;
}

int main() {
  solve();
  return 0;
}