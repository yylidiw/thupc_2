from random import random
import numpy as np
from tqdm import tqdm
N = 999999
alpha = random()*np.pi*2
beta = 1524*np.pi/100000/2
center = np.array([np.cos(alpha) * np.sin(beta), np.sin(alpha) * np.sin(beta), np.cos(beta)])
r = 77553*np.pi/100000/2
print(N)
lst = []
def maxz(elem):
    return elem[1] + elem[2]

for i in tqdm(range(N)):
  while True:
    na = np.pi  * 100 * 2 * i  / N 
    nb = np.pi / 2 * random()
    ncenter = np.array([np.cos(na) * np.sin(nb), np.sin(na) * np.sin(nb), np.cos(nb)])  
    dist = np.arccos(ncenter.dot(center))
    if dist < r:
      nr = (r - dist) * (random()**2)
      if(nr < ncenter[2]):
        break
  lst.append([na,nb,nr])

lst.sort(key=maxz)

for i in tqdm(range(N)):
  na = lst[i][0]
  nb = lst[i][1]
  nr = lst[i][2]
  ncenter = np.array([np.cos(na) * np.sin(nb), np.sin(na) * np.sin(nb), np.cos(nb)])  
  L = random() * 260817 + 654321
  rcenter = list(np.round(L * ncenter))
  rr = np.ceil(L * np.sin(nr))
  print("%d %d %d %d" % (rcenter[0], rcenter[1], rcenter[2], rr))
  