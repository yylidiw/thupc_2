import yaml
import os
from random import randint

from dotmap import DotMap

conf = yaml.safe_load(open('../conf.yaml'))
conf = DotMap(conf, _dynamic=False)

os.system(f'g++ {conf.compile.cpp} main.cpp -o main')

if __name__ == "__main__":
    T = conf.args.T
    for split in ['samples', 'data']:
        folder = {
            'samples': 'down',
            'data': 'data',
        }[split]
        for group in conf[split]:
            len = group.args.len
            for case in group.cases:
                print(f'generating {split} {case}')

                filename_in = f'../{folder}/{case}.in'
                filename_ans = f'../{folder}/{case}.ans'
                with open(filename_in, 'w') as f:
                    print(T, file=f)
                    for _ in range(T):
                        a, b, c = (randint(1, 10 ** (len + 1) - 1) for _ in range(3))
                        print(a, b, c, file=f)
                os.system(f'./main < {filename_in} > {filename_ans}')
