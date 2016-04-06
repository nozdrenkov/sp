vector<Vec> convex_hull(vector<Vec> a) {
  const int n = a.size();
  if (n < 3) return a;
  sort(a.begin(), a.end());
  vector<Vec> st(2 * n);
  int k = 0;
  for (int i = 0; i < n; ++i) {
    while (k > 1 && (st[k - 1] - st[k - 2]) * (a[i] - st[k - 2]) >= 0) k--;
    st[k++] = a[i];
  }
  for (int r = k, i = n - 2; i >= 0; --i) {
    while (k > r && (st[k - 1] - st[k - 2]) * (a[i] - st[k - 2]) >= 0) k--;
    st[k++] = a[i];
  }
  st.resize(k);
  return st;
}

