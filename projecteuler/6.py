# https://projecteuler.net/problem=6
# ans = 25164150

a = sum(range(1, 101)) ** 2
b = sum([i * i for i in range (1, 101)])
ans = a - b

print(ans)
