import yaml
import os
import random
from random import randint
import sys
from math import log

from dotmap import DotMap

sys.setrecursionlimit(10000000)
random.seed(91184)

conf = yaml.safe_load(open('../conf.yaml'))
conf = DotMap(conf, _dynamic=False)

os.system(f'g++ {conf.compile.cpp} std.cpp -o std')

def gcd(a, b):
    return a if b == 0 else gcd(b, a % b)

def gen_fib(up):
    x, y = 1, 1
    while True:
        z = x + y
        if z >= up:
            return x, y
        x, y = y, z

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
                        if split == 'data' and case == 4:
                            b, c = gen_fib(10 ** randint(l // 4 * 3, l))
                        elif split == 'data' and case == 5:
                            base = 2 + t
                            while True:
                                b = randint(1, 10 ** l // base)
                                if gcd(b, base) == 1:
                                    break
                            b *= base
                            c = base ** int(l * log(10) / log(base))
                        else:
                            d1, d2 = (randint(1, 10 ** (l // 4) - 1) for _ in range(2))
                            d = d1 * d2
                            b = d * randint(1, 10 ** (l // 2) - 1)
                            c = d * d2 * randint(1, 10 ** (l // 4) - 1)
                            d0 = gcd(b, c)
                        while True:
                            a = randint(1, 10 ** l - 1)
                            d = gcd(a, d0)
                            if nosol[t] and d != 1 or not nosol[t] and d == 1:
                                break

                        print(a, b, c, file=f)

                os.system(f'./std < {filename_in} > {filename_ans}')
