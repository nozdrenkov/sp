// tested on http://codeforces.com/gym/100255/problem/A

template<typename T>
class SparseTable {
  typedef function<T(T, T)> Op;
  Op op;
  vector<int> logTable;
  vector< vector<T> > data;
  //static const int maxN = 2e5;
  //static const int maxLog = 17;
  //int logTable[maxN + 1];
  //T data[maxLog + 1][maxN];
 public:
  SparseTable(const vector<T> &a, Op op) : op(op) {
    const int n = a.size();
    logTable.assign(n + 1, 0);
    for (int i = 2; i <= n; ++i) {
      logTable[i] = logTable[i >> 1] + 1;
    }
    data.assign(logTable[n] + 1, vector<T>(n));
    copy(a.begin(), a.end(), data[0].begin());
    //copy(a.begin(), a.end(), data[0]);
    for (int p = 1; (1 << p) <= n; ++p) {
      for (int i = 0; i + (1 << p) <= n; ++i) {
        data[p][i] = op(data[p - 1][i], data[p - 1][i + (1 << (p - 1))]);
      }
    }
  }
  T get(int l, int r) const {
    int p = logTable[r - l + 1];
    return op(data[p][l], data[p][r - (1 << p) + 1]);
  }
};
