int gcd(int a, int b) {
  while (b) {
    a %= b;
    swap(a, b);
  }
  return a;
}

vi gen(int n) {
  vi a(n);
  forn(i, n) {
    a[i] = (rand() % 100) + 1;
  }
  return a;
}

bool check(const vi &a, const vi &b) {
  vi c; c.reserve(a.size() * a.size());
  forn(i, a.size()) forn(j, a.size()) {
    c.push_back(gcd(a[i], a[j]));
  }
  sort(all(c));
  return c == b;
}

vi solve(int n, vi b) {
  multiset<int> vals(all(b));
  vi res;
  while (vals.size()) {
    auto mx = --vals.end();
    int cur = *mx;
    vals.erase(mx);
    for (int other : res) {
      int g = gcd(cur, other);
      forn(i, 2) {
        auto p1 = vals.lower_bound(g);
        if (p1 != vals.end() && *p1 == g) vals.erase(p1);
      }
    }
    res.push_back(cur);
  }
  sort(all(res));
  return res;
}

void solve() {
  int n; cin >> n;
  vi a(n * n); cin >> a;
  cout << solve(n, a) << endl;
}

void test() {
  while (true) {
    vi a = gen(5);
    sort(all(a));

    vi b;
    forn(i, a.size()) {
      forn(j, a.size()) {
        b.push_back(gcd(a[i], a[j]));
      }
    }

    sort(all(b));
    vi c = solve(a.size(), b);
    if (a == c) {
      cout << "ok!" << endl;
    }
    else {
      cout << "errror!" << endl;
      dbg(a);
      dbg(c);
      dbg(b);
      exit(0);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  solve();
  return 0;
}