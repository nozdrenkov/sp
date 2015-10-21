# https://projecteuler.net/problem=4
# ans = 906609

ans = 0

for a in range(10**2, 10**3):
    for b in range(a, 10**3):
        p = a * b
        s = str(p)
        if (s == s[::-1] and p > ans):
            ans = p

print(ans)