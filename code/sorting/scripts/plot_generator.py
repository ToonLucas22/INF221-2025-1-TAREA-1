import matplotlib
import matplotlib.pyplot as plt
import numpy as np

# Función tomada del siguiente sitio:
# https://facialix.com/tutorial-creacion-de-graficas-en-python-usando-matplotlib/
def autolabel(rects):
    """Funcion para agregar una etiqueta con el valor en cada barra"""
    for rect in rects:
        height = rect.get_height()
        ax.annotate('{}'.format(round(height,2)),
                    xy=(rect.get_x() + rect.get_width() / 2, height),
                    xytext=(0, 3),  # 3 points vertical offset
                    textcoords="offset points",
                    ha='center', va='bottom')

sorts = ['SelectionSort', 'MergeSort', 'QuickSort', 'std::sort']
sizes = [10, 1000, 100000, 10000000]
indices = [1, 73, 145, 217, 271]
doms = ['D1', 'D7']

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
  avgTimeDes7 = [0]*4
  avgTimeRnd7 = [0]*4
  n = sizes[i]
  for j in range(indices[i], indices[i+1]):
    line = measures.readline().strip().split()
    modes = line[0].strip(".txt").split("_")
    sortMode = sorts.index(line[1])
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
  for j in range(4):
    if (cntAsc1[j] != 0):
      avgTimeAsc1[j] /= cntAsc1[j]
    if (cntDes1[j] != 0):
      avgTimeDes1[j] /= cntDes1[j]
    if (cntRnd1[j] != 0):
      avgTimeRnd1[j] /= cntRnd1[j]
    if (cntAsc7[j] != 0):
      avgTimeAsc7[j] /= cntAsc7[j]
    if (cntDes7[j] != 0):
      avgTimeDes7[j] /= cntDes7[j]
    if (cntRnd7[j] != 0):
      avgTimeRnd7[j] /= cntRnd7[j]
    
  # El siguiente código es mayormente tomado del sitio
  # https://facialix.com/tutorial-creacion-de-graficas-en-python-usando-matplotlib/

  x = np.arange(len(sorts))
  width = 0.2
  
  for j in range(2):
    fig, ax = plt.subplots()
    if j==0:
      toUseA = avgTimeAsc1
      toUseD = avgTimeDes1
      toUseR = avgTimeRnd1
    else:
      toUseA = avgTimeAsc7
      toUseD = avgTimeDes7
      toUseR = avgTimeRnd7
    rectsAsc = ax.bar(x - width, toUseA, width, label='Ascendente')
    rectsDes = ax.bar(x,         toUseD, width, label='Descendente')
    rectsRnd = ax.bar(x + width, toUseR, width, label='Aleatorio')

    ax.set_ylabel('Tiempo de ejecución (s)')
    ax.set_title('Tiempo de ejecución de algoritmos de ordenamiento en '+doms[j])
    ax.set_xticks(x)
    ax.set_xticklabels(sorts)
    ax.legend()

    autolabel(rectsAsc)
    autolabel(rectsDes)
    autolabel(rectsRnd)
    fig.tight_layout()

    plt.savefig('../data/plots/'+str(n)+'_'+doms[j]+'.png')

measures.close()
