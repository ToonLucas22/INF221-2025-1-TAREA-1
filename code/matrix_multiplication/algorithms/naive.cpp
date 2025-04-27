#include <vector>

/*
    Este algoritmo ha sido extraido del PPT 5 Parte 2
    del ramo de INF-221, semestre 2025-1, y modificado
    para trabajar con vectores de vectores de enteros
    en vez de punteros a punteros a enteros
*/

std::vector<std::vector<int>> matrixMult(std::vector<std::vector<int>> &M1, std::vector<std::vector<int>> &M2, int n) {
    // Se crea la matriz M de n x n
    std::vector<std::vector<int>> M = std::vector<std::vector<int>>(n);
    for (int i=0;i<n;++i)
        M[i] = std::vector<int>(n);
    // Cálculo de cada casilla M[i][j]
    for (int i=0;i<n;++i){
        for (int j=0;j<n;++j) {
            M[i][j] = 0;
            for (int k=0;k<n;++k)
                M[i][j] += M1[i][k]*M[k][j];
        }
    }
    return M;
}