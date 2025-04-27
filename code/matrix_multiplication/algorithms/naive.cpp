#include <vector>

/*
    Esta implementación del algoritmo naive ha sido tomada del siguiente sitio:
    https://medium.com/swlh/strassens-matrix-multiplication-algorithm-936f42c2b344
    Strassen Matrix Multiplication | C++ | The Startup, Saahil Mahato, Medium, consultado el 27 de abril de 2025
*/

int** matrixMult(int** A, int** B, int n) {
    int** C = new int*[n];
    for(int i=0; i<n; i++) {
        C[i] = new int[n];
        for(int j=0; j<n; j++) {
            C[i][j] = 0;
            for(int k=0; k<n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    }
    return C;
}