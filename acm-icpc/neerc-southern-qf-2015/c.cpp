#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < n; ++i)

typedef long long LL;

int rnd() {
  return (rand() << 16) ^ rand();
}

LL big_rnd() {
  //return LL(rand()) << 48;
  return (LL(rnd()) << 32) ^ rnd();
}

struct node_t;
typedef node_t* pnode;

struct node_t {
  LL sz; int pr;
  pnode l, r;

  bool val;
  LL sum;

  node_t() {}
  node_t(bool val) : sz(1), pr(rnd()), l(0), r(0), val(val), sum(val) {}

  LL size() const {
    return this ? sz : 0LL;
  }

  LL getsum() const {
    return this ? sum : 0LL;
  }

  pnode clone() {
    if (!this) return 0;
    pnode res = new node_t();
    res->sz = sz;
    res->pr = pr;
    res->val = val;
    res->sum = sum;
    res->l = l;
    res->r = r;
    return res;
  }

  void upd() {
    if (this) {
      sz = l->size() + 1LL + r->size();
      sum = l->getsum() + LL(val) + r->getsum();
    }
  }

  friend void split(pnode orig, pnode &l, pnode &r, LL x) {
    pnode t = orig->clone();
    if (t == 0) l = r = 0;
    else if (t->l->size() + 1 > x)
      split(t->l, l, t->l, x), r = t;
    else
      split(t->r, t->r, r, x - t->l->size() - 1), l = t;
    l->upd(), r->upd();
  }

  friend void merge(pnode l, pnode r, pnode &t) {
    LL x = l->size();
    LL y = r->size();
    if (l == 0) t = r;
    else if (r == 0) t = l;
    else if (big_rnd() % (x + y) < y) {
      pnode nr = r->clone();
      merge(l, nr->l, nr->l), t = nr;
    }
    else {
      pnode nl = l->clone();
      merge(nl->r, r, nl->r), t = nl;
    }
    t->upd();
  }

  void out() const {
    if (this) {
      l->out();
      cout << val << " ";
      r->out();
    }
  }

  int prior() const {
    return this ? pr : 0;
  }

  void* operator new (size_t sz);
};

/* statistics */
int max_diff = 0;
int max_cnt = 0;

const int maxmem = 1e6 + 100;
node_t mem[maxmem];
int memptr = 0;

void* node_t::operator new (size_t sz){
  max_cnt = max(memptr, max_cnt);
return &mem[memptr++];
}

struct query_t {
  LL l, r;
  char c;
  int idx;
  void read() {
    scanf("%I64d %I64d %c", &l, &r, &c);
    --l, --r;
  }
};

const int maxn = 2e5 + 100;

char s[200];
int n, m;
int rot[maxn];
vector<query_t> q[26];
LL ans[maxn];

void read() {
  scanf("%s", s);
  scanf("%d %d", &n, &m);
  forn(i, n) {
    scanf("%d", rot + i);
  }
  forn(i, m) {
    query_t cur;
    cur.read();
    cur.idx = i;
    q[cur.c - 'a'].push_back(cur);
  }
}

void process() {
  forn(ch, 26) {
    if (q[ch].size()) {
      memptr = 0;
      pnode tree = 0;
      for (int i = 0; s[i]; ++i) {
        bool val = s[i] == 'a' + ch;
        merge(tree, new node_t(val), tree);
      }
      forn(i, n) {
        if (tree->size() > 1e18 + 10) {
          break;
        }
        pnode t1, t2;
        split(tree, t1, t2, tree->size() - (rot[i] % tree->size()));
        merge(tree, t2, tree);
        merge(tree, t1, tree);
      }
      for (auto &query : q[ch]) {
        int ptr = memptr;
        pnode t1, t2, mid;
        split(tree, t1, t2, query.r + 1);
        split(t1, t1, mid, query.l);
        ans[query.idx] = mid->getsum();
        max_diff = max(max_diff, memptr - ptr);
        memptr = ptr;
      }
    }
  }
}

void print() {
  forn(i, m) {
    if (i) printf(" ");
    printf("%I64d", ans[i]);
  }
  puts("");
}

void gen() {
  freopen("input.txt", "w", stdout);
  const int slen = 100;
  const int maxn = 1e5;
  forn(i, slen) cout << char('a' + (rand() % 26)); cout << endl;
  cout << maxn << " " << maxn << endl;
  forn(i, maxn) cout << (rand() % 100) + 1 << " "; cout << endl;
  forn(i, maxn) {
    const int maxq = 1e18;
    LL l = (big_rnd() % maxq) + 1;
    LL r = (big_rnd() % maxq) + 1;
    if (l > r) swap(l, r);
    cout << l << " " << r << " " << char('a' + (rand() % 26)) << endl;
  }
  exit(0);
}

int main() {
  //gen();
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //auto start = clock();
  read();
  process();
  print();
  //cerr << "time = " << double(clock() - start) / CLOCKS_PER_SEC << endl;
  //cerr << "max nodes = " << max_cnt << endl;
  //cerr << "max diff = " << max_diff << endl;
  return 0;
}

/*

aba
2 5
1 4
1 12 b
2 10 b
2 9 b
3 3 a
8 11 a

--
4 3 2 1 3

*/