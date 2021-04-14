import sys

def gcd(a, b):
    return a if b == 0 else gcd(b, a % b)

if __name__ == "__main__":
    sys.setrecursionlimit(10000000)
    T = int(input())
    for _ in range(T):
        a, b, c = map(int, input().split())
        if gcd(a, gcd(b, c)) != 1:
            print('-1')
            continue

        while True:
            d = gcd(b, c)
            if d == 1:
                break
            c //= d
        print(c)
