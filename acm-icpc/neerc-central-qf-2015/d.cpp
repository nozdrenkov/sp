LD h1, t1, h2, t2;

bool check(LD delay) {
  if (delay < 0) return false;
  LD g1 = (2 * h1) / ((t1 - delay) * (t1 - delay));
  LD g2 = (2 * h2) / ((t2 - delay) * (t2 - delay));
  return abs(g1 - g2) < eps;
}

void solve() {
  cin >> h1 >> t1 >> h2 >> t2;

  LD a = h1 - h2;
  LD b = 2 * (h2 * t1 - h1 * t2);
  LD c = (h1 * t2 * t2 - h2 * t1 * t1);

  LD d = b * b - 4 * a * c;

  LD x1 = (-b - sqrt(d)) / (2 * a);
  LD x2 = (-b + sqrt(d)) / (2 * a);
  if (x1 > x2) {
    swap(x1, x2);
  }

  LD ans = max(x1, x2);

  cout.setf(ios::fixed);
  cout.precision(10);

  if (check(x1)) cout << x1 << endl;
  else if (check(x2)) cout << x2 << endl;
  else assert(false);
}
