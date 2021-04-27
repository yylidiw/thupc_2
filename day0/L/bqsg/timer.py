import os
import time
x = []
for i in range(100):
  time_start=time.time()
  val = os.system('./std < "../data/4.in" >/dev/null')
  time_end = time.time()
  print(time_end-time_start)