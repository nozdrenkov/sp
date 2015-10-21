# https://projecteuler.net/problem=10
# ans = 142913828922

from math import sqrt

def calc(n):
    prime = [True] * n
    prime[0] = prime[1] = False
    sum = 0
    for i in range(2, n):
        if prime[i] == True:
            sum += i
            for j in range(i * i, n, i):
                prime[j] = False
    return sum

print(calc(2 * 10**6))
