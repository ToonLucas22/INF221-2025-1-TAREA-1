import matplotlib
import matplotlib.pyplot as plt
import numpy as np

sorts = ['SelectionSort', 'MergeSort', 'QuickSort', 'std::sort']
sizes = [10, 1000, 100000, 10000000]
indices = [0, 73, 145, 217, 271]

measures = open("../data/measurements/a.txt")

for i in range(4):
  cntAsc1 = [0]*4
  cntDes1 = [0]*4
  cntRnd1 = [0]*4
  cntAsc7 = [0]*4
  cntDes7 = [0]*4
  cntRnd7 = [0]*4
  avgTimeAsc1 = [0]*4
  avgTimeDes1 = [0]*4
  avgTimeRnd1 = [0]*4
  avgTimeAsc7 = [0]*4
  avgTimeDec7 = [0]*4
  avgTimeRnd7 = [0]*4
  n = sizes[i]
  for j in range(indices[i], indices[i+1]):
    line = measures.readline().strip().split()
    modes = filename[0].strip(".txt").split("_")
    sortMode = sorts.find(line[1])
    type = modes[1]
    d = modes[2]
    eTime = float(line[2])
    if d == "D1":
      if type == 'ascendente':
        cntAsc1[sortMode] += 1
        avgTimeAsc1[sortMode] += eTime
      elif type == 'descendente':
        cntDes1[sortMode] += 1
        avgTimeDes1[sortMode] += eTime
      else:
        cntRnd1[sortMode] += 1
        avgTimeRnd1[sortMode] += eTime
    else:
      if type == 'ascendente':
        cntAsc7[sortMode] += 1
        avgTimeAsc7[sortMode] += eTime
      elif type == 'descendente':
        cntDes7[sortMode] += 1
        avgTimeDes7[sortMode] += eTime
      else:
        cntRnd7[sortMode] += 1
        avgTimeRnd7[sortMode] += eTime
