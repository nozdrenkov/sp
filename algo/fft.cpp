#include <bits/stdc++.h>

using namespace std;

typedef complex<double> num;

const int K = 20;
const int N = 1 << K;

num root[N];
int rev[N];

void init() {
  const double pi = acos(-1);
  for (int i = 0; i < N; ++i) {
    double angle = 2 * pi * i / N;
    root[i] = num(cos(angle), sin(angle));
    rev[i] = rev[i / 2] / 2 | (i & 1) << (K - 1);
  }
}

void fft(num *a) {
  for (int i = 0; i < N; ++i) {
    if (i < rev[i]) {
      swap(a[i], a[rev[i]]);
    }
  }
  for (int bs = 2; bs <= N; bs *= 2) {
    for (int st = 0; st < N; st += bs) {
      int k = bs / 2;
      for (int i = 0; i < k; ++i) {
        num v1 = a[st + i];
        num v2 = a[st + i + k] * root[i * (N / bs)];
        a[st + i]     = v1 + v2;
        a[st + i + k] = v1 - v2;
      }
    }
  }
}

void inv(num *a) {
  fft(a);
  reverse(a + 1, a + N);
  for (int i = 0; i < N; ++i) {
    a[i] /= N;
  }
}
