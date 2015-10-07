bool pr(int x) {
  if (x < 2) return false;
  for (int d = 2; LL(d) * d <= x; ++d) {
    if (x % d == 0) {
      return false;
    }
  }
  return true;
}

void solve() {
  int n; cin >> n;
  if (pr(n)) {
    cout << 1 << endl;
    cout << n << endl;
  } else {
    for (int x = n - 1; x >= 0; --x) {
      if (pr(x)) {
        int diff = n - x;
        if (pr(diff)) {
          cout << 2 << endl;
          cout << x << " " << diff << endl;
          return;
        }
        for (int k = diff - 1; k >= max(0, diff - 100); --k) {
          if (pr(k) && pr(diff - k)) {
            cout << 3 << endl;
            cout << x << " " << k << " " << diff - k << endl;
            //assert(pr(x) && pr(k) && pr(diff - k) && x + k + diff - k == n);
            return;
          }
        }
      }
    }
  }
}

int main() {

  solve();

  return 0;
}
