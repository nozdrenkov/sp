# https://projecteuler.net/problem=13
# ans = 5537376230

f = open('input.txt', 'r')
sum = 0
for x in f:
    sum += int(x.strip())

print(str(sum)[0:10])