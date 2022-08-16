def isprime(n):
    if n == 1:
        return 0
    for i in range(2,n-1):
        if n%i==0:
            return 0
    return 1

num = int(input())
ans = isprime(num)
print(ans)
