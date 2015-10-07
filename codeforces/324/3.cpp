int diff(const string &a, const string &b) {
  int cnt = 0;
  forn(i, a.size()) cnt += int(a[i] != b[i]);
  return cnt;
}

char get(char a, char b) {
  for (char x = 'a'; x <= 'z'; ++x) {
    if (x != a && x != b) {
      return x;
    }
  }
}

void solve() {
  int n, kk;
  cin >> n >> kk;
  string a, b;
  cin >> a >> b;

  queue<int> ss;
  queue<int> dd;
  forn(i, n) {
    if (a[i] != b[i]) {
      dd.push(i);
    } else {
      ss.push(i);
    }
  }

  string s = a;

  if (kk >= dd.size()) {
    int k = kk;
    while (k > 0 && dd.size()) {
      int pos = dd.front(); dd.pop();
      s[pos] = get(a[pos], b[pos]);
      --k;
    }

    while (k > 0 && ss.size()) {
      int pos = ss.front(); ss.pop();
      s[pos] = get(a[pos], b[pos]);
      --k;
    }

    int d1 = diff(a, s);
    int d2 = diff(b, s);
    if (d1 == kk && d2 == kk) {
      cout << s << endl;
    } else {
      cout << -1 << endl;
    }
  } else {
    int same = 2 * kk - int(dd.size());
    int k = kk;
    while (dd.size() && same > 0 && k > 0) {
      int pos = dd.front(); dd.pop();
      s[pos] = get(a[pos], b[pos]);
      --same;
      --k;
    }
    forn(i, k) {
      if (dd.size()) {
        int pos = dd.front(); dd.pop();
        s[pos] = b[pos];
      }
    }
    int d1 = diff(a, s);
    int d2 = diff(b, s);
    if (d1 == kk && d2 == kk) {
      cout << s << endl;
    }
    else {
      cout << -1 << endl;
    }
  }
}

int main() {

  solve();

  return 0;
}
