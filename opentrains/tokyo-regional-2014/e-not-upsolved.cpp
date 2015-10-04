#if 1
#define _CRT_SECURE_NO_WARNINGS
#include <functional>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <sstream>
#include <numeric>
#include <string>
#include <vector>
#include <bitset>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <list>

using namespace std;

typedef long long LL;
typedef long double LD;
typedef pair<int, int> pii;

const LD eps = 1e-9;
const LD pi = acos(-1.0);
const int inf = 1e+9;

#define mp make_pair
#define pb push_back
#define X first
#define Y second

#define dbg(x) { cerr << #x << " = " << x << endl; }

// extended template
#pragma comment(linker, "/STACK:99999999999")
typedef vector<int> vi;
typedef vector<vi> vvi;

#define forn(i, n) for (int i = 0; i < n; ++i)
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()

template<typename T> istream & operator >> (istream &, vector<T> &);
template<typename T> ostream & operator << (ostream &, const vector<T> &);

#define START clock_t _clock = clock();
#define END cerr << endl << "time: " << (clock() - _clock) / LD(CLOCKS_PER_SEC) << endl;

#define NAME "problem"

int dx[4] = { 0,  1,  0, -1 };
int dy[4] = { 1,  0, -1,  0 };

int to_dir(char c) {
  return string("NESW").find(c);
}

const int maxn = 51;
bool go[maxn][maxn][4];
bool dp[1100][maxn][maxn][4];

void solve() {
  //memset(dp, 0, sizeof(dp));
  //dbg(sizeof(dp));
  int n, x0, y0, t;
  cin >> n >> x0 >> y0 >> t;
  forn(i, n) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    if (x1 == x2) {
      go[x1][min(y1, y2)][0] = true;  // up
      go[x1][max(y1, y2)][2] = true;  // down
      for (int y = min(y1, y2) + 1; y < max(y1, y2); ++y) {
        go[x1][y][0] = go[x1][y][2] = true;
      }
    }
    else {
      go[min(x1, x2)][y1][1] = true;  // right
      go[max(x1, x2)][y1][3] = true;  // left
      for (int x = min(x1, x2) + 1; x < max(x1, x2); ++x) {
        go[x][y1][1] = go[x][y1][3] = true;
      }
    }
  }
  forn(dir, 4) {
    dp[0][x0][y0][dir] = true;
  }

  vector<int> len(t);
  vector<int> last_dir(t);
  forn(i, t) {
    string to;
    cin >> len[i] >> to;
    last_dir[i] = to_dir(to[0]);
  }

  vi step_sums(t);
  partial_sum(all(len), step_sums.begin());

  int pos = 0;
  for (int step = 1; step <= step_sums.back(); ++step) {
    int impossible_dir = -1;
    if (step == step_sums[pos]) {
      impossible_dir = (last_dir[pos] + 2) % 4;
      ++pos;
    }
    
    bool prev_frame_was_key = binary_search(all(step_sums), step - 1);
    int need_dir = pos - 1 >= 0 ? last_dir[pos - 1] : -1;

    for (int x = 0; x < maxn; ++x) {
      for (int y = 0; y < maxn; ++y) {
        for (int dir = 0; dir < 4; ++dir) {
          if (dir != impossible_dir) {
            if (step != step_sums.back() && prev_frame_was_key && dir != need_dir) {
              continue;
            }
            int px = x - dx[dir];
            int py = y - dy[dir];
            if (0 <= px && px < maxn && 0 <= py && py < maxn) {
              for (int pdir = 0; pdir < 4; ++pdir) {
                if ((dir + 2) % 4 != pdir) {
                  if (go[px][py][dir] && dp[step - 1][px][py][pdir]) {
                    dp[step][x][y][dir] = true;
                    break;
                  }
                }
              }
            }
          }
        }
      }
    }
    if (step == step_sums.back()) {
      for (int x = 0; x < maxn; ++x) {
        for (int y = 0; y < maxn; ++y) {
          bool ok = false;
          for (int dir = 0; dir < 4; ++dir) {
            if (dir != impossible_dir) {
              if (dp[step][x][y][dir]) {
                ok = true;
                break;
              }
            }
          }
          if (ok) {
            cout << x << " " << y << endl;
          }
        }
      }
    }
  }
}

int main() {
  START;
  // freopen(NAME ".in", "r", stdin); freopen(NAME ".out", "w", stdout);
  //freopen("input.txt", "r", stdin); // freopen("output.txt", "w", stdout);

  ios_base::sync_with_stdio(false);
  solve();

  // END;
  return 0;
}
/*******************************************
*******************************************/

template<typename T> istream & operator >> (istream &is, vector<T> &v) {
  forn(i, v.size()) {
    is >> v[i];
  }
  return is;
}
template<typename T> ostream & operator << (ostream &os, const vector<T> &v) {
  forn(i, v.size()) {
    if (i) os << " ";
    os << v[i];
  }
  return os;
}
#endif