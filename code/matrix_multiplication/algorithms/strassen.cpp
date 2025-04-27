#include <vector>

/*
    La implementación de este algoritmo se basa
    en el pseudocódigo del mismo visto en el
    PPT 5 Parte 2 del ramo de INF-221, semestre 2025-1
*/

std::vector<std::vector<int>> strassen(std::vector<std::vector<int>> &M1, std::vector<std::vector<int>> &M2) {
    std::vector<std::vector<int>> res;
    if (M1.size() == 1 && M2.size() == 1) {
        res = std::vector<std::vector<int>>(1);
        res[0] = std::vector<int>(1);
        res[0][0] = M1[0][0]*M2[0][0];
        return res;
    }

    int n = M1.size();
    res = std::vector<std::vector<int>>(n);
    for (int i=0;i<n;i++) {
        res[i] = std::vector<int>(n);
    }

    //XpY = suma de vector X con Y
    //XmY = resta de vector X con Y
    std::vector<std::vector<int>> A(n/2), B(n/2),
    C(n/2), D(n/2), E(n/2), F(n/2), G(n/2), H(n/2),
    FmH(n/2), ApB(n/2), CpD(n/2), GmE(n/2), ApD(n/2),
    EpH(n/2), BmD(n/2), GpH(n/2), AmC(n/2), EpF(n/2),
    P1, P2, P3, P4, P5, P6, P7;

    //Inicialización de las subdivisiones de matrices
    for (int i=0;i<n;i++) {
        A[i] = std::vector<int>(n/2);
        B[i] = std::vector<int>(n/2);
        C[i] = std::vector<int>(n/2);
        D[i] = std::vector<int>(n/2);
        E[i] = std::vector<int>(n/2);
        F[i] = std::vector<int>(n/2);
        G[i] = std::vector<int>(n/2);
        H[i] = std::vector<int>(n/2);
    }

    //Construcción de las submatrices
    for (int i=0;i<(n/2);i++) {
        for (int j=0;j<(n/2);j++) {
            A[i][j] = M1[i][j];
            B[i][j] = M1[i][j+(n/2)];
            C[i][j] = M1[i+(n/2)][j];
            D[i][j] = M1[i+(n/2)][j+(n/2)];
            F[i][j] = M2[i][j];
            F[i][j] = M2[i][j+(n/2)];
            G[i][j] = M2[i+(n/2)][j];
            H[i][j] = M2[i+(n/2)][j+(n/2)];
            FmH[i][j] = F[i][j]-H[i][j];
            ApB[i][j] = A[i][j]+B[i][j];
            CpD[i][j] = C[i][j]+D[i][j];
            GmE[i][j] = G[i][j]-E[i][j];
            ApD[i][j] = A[i][j]+D[i][j];
            EpH[i][j] = E[i][j]+H[i][j];
            BmD[i][j] = B[i][j]+D[i][j];
            GpH[i][j] = G[i][j]+H[i][j];
            AmC[i][j] = A[i][j]-C[i][j];
            EpF[i][j] = E[i][j]+F[i][j];
        }
    }

    P1 = strassen(A, FmH);
    P2 = strassen(ApB, H);
    P3 = strassen(CpD, E);
    P4 = strassen(D, GmE);
    P5 = strassen(ApD, EpH);
    P6 = strassen(BmD, GpH);
    P7 = strassen(AmC, EpF);

    for (int i=0;i<(n/2);i++) {
        for (int j=0;j<(n/2);j++) {
            res[i][j] = P5[i][j]+P4[i][j]+P6[i][j]-P2[i][j];
            res[i][j+(n/2)] = P1[i][j]+P2[i][j];
            res[i+(n/2)][j] = P3[i][j]+P4[i][j];
            res[i+(n/2)][j+(n/2)] = P1[i][j]+P5[i][j]-P3[i][j]-P7[i][j];
        }
    }
    return res;
    
}