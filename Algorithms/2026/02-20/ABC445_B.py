n = int(input())
l = []
maxx = 0
for i in range(n):
    s = input()
    if len(s) > maxx:
        maxx = len(s)
    l.append(s)
for s in l :
    print(s.center(maxx,'.'))