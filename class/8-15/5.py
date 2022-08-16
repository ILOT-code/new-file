ans = [0]*26
try:
    while True:
        str = input()
        for c in str:
            if c.islower():
                index = ord(c) - ord("a") 
                ans[index] += 1
except EOFError:
    pass

Max = 0
for i in ans:
    if i > Max:
        Max = i
for i in range(Max+1):
    lower = ""
    if i == Max:
        for j in range(97,123):
            lower += chr(j)
    else:
        for j in range(26):
            if i < Max - ans[j]:
                lower += ' '
            else:
                lower += '*'
    print(lower)
