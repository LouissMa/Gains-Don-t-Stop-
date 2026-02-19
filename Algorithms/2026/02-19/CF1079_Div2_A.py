for _ in range(int(input())):
    n = int(input())
    c = 0
    for i in range(n,n + 100):
        x = sum(int(j) for j in str(i))
        if i - x == n:
            c += 1
    print(c)
    