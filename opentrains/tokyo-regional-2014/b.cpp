LL calc(string s, char prior) {
  if (prior == '*') {
    vector<LL> vals;
    vector<LL> cur;
    for (int i = 0; i < s.size(); i += 2) {
      cur.push_back(s[i] - '0');
      if (i + 1 >= s.size() || s[i + 1] != prior) {
        if (cur.size()) {
          LL prod = cur[0];
          for (int j = 1; j < cur.size(); ++j) {
            prod *= cur[j];
          }
          vals.push_back(prod);
          cur.clear();
        }
      }
    }
    LL sum = 0;
    forn(i, vals.size()) {
      sum += vals[i];
    }
    return sum;
  }

  if (prior == 'L') {
    LL ans = 0;
    for (int i = 0; i < s.size(); i += 2) {
      if (i == 0) ans = LL(s[i] - '0');
      else {
        if (s[i - 1] == '+') ans += LL(s[i] - '0');
        else if (s[i - 1] == '*') ans *= LL(s[i] - '0');
        else assert(false);
      }
    }
    return ans;
  }
}

string solve() {
  //dbg(calc("1+2*3+4", 'L'));
  //return "";

  string s; cin >> s;
  LL x; cin >> x;
  LL v1 = calc(s, '*');
  LL v2 = calc(s, 'L');
  if (v1 == x && v2 == x) return "U";
  if (v1 == x) return "M";
  if (v2 == x) return "L";
  return "I";
}

int main() {

  cout << solve() << endl;

  return 0;
}