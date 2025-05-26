#Cynthia's Part!:
"""
Goal: Rewrite this such that it makes a request once,
Then it makes a request again
We should always be requesting data from the server 
"""

import requests
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import sys

#set up router 
url = 'http://127.0.0.1:5000/plot'
unit = "hPa"
consts = {"hPa": 1013.25, "atm": 1, "Pa": 101325, "mmHg": 760}
begin_const = consts[unit]
times = [0]
pressures = [begin_const]
distances = [0]
fig, (ax, ax2) = plt.subplots(1, 2, figsize=(10, 5))
plt.subplots_adjust(bottom=0.2) 
colors = ['#1f77b4', '#ff7f0e', '#2ca02c']

graph, = ax.plot(times, pressures, color=colors[0])
graph2, = ax2.plot(times, distances, color=colors[1])

test = input("T or F: ")
flag = (test == 'T')
counter = 0
pCounter = 0
dCounter = 0

    
# Update our graph by grabbing a request
def GETRequest():
    json = requests()
    return json
def main():
    return
if __name__ == '__main__':
    #check if this is good
    main()