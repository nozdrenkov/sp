string rot(const string &s) {
  string t = s;
  reverse(all(t));
  for (auto &c : t) {
    if (c == '3' || c == '4' || c == '7') return "";
    if (c == '6') c = '9';
    else if (c == '9') c = '6';
  }
  return t;
}

LL toLL(const string &s) {
  istringstream is(s);
  LL x; is >> x;
  return x;
}

bool prime(LL x) {
  if (x < 2) return false;
  if (x > 2 && x % 2 == 0) return false;
  for (LL d = 2; d * d <= x; ++d) {
    if (x % d == 0) {
      return false;
    }
  }
  return true;
}

bool solve() {
  string a; cin >> a;
  if (!prime(toLL(a))) return false;
  string b = rot(a);
  if (b == "") return false;
  if (!prime(toLL(b))) return false;
  return true;
}

int main() {
  cout << (solve() ? "yes" : "no") << endl;
  return 0;
}
