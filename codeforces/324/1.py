n, t = map(int, input().split())
v = t
while True:
    l = len(str(v))
    if l > n:
        print("-1")
        break
    if l == n:
        print(v)
        break
    v *= t