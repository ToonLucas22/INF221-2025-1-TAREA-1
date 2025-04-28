import matplotlib
import matplotlib.pyplot as plt
import numpy as np

# Función tomada del siguiente sitio:
# https://facialix.com/tutorial-creacion-de-graficas-en-python-usando-matplotlib/
def autolabel(rects):
    """Funcion para agregar una etiqueta con el valor en cada barra"""
    for rect in rects:
        height = rect.get_height()
        ax.annotate('{}'.format(height),
                    xy=(rect.get_x() + rect.get_width() / 2, height),
                    xytext=(0, 3),  # 3 points vertical offset
                    textcoords="offset points",
                    ha='center', va='bottom')

mults = ['Strassen', 'Naive']
sizes = [16, 64, 256, 1024]
indices = [1, 37, 73, 109, 145]
doms = ['D1', 'D10']

measures = open("../data/measurements/a.txt")

for i in range(4):
  cntDsp1 = [0]*2
  cntDgn1 = [0]*2
  cntDen1 = [0]*2
  cntDsp10 = [0]*2
  cntDgn10 = [0]*2
  cntDen10 = [0]*2
  avgTimeDsp1 = [0]*2
  avgTimeDgn1 = [0]*2
  avgTimeDen1 = [0]*2
  avgTimeDsp10 = [0]*2
  avgTimeDgn10 = [0]*2
  avgTimeDen10 = [0]*2
  n = sizes[i]
  for j in range(indices[i], indices[i+1]):
    line = measures.readline().strip().split()
    modes = filename[0].strip(".txt").split("_")
    multMode = mults.find(line[1])
    type = modes[1]
    d = modes[2]
    eTime = float(line[2])
    if d == "D1":
      if type == 'dispersa':
        cntDsp1[multMode] += 1
        avgTimeDgn1[sortMode] += eTime
      elif type == 'diagonal':
        cntDgn1[multMode] += 1
        avgTimeDgn1[sortMode] += eTime
      else:
        cntDen1[multMode] += 1
        avgTimeDen1[sortMode] += eTime
    else:
      if type == 'dispersa':
        cntDsp10[multMode] += 1
        avgTimeDsp10[sortMode] += eTime
      elif type == 'diagonal':
        cntDgn10[multMode] += 1
        avgTimeDgn10[sortMode] += eTime
      else:
        cntDen10[multMode] += 1
        avgTimeDen10[sortMode] += eTime
  for j in range(2):
    if (cntDsp1[j] != 0):
      avgTimeDsp1[j] /= cntDsp1[j]
    if (cntDgn1[j] != 0):
      avgTimeDgn1[j] /= cntDgn1[j]
    if (cntRnd1[j] != 0):
      avgTimeDen1[j] /= cntDen1[j]
    if (cntDsp10[j] != 0):
      avgTimeDsp10[j] /= cntDsp10[j]
    if (cntDgn10[j] != 0)
      avgTimeDgn10[j] /= cntDgn10[j]
    if (cntDen10[j] != 0)
      avgTimeDen10[j] /= cntDen10[j]
    
  # El siguiente código es mayormente tomado del sitio
  # https://facialix.com/tutorial-creacion-de-graficas-en-python-usando-matplotlib/

  x = np.arrange(len(sorts))
  width = 0.6
  
  for j in range(2):
    fig, ax = plt.subplots()
    if j==0:
      toUseA = avgTimeDsp1
      toUseD = avgTimeDgn1
      toUseR = avgTimeDen1
    else:
      toUseA = avgTimeDsp10
      toUseD = avgTimeDgn10
      toUseR = avgTimeDen10
    rectsAsc = ax.bar(x - width, toUseA, width, label='Dispersa')
    rectsDes = ax.bar(x,         toUseD, width, label='Diagonal')
    rectsRnd = ax.bar(x + width, toUseR, width, label='Densa')

    ax.set_ylabel('Tiempo de ejecución (s)')
    ax.set_title('Tiempo de ejecución de multiplicación de matrices en '+doms[j])
    ax.set_xticks(x)
    ax.set_xticklabels(sorts)
    ax.legend()

    autolabel(rectsAsc)
    autolabel(rectsDes)
    autolabel(rectsRnd)
    fig.tight_layout()

    plt.savefig('../data/plots/'+str(n)+'_'+doms[j]+'.png')

measures.close()
