import yaml
import os
from random import randint
import sys

from dotmap import DotMap

sys.setrecursionlimit(10000000)

conf = yaml.safe_load(open('../conf.yaml'))
conf = DotMap(conf, _dynamic=False)

os.system(f'g++ {conf.compile.cpp} main.cpp -o main')

def gcd(a, b):
    return a if b == 0 else gcd(b, a % b)

if __name__ == "__main__":
    conf.update
    for split in ['samples', 'data']:
        folder = {
            'samples': 'down',
            'data': 'data',
        }[split]
        for group in conf[split]:
            for case in group.cases:
                if split == 'samples' and case == 1:
                    continue
                print(f'generating {split} {case}')
                filename_in = f'../{folder}/{case}.in'
                filename_ans = f'../{folder}/{case}.ans'
                T = group.args.T
                l = group.args.l
                with open(filename_in, 'w') as f:
                    print(T, file=f)
                    nosol = [0] * T
                    if T > 1:
                        nosol[randint(0, T - 1)] = 1
                    for t in range(T):
                        d1, d2 = (randint(1, 10 ** (l // 4) - 1) for _ in range(2))
                        d = d1 * d2
                        b = d * randint(1, 10 ** (l // 2) - 1)
                        c = d * d2 * randint(1, 10 ** (l // 4) - 1)
                        # a, b, c = (randint(1, 10 ** l - 1) for _ in range(3))
                        d0 = gcd(b, c)
                        while True:
                            a = randint(1, 10 ** l - 1)
                            d = gcd(a, d0)
                            if nosol[t] and d != 1 or not nosol[t] and d == 1:
                                break

                        print(a, b, c, file=f)
                        # print('gcd:', gcd(b, c))
                os.system(f'./main < {filename_in} > {filename_ans}')
