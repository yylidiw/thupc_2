from random import random
import numpy as np
N = 999999
alpha = np.pi/3
beta = np.pi/6
center = np.array([np.cos(alpha) * np.sin(beta), np.sin(alpha) * np.sin(beta), np.cos(beta)])
r = np.pi/4
for i in range(N):
  while True:
    na = np.pi * 2 / 3 * random()
    nb = np.pi / 3 * random()
    ncenter = np.array([np.cos(na) * np.sin(nb), np.sin(na) * np.sin(nb), np.cos(nb)])  
    dist = np.arccos(ncenter.dot(center))
    if dist < r:
      nr = (r - dist) * (random() + 1) / 2
      if(nr < ncenter[2]):
        break
  L = random() * 4000000 + 2000000
  rcenter = list(np.round(L * ncenter))
  rr = np.round(L * np.sin(nr))
  print("%d %d %d %d" % (rcenter[0], rcenter[1], rcenter[2], rr))
  