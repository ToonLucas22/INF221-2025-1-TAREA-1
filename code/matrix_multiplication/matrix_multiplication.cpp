#include "algorithms/naive.cpp"
#include "algorithms/strassen.cpp"
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
    int N[] = {2*2*2*2, 2*2*2*2*2*2, 2*2*2*2*2*2*2*2, 2*2*2*2*2*2*2*2*2*2};
    std::string T[] = {"dispersa", "diagonal", "densa"};
    std::string D[] = {"D0", "D10"};
    char M[] = {'a', 'b', 'c'};

    std::string filename;
    std::string pathTo = "./data/matrix_input/";
    std::string pathM  = "./data/measurements/";
    std::string pathOut= "./data/matrix_output/";
    double execTime;
    unsigned t0, t1;
    int beginMem, endMem, totalMemUse;
    std::ofstream measure(pathM+"a.txt");

    for (int n=0;n<4;n++) {
        for (int t=0;t<3;t++) {
            for (int d=0;d<2;d++) {
                for (int m=0;m<3;m++) {
                    filename = std::to_string(N[n])+'_'+T[t]+'_'+D[d]+'_'+M[m];
                    std::ifstream file1(pathTo+filename+"_1.txt");
                    std::ifstream file2(pathTo+filename+"_2.txt");
                    std::ofstream output(pathOut+filename+"_out.txt");
                    if (!file1) {
                        std::cout << "Oops! Error al abrir archivo "+filename+"_1.txt\n";
                        exit(EXIT_FAILURE);
                    }
                    if (!file2) {
                        std::cout << "Oops! Error al abrir archivo "+filename+"_2.txt\n";
                        exit(EXIT_FAILURE);
                    }

                    int **arr1 = new int*[N[n]], **arr2 = new int*[N[n]],
                    //**copy1 = new int*[N[n]], **copy2 = new int*[N[n]],
                    **mul1, **mul2;
                    for (int i=0;i<N[n];i++) {
                        arr1[i] = new int[(N[n])];
                        //copy1[i] = new int[(N[n])];
                        arr2[i] = new int[(N[n])];
                        //copy2[i] = new int[(N[n])];
                    }
                    for (int i=0;i<N[n];i++) {
                        for (int j=0;j<N[n];j++) {
                            file1 >> arr1[i][j];
                            //copy1[i][j] = arr1[i][j];
                            file2 >> arr2[i][j];
                            //copy2[i][j] = arr2[i][j];
                        }
                    }

                    
                    //Strassen
                    beginMem = getValue();
                    t0 = clock();
                    mul1 = strassen(arr1, arr2, N[n]); 
                    t1 = clock();
                    endMem = getValue();
                    execTime = (double(t1-t0)/CLOCKS_PER_SEC);
                    totalMemUse = endMem-beginMem;
                    measure << filename << " Strassen " << execTime << ' ' << totalMemUse << "\n";
                    std::cout << "Strassen ejecutado exitosamente para "+filename+"\n";
                    

                    //Naive
                    beginMem = getValue();
                    t0 = clock();
                    mul2 = matrixMult(arr1, arr2, N[n]);
                    t1 = clock();
                    endMem = getValue();
                    execTime = (double(t1-t0)/CLOCKS_PER_SEC);
                    totalMemUse = endMem-beginMem;
                    measure << filename << " Naive " << execTime << ' ' << totalMemUse << "\n";
                    std::cout << "Naive ejecutado exitosamente para "+filename+"\n";

                    bool sanityCheck = true;
                    for (int i=0;i<N[n];i++) {
                        for (int j=0;j<N[n];j++) {
                            sanityCheck = (mul1[i][j] == mul2[i][j]);
                            if (!sanityCheck) break;
                        }
                    }
                    
                    //El sanitycheck siempre debiera dar true
                    if (!sanityCheck) std::cout << "¡NO COINCIDEN LAS MATRICES! Usando resultado de Strassen\n";
                    for (int i=0;i<N[n];i++) {
                        for (int j=0;j<N[n];j++) {
                            output << mul2[i][j] << ' ';
                        }
                        output << "\n";
                    }

                    file1.close();
                    file2.close();
                    output.close();

                    for (int i=0;i<N[n];i++) {
                        delete[] arr1[i]; delete[] arr2[i];
                        delete[] mul1[i];
                        delete[] mul2[i];
                        arr1[i] = NULL; arr2[i] = NULL;
                        mul1[i] = NULL;
                        mul2[i] = NULL;
                    }
                    delete[] arr1; delete[] arr2;
                    delete[] mul1;
                    delete[] mul2;
                    arr1 = NULL; arr2 = NULL;
                    mul1 = NULL;
                    mul2 = NULL;
                }
            }
        }
    }

    measure.close();
}