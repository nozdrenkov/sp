#include <bits/stdc++.h>

using namespace std;

vector< vector<double> > a;

void gauss() {
  const int n = a[0].size() - 1;
  for (int k = 0; k < n; ++k) {
    int mx = k;
    for (int i = k + 1; i < a.size(); ++i) {
      if (abs(a[i][k]) > abs(a[mx][k])) {
        mx = i;
      }
    }
    swap(a[k], a[mx]);
    double val = a[k][k];
    assert(abs(val) > 1e-9);
    for (int j = 0; j < a[k].size(); ++j) {
      a[k][j] /= val;
    }
    for (int i = k + 1; i < a.size(); ++i) {
      double val = a[i][k];
      for (int j = 0; j < a[i].size(); ++j) {
        a[i][j] -= val * a[k][j];
      }
    }
  }
  for (int i = n - 1; i >= 0; --i) {
    for (int j = i - 1; j >= 0; --j) {
      double val = a[j][i];
      for (int k = 0; k < a[j].size(); ++k) {
        a[j][k] -= val * a[i][k];
      }
    }
  }
}

int n, m, k;
vector<int> neighbours[100][4];

unordered_map<char, int> mp;
unordered_map<int, char> pm;
int conv(char c) {
  if (!mp.count(c)) {
    int idx = mp.size();
    mp.insert(make_pair(c, idx));
    pm.insert(make_pair(idx, c));
  }
  return mp[c];
}

char conv(int c) {
  return pm[c];
}

vector<int> conv(const string &s) {
  vector<int> ans;
  for (char v : s) {
    ans.push_back(conv(v));
  }
  return ans;
}

void read() {
  cin >> n >> m >> k;
  for (int i = 0; i < k; ++i) {
    string ch, up, right, down, left;
    cin >> ch >> up >> right >> down >> left;
    int plant = conv(ch[0]);
    if (up != "~") neighbours[plant][0] = conv(up);
    if (right != "~") neighbours[plant][1] = conv(right);
    if (down != "~") neighbours[plant][2] = conv(down);
    if (left != "~") neighbours[plant][3] = conv(left);
  }
}

vector<int> used;
vector<double> eq;
int ok = 0;
void dfs(int u, int dir, int val = 1) {
  used[u] = true;
  eq[u] = val;
  if (val == 1) ok |= 2; else ok |= 1;
  for (int v : neighbours[u][dir]) {
    if (!used[v]) {
      dfs(v, (dir + 2) % 4, val * -1);
    }
  }
}

void prepare() {
  for (int dir = 0; dir < 4; ++dir) {
    for (int u = 0; u < k; ++u) {
      used.assign(k, false);
      eq.assign(k + 1, 0);
      ok = 0;
      dfs(u, dir);
      if (ok == 3) {
        a.push_back(eq);
      }
    }
  }
  for (int d = 0; d < 4; ++d) {
    vector<double> line(k + 1);
    for (int cur = 0; cur < k; ++cur) {
      if (neighbours[cur][d].empty()) {
        line[cur] = 1;
      }
    }
    line.back() = d & 1 ? n : m;
    a.push_back(line);
  }
}

vector<string> ans;
void recover() {
  ans.assign(n, string(m, '.'));
  int it = k;
  vector<int> xx(k, -1), yy(k, -1);
  vector<int> len(k, 0), used(k, false);
  for (int cur = 0; cur < k; ++cur) {
    len[cur] = int(a[cur].back() + 0.5);
  }
  while (it--) {
    for (int cur = 0; cur < k; ++cur) {
      if (!used[cur]) {
        // left
        if (neighbours[cur][3].empty()) yy[cur] = 0;
        for (int adj : neighbours[cur][3]) {
          if (yy[adj] != -1) {
            yy[cur] = yy[adj] + len[adj];
          }
        }
        // right
        if (neighbours[cur][1].empty()) yy[cur] = m - len[cur];
        for (int adj : neighbours[cur][1]) {
          if (yy[adj] != -1) {
            yy[cur] = yy[adj] - len[cur];
          }
        }
        // up
        if (neighbours[cur][0].empty()) xx[cur] = 0;
        for (int adj : neighbours[cur][0]) {
          if (xx[adj] != -1) {
            xx[cur] = xx[adj] + len[adj];
          }
        }
        // down
        if (neighbours[cur][2].empty()) xx[cur] = n - len[cur];
        for (int adj : neighbours[cur][2]) {
          if (xx[adj] != -1) {
            xx[cur] = xx[adj] - len[cur];
          }
        }
      }
    }
    for (int cur = 0; cur < k; ++cur) {
      if (!used[cur]) {
        if (xx[cur] != -1 && yy[cur] != -1) {
          for (int x = xx[cur]; x < xx[cur] + len[cur]; ++x) {
            for (int y = yy[cur]; y < yy[cur] + len[cur]; ++y) {
              ans[x][y] = conv(cur);
            }
          }
        }
      }
    }
  }
}

void print() {
  for (int i = 0; i < n; ++i) {
    cout << ans[i] << endl;
  }
}

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false);
  read();
  prepare();
  gauss();
  recover();
  print();
  return 0;
}