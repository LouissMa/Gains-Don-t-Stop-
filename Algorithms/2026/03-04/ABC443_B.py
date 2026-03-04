N, K = map(int, input().split())

year = N
eaten = 0
while True:
    eaten += year
    if eaten >= K:
        print(year - N)
        break
    year += 1

