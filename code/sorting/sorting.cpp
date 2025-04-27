#include "algorithms/mergesort.cpp"
#include "algorithms/quicksort.cpp"
#include "algorithms/selectionsort.cpp"
#include "algorithms/sort.cpp"
#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

/*
    Las siguientes funciones parseLine y getValue han sido tomadas
    de esta página de stackoverflow:
    https://stackoverflow.com/questions/63166/how-to-determine-cpu-and-memory-consumption-from-inside-a-process

    Su propósito es parsear el valor arrojado por el kernel correspondiente
    a la memoria usada por el proceso actual y luego retornar tal valor.
*/

int parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

int getValue(){ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmRSS:", 6) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

int main() {
    int N[] = {10, 1000, 100000, 10000000};
    std::string T[] = {"ascendente", "descendente", "aleatorio"};
    std::string D[] = {"D1", "D7"};
    char M[] = {'a', 'b', 'c'};

    std::string filename;
    std::string pathTo = "./data/array_input/";
    std::string pathM  = "./data/measurements/";
    std::string pathOut= "./data/array_output/";
    double execTime;
    unsigned t0, t1;
    int beginMem, endMem, totalMemUse;
    std::ofstream measure(pathM+"a.txt");

    for (int n=0;n<4;n++) {
        for (int t=0;t<3;t++) {
            for (int d=0;d<2;d++) {
                for (int m=0;m<3;m++) {
                    filename = std::to_string(N[n])+'_'+T[t]+'_'+D[d]+'_'+M[m]+".txt";
                    std::ifstream file(pathTo+filename);
                    std::ofstream output(pathOut+filename.substr(0,filename.size()-4)+"_out.txt");
                    if (!file) {
                        std::cout << "Oops! Error al abrir archivo "+filename+"\n";
                        exit(EXIT_FAILURE);
                    }
                    std::vector<int> arr(N[n]), copy1(N[n]), copy2(N[n]), copy3(N[n]);
                    for (int i=0;i<N[n];i++) {
                        file >> arr[i];
                        copy1[i] = arr[i];
                        copy2[i] = arr[i];
                        copy3[i] = arr[i];
                    }

                    //std::sort
                    beginMem = getValue();
                    t0 = clock();
                    sortArray(arr);
                    t1 = clock();
                    endMem = getValue();
                    execTime = (double(t1-t0)/CLOCKS_PER_SEC);
                    totalMemUse = endMem-beginMem;
                    measure << filename << " std::sort " << execTime << ' ' << totalMemUse << "\n";
                    std::cout << "std::sort ejecutado exitosamente para "+filename+"\n";

                    //MergeSort
                    beginMem = getValue();
                    t0 = clock();
                    mergeSort(copy1);
                    t1 = clock();
                    endMem = getValue();
                    execTime = (double(t1-t0)/CLOCKS_PER_SEC);
                    measure << filename << " MergeSort " << execTime << ' ' << totalMemUse << "\n";
                    std::cout << "MergeSort ejecutado exitosamente para "+filename+"\n";

                    //QuickSort
                    beginMem = getValue();
                    t0 = clock();
                    QuickSort(copy2, 0, N[n]-1);
                    t1 = clock();
                    endMem = getValue();
                    execTime = (double(t1-t0)/CLOCKS_PER_SEC);
                    measure << filename << " QuickSort " << execTime << ' ' << totalMemUse << "\n";
                    std::cout << "QuickSort ejecutado exitosamente para "+filename+"\n";

                    //SelectionSort; Se omite si N[n] = 10^7, al demorarse demasiado
                    if (n != 3) {
                        beginMem = getValue();
                        t0 = clock();
                        selectionSort(copy3);
                        t1 = clock();
                        endMem = getValue();
                        execTime = (double(t1-t0)/CLOCKS_PER_SEC);
                        measure << filename << " SelectionSort " << execTime << ' ' << totalMemUse << "\n";
                        std::cout << "SelectionSort ejecutado exitosamente para "+filename+"\n";
                    } else {
                        for (int i=0;i<N[n];i++) {
                            copy3[i] = arr[i];
                        }
                        std::cout << "SelectionSort omitido por lentitud\n";
                    }

                    bool sanityCheck = true;
                    for (int i=0;i<N[n];i++) {
                        sanityCheck = (arr[i]==copy1[i] && copy2[i]==copy3[i]) && copy1[i]==copy2[i];
                        if (!sanityCheck) break;
                    }
                    
                    //El sanitycheck siempre debiera dar true
                    if (!sanityCheck) std::cout << "¡NO COINCIDEN LOS ARREGLOS! Usando resultado de std::sort por defecto\n";
                    for (int i=0;i<N[n];i++) {
                        output << arr[i] << ' ';
                    } output << "\n";

                    file.close();
                    output.close();
                }
            }
        }
    }

    measure.close();
}