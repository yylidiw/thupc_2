import sys
from copy import deepcopy

def gcd(a, b):
    cnt = 0
    while True:
        if b == 0:
            return a
        cnt += 1
        a, b = b, a % b

if __name__ == "__main__":
    sys.setrecursionlimit(10000000)
    T = int(input())
    for _ in range(T):
        a, b, c = map(int, input().split())
        if gcd(a, gcd(b, c)) != 1:
            print('-1')
            continue

        n = deepcopy(c)
        while True:
            # 如果是使用倍增，由于运算数字变大，辗转相除求 gcd 将非常慢（只能通过小数据）
            # 因此这里使用使用这个迭代：n_0=c, n_{i+1} = \frac{n_i}{(b, n_i)}，可以通过手动构造的第五个点以外的点
            d = gcd(b, n)
            if d == 1:
                break
            n //= d
        print(n)
