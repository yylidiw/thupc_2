from random import random
import numpy as np
from tqdm import tqdm
N = 1000000
alpha = random()*np.pi*2
beta = 18547*np.pi/100000/2
center = np.array([np.cos(alpha) * np.sin(beta), np.sin(alpha) * np.sin(beta), np.cos(beta)])
r = 62845*np.pi/100000/2
print(N+2)
for i in tqdm(range(N)):
  while True:
    na = np.pi * 2 * random()
    nb = np.pi / 2 * random()
    ncenter = np.array([np.cos(na) * np.sin(nb), np.sin(na) * np.sin(nb), np.cos(nb)])  
    dist = np.arccos(ncenter.dot(center))
    if dist < r:
       nr = (r - dist) * (random() + 1) / 2
       if(nr < ncenter[2]):
         break
  # ncenter = np.array([np.cos(na) * np.sin(nb), np.sin(na) * np.sin(nb), np.cos(nb)])

  L = random() * 200000 + 770000
  rcenter = list(np.round(L * ncenter))
  rr = np.ceil(L * np.sin(nr))
  print("%d %d %d %d" % (rcenter[0], rcenter[1], rcenter[2], rr))
  


# L1 = 987654
# beta1 = beta + 12311*np.pi/100000/2
# alpha1 = 4*np.pi/3
# r1 = 36263*np.pi/100000/2
# center1 = np.array([np.cos(alpha1) * np.sin(beta1), np.sin(alpha1) * np.sin(beta1), np.cos(beta1)])
# rcenter1 = list(np.round(L1 * center1))
# rr1 = np.ceil(L1 * np.sin(r1))
# print("%d %d %d %d" % (rcenter1[0], rcenter1[1], rcenter1[2], rr1))

# L2 = 975310

# beta2 = beta - 12311*np.pi/100000/2
# alpha2 = 4*np.pi/3
# r2 = 40263*np.pi/100000/2
# center2 = np.array([np.cos(alpha2) * np.sin(beta2), np.sin(alpha2) * np.sin(beta2), np.cos(beta2)])

# rcenter2 = list(np.round(L2 * center2))
# rr2 = np.ceil(L2 * np.sin(r2))
# print("%d %d %d %d" % (rcenter2[0], rcenter2[1], rcenter2[2], rr2))