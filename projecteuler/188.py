# https://projecteuler.net/problem=188
# ans = 95962097

import sys

sys.setrecursionlimit(2**29)

def phi(n):
    res = n
    d = 2
    while d * d <= n:
        if n % d == 0:
            while n % d == 0:
                n //= d
            res -= res // d
        d += 1
    if n > 1:
        res -= res // n
    return res

def binpow(a, n, mod):
    if n == 0:
        return 1
    r = binpow(a, n // 2, mod)
    r *= r
    r %= mod
    if n % 2 == 1:
        r *= a
        r %= mod
    return r

def func(p, b, mod):
    if b == 1:
        return p
    return binpow(p, func(p, b - 1, phi(mod)), mod)

print(func(1777, 1855, 10**8))
