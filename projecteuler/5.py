# https://projecteuler.net/problem=5
# ans = 232792560

def check(num):
    for i in range(2, 21):
        if num % i != 0:
            return False
    return True

def calc():
    num = 1
    while True:
        if check(num):
            return num
        num += 1

print(calc())