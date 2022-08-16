def big_m(m):
    if m == 1 or m == 3 or m == 5 or m == 7 or m == 8 or m == 10 or m == 12:
        return 1
    else:
        return 0


def run(y):
    if (y % 4 == 0 and y % 100 != 0) or y % 400 == 0:
        return 1
    else:
        return 0


y, m, d = map(int, input().split())
ans = 0
for i in range(1, m):
    if big_m(i):
        ans += 31
    elif i == 2:
        ans += 28 + run(y)
    else:
        ans += 30
print(ans + d)
