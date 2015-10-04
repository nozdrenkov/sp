vi gen(int n) {
  vi a(n);
  forn(i, n) {
    a[i] = (rand() % 100) + 1;
  }
  return a;
}

const int maxn = 333;
int t[maxn];
void finit() {
  memset(t, 0, sizeof(t));
}

void fset(int i, int val) {
  for (; i < maxn; i |= i + 1) {
    t[i] = max(t[i], val);
  }
}

int fmax(int r) {
  int ans = 0;
  for (; r >= 0; r &= r + 1, --r) {
    ans = max(ans, t[r]);
  }
  return ans;
}

int lis(const vi &a) {
  const int n = a.size();
  vi dp(n);
  finit();
  forn(i, n) {
    dp[i] = fmax(a[i]) + 1;
    fset(a[i], dp[i]);
  }
  return *max_element(all(dp));
}

int lis_slow(const vi &a) {
  const int n = a.size();
  vi dp(n);
  forn(i, n) {
    dp[i] = 1;
    for (int j = i - 1; j >= 0; --j) {
      if (a[i] >= a[j]) {
        dp[i] = max(dp[i], dp[j] + 1);
      }
    }
  }
  return *max_element(all(dp));
}

vi times(const vi &a, int k) {
  if (k == 0) return vi();
  vi b;
  forn(i, k) {
    b.insert(b.end(), all(a));
  }
  return b;
}

LL solve(const vi &a, int t) {
  int mt = min(3 * (int)a.size(), t);
  if (t < mt) {
    return lis(times(a, t));
  } else {
    int l1 = lis(times(a, mt));
    int l2 = lis(times(a, mt + 1));
    LL d = l2 - l1;
    //for (int i = 1; i <= 10; ++i) {
    //  cerr << i << ": " << lis(times(a, i)) << endl;
    //}
    //dbg(mt);
    //dbg(l1);
    //dbg(t);
    //dbg(d);
    LL ans = LL(l1) + LL(t - mt) * d;
    //dbg(ans);
    return ans;
  }
}

void test() {
  while (true) {
    const int n = (rand() % 10) + 1;
    int t = (rand() % 1000) + 1;
    vi a = gen(n);
    LL v1 = solve(a, t);
    LL v2 = lis(times(a, t));
    if (v1 != v2) {
      dbg(v1);
      dbg(v2);
      dbg("ERROR!");
      dbg(a);
      dbg(t);
      exit(0);
    }
    //else cerr << "ok!" << endl;
  }

  //while (true) {
  //  int n = (rand() % 100) + 1;
  //  vi a = gen(n);
  //  if (lis(a) != lis2(a)) {
  //    dbg("err!");
  //    exit(0);
  //  }
  //  //else cout << "ok!" << endl;
  //}

}

void solve() {
  //test();
  //return;
  int n, t; cin >> n >> t;
  vi a(n);
  cin >> a;
  cout << solve(a, t) << endl;
}


int main() {
  ios_base::sync_with_stdio(false);
  solve();
  return 0;
}