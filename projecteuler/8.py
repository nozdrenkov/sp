# https://projecteuler.net/problem=8
# ans = 23514624000

from functools import reduce
from operator import mul

def calc(s, k):
    ans = 0
    for i in range(0, len(s) - k + 1):
        a = list(map(int, s[i:i + k]))
        cur = reduce(mul, a, 1)
        ans = max(ans, cur)
    return ans

s = input()
print(calc(s, 13))
