#include <vector>

/*
    Esta implementación del algoritmo ha sido tomada del siguiente sitio:
    https://medium.com/swlh/strassens-matrix-multiplication-algorithm-936f42c2b344
    Strassen Matrix Multiplication | C++ | The Startup, Saahil Mahato, Medium, consultado el 27 de abril de 2025
*/

int** add(int** A, int** B, int n) {
    int** temp = new int*[n];
    for(int i=0; i<n; i++) {
        temp[i] = new int[n];
        for(int j=0; j<n; j++)
            temp[i][j] = (A[i][j] + B[i][j]);
    }
    return temp;
}
int** subtract(int** A, int** B, int n) {
    int** temp = new int*[n];
    for(int i=0; i<n; i++) {
        temp[i] = new int[n];
        for(int j=0; j<n; j++)
            temp[i][j] = A[i][j] - B[i][j];
    }
    return temp;
}

int** strassen(int** A, int** B, int n) {
    //Caso base
    if (n == 1) {
        int** C = new int*[1];
        C[0] = new int[1];
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    //Construcción de la matriz solución
    int** C = new int*[n];
    for (int i=0;i<n;i++) {
        C[i] = new int[n];
    }
    int k = n/2;

    //Se construyen las submatrices de tamaño k=n/2 X k=n/2
    int** A11 = new int*[k];
    int** A12 = new int*[k];
    int** A21 = new int*[k];
    int** A22 = new int*[k];
    int** B11 = new int*[k];
    int** B12 = new int*[k];
    int** B21 = new int*[k];
    int** B22 = new int*[k];
    for (int i=0;i<k;i++) {
        A11[i] = new int[k];
        A12[i] = new int[k];
        A21[i] = new int[k];
        A22[i] = new int[k];
        B11[i] = new int[k];
        B12[i] = new int[k];
        B21[i] = new int[k];
        B22[i] = new int[k];
    }

    //Se copian los elementos de A y B a las submatrices según corresponde
    for(int i=0; i<k; i++) {
        for(int j=0; j<k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][k+j];
            A21[i][j] = A[k+i][j];
            A22[i][j] = A[k+i][k+j];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][k+j];
            B21[i][j] = B[k+i][j];
            B22[i][j] = B[k+i][k+j];
        }
    }

    //Creación de las matrices a combinar en la matriz final
    //M = resta, P = adicion
    int** B12MB22 = subtract(B12, B22, k);
    int** A11PA12 = add(A11, A12, k);
    int** A21PA22 = add(A21, A22, k);
    int** B21MB11 = subtract(B21, B11, k);
    int** A11PA22 = add(A11, A22, k);
    int** B11PB22 = add(B11, B22, k);
    int** A12MA22 = subtract(A12, A22, k);
    int** B21PB22 = add(B21, B22, k);
    int** A11MA21 = subtract(A11, A21, k);
    int** B11PB12 = add(B11, B12, k);

    
    int** P1 = strassen(A11, B12MB22, k);
    int** P2 = strassen(A11PA12, B22, k);
    int** P3 = strassen(A21PA22, B11, k);
    int** P4 = strassen(A22, B21MB11, k);
    int** P5 = strassen(A11PA22, B11PB22, k);
    int** P6 = strassen(A12MA22, B21PB22, k);
    int** P7 = strassen(A11MA21, B11PB12, k);


    int** P5PP4 = add(P5, P4, k);
    int** P5PP4PP6 = add(P5PP4, P6, k);
    int** P5PP1 = add(P5, P1, k);
    int** P5PP1MP3 = subtract(P5PP1, P3, k);


    int** C11 = subtract(P5PP4PP6, P2, k);
    int** C12 = add(P1, P2, k);
    int** C21 = add(P3, P4, k);
    int** C22 = subtract(P5PP1MP3, P7, k);

    for(int i=0; i<k; i++) {
        for(int j=0; j<k; j++) {
            C[i][j] = C11[i][j];
            C[i][j+k] = C12[i][j];
            C[k+i][j] = C21[i][j];
            C[k+i][k+j] = C22[i][j];
        }
    }

    //liberar toda la memoria
    for (int i=0; i<k; i++) {
        delete[] P1[i]; delete[] P2[i]; delete[] P3[i]; delete[] P4[i]; delete[] P5[i]; delete[] P6[i];
        delete[] P7[i]; delete[] C11[i]; delete[] C12[i]; delete[] C21[i]; delete[] C22[i];
        delete[] B12MB22[i]; delete[] A11PA12[i]; delete[] A21PA22[i]; delete[] B21MB11[i];
        delete[] A11PA22[i]; delete[] B11PB22[i]; delete[] A12MA22[i]; delete[] B21PB22[i];
        delete[] A11MA21[i]; delete[] B11PB12[i]; delete[] P5PP4[i]; delete[] P5PP4PP6[i];
        delete[] P5PP1[i]; delete[] P5PP1MP3[i];
        delete[] A11[i]; delete[] A12[i]; delete[] A21[i]; delete[] A22[i];
        delete[] B11[i]; delete[] B12[i]; delete[] B21[i]; delete[] B22[i]; 
        P1[i] = NULL, P2[i] = NULL, P3[i] = NULL, P4[i] = NULL, P5[i] = NULL, P6[i] = NULL,
        P7[i] = NULL, C11[i] = NULL, C12[i] = NULL, C21[i] = NULL, C22[i] = NULL,
        B12MB22[i] = NULL, A11PA12[i] = NULL, A21PA22[i] = NULL, B21MB11[i] = NULL,
        A11PA22[i] = NULL, B11PB22[i] = NULL, A12MA22[i] = NULL, B21PB22[i] = NULL,
        A11MA21[i] = NULL, B11PB12[i] = NULL, P5PP4[i] = NULL, P5PP4PP6[i] = NULL,
        P5PP1[i] = NULL, P5PP1MP3[i] = NULL;
        A11[i] = NULL, A12[i] = NULL, A21[i] = NULL, A22[i] = NULL;
        B11[i] = NULL, B12[i] = NULL, B21[i] = NULL, B22[i] = NULL;
    }
    delete[] P1; delete[] P2; delete[] P3; delete[] P4; delete[] P5; delete[] P6; delete[] P7; delete[] C11; delete[] C12; delete[] C21; delete[] C22;
    delete[] B12MB22; delete[] A11PA12; delete[] A21PA22; delete[] B21MB11;
    delete[] A11PA22; delete[] B11PB22; delete[] A12MA22; delete[] B21PB22;
    delete[] A11MA21; delete[] B11PB12; delete[] P5PP4; delete[] P5PP4PP6;
    delete[] P5PP1; delete[] P5PP1MP3;
    delete[] A11; delete[] A12; delete[] A21; delete[] A22;
    delete[] B11; delete[] B12; delete[] B21; delete[] B22; 
    P1 = NULL, P2 = NULL, P3 = NULL, P4 = NULL, P5 = NULL, P6 = NULL, P7 = NULL, C11 = NULL, C12 = NULL, C21 = NULL, C22 = NULL,
    B12MB22 = NULL, A11PA12 = NULL, A21PA22 = NULL, B21MB11 = NULL,
    A11PA22 = NULL, B11PB22 = NULL, A12MA22 = NULL, B21PB22 = NULL,
    A11MA21 = NULL, B11PB12 = NULL, P5PP4 = NULL, P5PP4PP6 = NULL,
    P5PP1 = NULL, P5PP1MP3 = NULL;
    A11 = NULL, A12 = NULL, A21 = NULL, A22 = NULL;
    B11 = NULL, B12 = NULL, B21 = NULL, B22 = NULL;
    return C;
}