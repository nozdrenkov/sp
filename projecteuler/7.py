# https://projecteuler.net/problem=7
# ans = 104743

def calc(idx):
    maxn = 10**6
    prime = [True] * maxn
    prime[0] = prime[1] = False
    primes = []
    for i in range(2, maxn):
        if prime[i] == True:
            primes.append(i)
            for j in range(i * i, maxn, i):
                prime[j] = False
    return primes[idx]

print(calc(10**4))