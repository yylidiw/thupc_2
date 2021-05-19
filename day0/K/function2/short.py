import sys
from copy import deepcopy

# from math import gcd

def gcd(a, b):
    cnt = 0
    while True:
        if b == 0:
            return a
        cnt += 1
        a, b = b, a % b

def solve_iter(b, c):
    n = deepcopy(c)
    while True:
        d = gcd(b, n)
        if d == 1:
            break
        n //= d
    return n

def solve_double(b, c):
    d = gcd(b, c)
    while True:
        d2 = gcd(c, d * d)
        # print('d2:', d2)
        if d2 == d:
            break
        d = d2
    return c // d

if __name__ == "__main__":
    sys.setrecursionlimit(10000000)
    T = int(input())
    for _ in range(T):
        a, b, c = map(int, input().split())
        if gcd(a, gcd(b, c)) != 1:
            print('-1')
            continue
        n = solve_iter(b, c)
        print(n)
