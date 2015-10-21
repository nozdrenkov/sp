# https://projecteuler.net/problem=9
# ans = 31875000

from math import sqrt

def calc():
    for a in range(1, 1001):
        for b in range(a, 1001):
            c = int(sqrt(a * a + b * b))
            if (a * a + b * b == c * c and a + b + c == 1000):
                return a * b * c

print(calc())
