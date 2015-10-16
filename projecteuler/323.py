# https://projecteuler.net/problem=323
# ans = 6.3551758451

def f(len, n):
    return (1.0 - (2.0 ** (-len))) ** n

def calc(n):
    k = 1000000
    ans = 0.0
    for len in range(1, k):
        cur = f(len, n) - f(len - 1, n)
        ans += len * cur
    return ans

print("%.10f" % calc(32))