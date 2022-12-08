import matplotlib.pyplot as plt
import json
import numpy as np
import io
from scipy import signal
import pandas as pd

mylist = json.load(io.open('try4_res.json', 'r'))
#test for me
#list2 = mylist[0:10000]

#initializing lists
t = []
freq = []
mag = []

#parsing through first list to get to dictionaries
for n, i in enumerate(mylist):
    # getting data points
    mag.append([])
    data_dict = i
    t.append(data_dict["tsf"])
    for j in data_dict["data"]:
        if n == 0:
            freq.append(j[0])
        mag[n].append(j[1])

print(len(mag))
mag_t = pd.DataFrame(mag).T.values.tolist()
print(len(mag_t))
print(len(t))
print(len(freq))

plt.pcolormesh(t, freq, mag_t, shading='gouraud')
plt.ylabel('Frequency [Hz]')
plt.xlabel('Time []')
plt.show()

exit()

