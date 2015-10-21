# https://projecteuler.net/problem=11
# ans = 70600674

def calc(mat, k = 4):
    n = len(mat)
    ans = 0
    for x in range(n):
        for y in range(n):
            for dx in range(2):
                for dy in range(-1, 2):
                    if dx != 0 or dy != 0:
                        mx = x + (k - 1) * dx
                        my = y + (k - 1) * dy
                        if (0 <= mx and mx < n and 0 <= my and my < n):
                            prod = 1
                            for i in range(k):
                                prod *= mat[x + i * dx][y + i * dy]
                            ans = max(ans, prod)
    return ans

f = open('input.txt' , 'r')
mat = [list(map(int, line.strip().split(' '))) for line in f]

print(calc(mat, 4))
