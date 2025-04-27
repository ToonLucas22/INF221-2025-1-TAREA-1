#include <vector>
#include "memusage.cpp"

/*
    Ambas funciones han sido extraídas del PPT #6
    del ramo de INF-221 en el AULA y modificados
    levemente para trabajar con vectores
*/

int partition(std::vector<int> &A, int i, int d, int p) {
    i--;
    d++;
    do {
        i++;
        while (A[i] < A[p]) i++;
        d--;
        while (i < d && A[d] > A[p]) d--;
        if (i<d)
            std::swap(A[i], A[d]);
    } while (i<d);
    
    return i;
}

void QuickSort(std::vector<int> &A, int i, int d) {
    int n = d - i +1;
    if (n <= 1) return;
    else {
        int p = i+n/2;
        std::swap(A[p], A[d]);
        int k = partition(A, i, d-1, d);
        std::swap(A[k], A[d]);
        if (k == d-1)
            k = d;
        QuickSort (A, i, k-1);
        QuickSort(A, k+1, d);
    }
    curMemUsage = getValue();
}