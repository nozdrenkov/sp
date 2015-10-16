# https://projecteuler.net/problem=2
# ans = 4613732

ans = 0

a = 1
b = 1
while True:
    cur = a + b
    a = b
    b = cur
    if cur > 4 * 10**6:
        break
    if cur % 2 == 0:
        ans += cur

print(ans)