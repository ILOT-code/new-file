words = []
try:
    while True:
        word = input()
        words.append(word)
except EOFError:
    pass
words.sort()
for word in words:
    print(word)
