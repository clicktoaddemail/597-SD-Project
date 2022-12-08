import matplotlib.pyplot as plt
import json
import numpy as np
import io
from scipy import signal
import pandas as pd
from obspy.imaging.spectrogram import spectrogram

mylist = json.load(io.open('try2_res.json', 'r'))
mylist = mylist[:10000]
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
    t.append(data_dict["tsf"]/1000000)
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
plt.xlabel('Time [ns]')
plt.colorbar(label = "Power dB") #Adding color bar
plt.show()

exit()

## LINE GRAPH ##
#plt.plot(t, f_avg, color='maroon', marker='o')
#plt.xlabel('variable')
#plt.ylabel('value')

#plt.show()
