import sys
import random

def check(s):
    if s[0] == '0' or s[-1] == '0':
        return False
    ans = []
    for base in range(2, 11):
        num = 0;
        for c in s:
            num *= base
            if c == '1':
                num += 1

        d = 2
        div = -1
        while d * d <= num:
            if num % d == 0:
                div = d
                break
            if d > 50000:
                return False
            d += 1

        if div == -1:
            return False
        ans.append(div)
    
    print(s + ' ' + ' '.join(map(str, ans)))
    return True

def calc():
    n, k = map(int, input().split())
    if n > 7:
        used = set()
        while k > 0:
            s = ''.join(random.choice('01') for _ in range(n))
            if (s not in used and check(s)):
                k -= 1
            used.add(s)
    else:
        for mask in range(1, 2 ** n):
            if k == 0:
                break
            get_bin = lambda x, n: format(x, 'b').zfill(n)
            s = get_bin(mask, n)
            if len(s) == n and check(s):
                k -= 1


t = int(input())
for i in range(1, t + 1):
    print('Case #{0}:'.format(i))
    sys.stderr.write(str(i) + '\n')
    calc()

sys.stderr.write('Ready!\n')
