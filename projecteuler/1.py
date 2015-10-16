# https://projecteuler.net/problem=1
# ans = 233168

ans = 0
for x in range(1, 1000):
    if x % 3 == 0 or x % 5 == 0:
        ans += x

print(ans)