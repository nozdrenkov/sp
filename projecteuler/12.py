# https://projecteuler.net/problem=12
# ans = 76576500

def divs(num):
    d = 2
    res = 2
    while d * d <= num:
        if num % d == 0:
            res += 1 if d * d == num else 2
        d += 1
    return res

def calc(cnt):
    sum = 0
    for i in range(1, 1000000):
        sum += i
        if divs(sum) > cnt:
            #print(i)
            return sum
    return -1

print(calc(500))