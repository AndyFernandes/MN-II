#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

struct Elemento{
    int inc[2];
    int id;
    double matrizK[2][2];
    double vetorF[2];
    double vetorG[2];
};

double** AlocarMatriz(int tamanho){
    double **matrix_res = (double**)malloc(tamanho * sizeof(double*));
    for(int i=0; i < tamanho; i++){
        matrix_res[i] = (double*)malloc(sizeof(double) * tamanho);
    }
    for(int i = 0; i< tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            matrix_res[i][j] = 0;
        }
    }
    return matrix_res;
}

double* AlocarVetor(int tamanho){
    double *vetor = (double*)malloc(tamanho*sizeof(double));
    for(int i = 0; i < tamanho; i++){
        vetor[i] = 0;
    }
    return vetor;
}

Elemento* AlocarVetorElementos(int tamanho){
    Elemento *vetor = (Elemento*)malloc(tamanho*sizeof(Elemento));
    return vetor;
}

void ImprimirMatrix(double** matrix, int tamanho){
    cout<<"\n";
    for (int row = 0; row < tamanho; row++) {
        for (int col = 0; col < tamanho; col++) {
            printf( " %.3f ", matrix[row][col]);
            //cout << matrix[row][col] << " ";
        }
        cout << endl;
    }
}

void ImprimirVetor(double* vetor, int tamanho){
    cout << "\n";
    cout << "{ " ;

    for (int index = 0; index < tamanho; index++) {
        cout << vetor[index]<< endl;
    }
    cout << "}" << endl;
}

void SetarDados(Elemento * elementos, double nos[8], int tamanho, int numParticoes){

    double Le = (nos[7] - nos[0]) / numParticoes, M = 0;

    int pos_vetor_no = 0;

    for(int i = 0; i < numParticoes; i++ ){

        pos_vetor_no = elementos[i].id;
        M = nos[pos_vetor_no] + nos[pos_vetor_no -1];

        elementos[i].matrizK[0][0] = ( -15.0 * Le*log(M + Le)
                                       + 15.0 *Le*log( M - Le)
                                       - 15.0 *M*log(M +Le)
                                       + 15.0*M*log(M - Le)) / (2.0 * pow(Le,2));
        elementos[i].matrizK[0][1] = (15.0 *(M + Le) * (log(M + Le) - log(M - Le))) / (2.0 * pow(Le,2));
        elementos[i].matrizK[1][0] = (15.0 *(M - Le) * (log(M + Le) - log(M - Le))) / (2.0 * pow(Le,2));
        elementos[i].matrizK[1][1] = (15.0 * Le*log(M + Le) - 15.0 *Le*log( M - Le) - 15.0 *M*log(M +Le) + 15.0*M*log(M - Le)) / (2.0 * pow(Le, 2));
        elementos[i].vetorG[0] = 0;
        elementos[i].vetorG[1] = 0;
        elementos[i].vetorF[0] = (-8.0 * Le) / 2.0;
        elementos[i].vetorF[1] = (-8.0 * Le) / 2.0;
    }

}

double** CalcularMatrizA(Elemento* elementos, int tamanho, int numParticoes){

    double ** matrizA = AlocarMatriz(tamanho);

    int I, J;
    for(int pos = 0; pos < numParticoes; pos++){
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                I = elementos[pos].inc[i];
                J = elementos[pos].inc[j];
                if( I != -1 && J != -1){
                    matrizA[I][J] += elementos[pos].matrizK[i][j];
                }
            }
        }
    }
    return matrizA;
}

double* CalcularVetorB(Elemento * elementos, int tamanho, int numParticoes){
    double *vetorB = AlocarVetor(tamanho);
    int I;
    for(int pos = 0; pos < numParticoes; pos++){
        for(int i = 0; i < 2; i++){
            I = elementos[pos].inc[i];
            if(I != -1){
                vetorB[I] += (elementos[pos].vetorF[i]);
            }
        }
    }

    return vetorB;
}


double** MatrizIdentidade(int tamanho){
    double **matriz = AlocarMatriz(tamanho);
    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            if (i == j){
                matriz[i][i] = 1;
            }else{
                matriz[i][j] = 0;
            }
        }
    }
    return matriz;
}

//nxn e nx1
double* MultiplicacaoMatrixVetor(int tamanho, double** matriz, double* vetor){

    double *vetor_Res = AlocarVetor(tamanho);

    double sum = 0;
    for (int row = 0; row < tamanho; row++) {
        for (int coluna = 0; coluna < tamanho; coluna++) {
            sum += matriz[row][coluna] * vetor[coluna];
        }
        vetor_Res[row] = sum;
        sum = 0;
    }

    return vetor_Res;
}


void substituicoesSucessivas(double* X, double ** Coeficientes, double* B, int tamanho){
    X[0] = B[0]/Coeficientes[0][0];

    for(int i = 1; i < tamanho; i++){
        float soma = 0;
        for(int j = 0; j < i; j++){
            soma += Coeficientes[i][j] * X[j];
        }
        X[i] = (B[i] - soma) / Coeficientes[i][i];
    }

    for(int i = 0; i < tamanho; i++){
        float aux = floorf(X[i]*1000)/1000;
        X[i] = aux;
    }
}


void substituicoesRetroativas(double* X, double** Coeficientes, double* B, int tamanho){
    X[tamanho-1] = B[tamanho-1]/Coeficientes[tamanho-1][tamanho-1];

    for(int i = tamanho-2; i >= 0; i--){
        float soma=0;
        for(int j = i+1; j <= tamanho-1; j++){
            soma += Coeficientes[i][j] * X[j];
        }
        X[i] = (B[i] - soma) / Coeficientes[i][i];
    }

    for(int i = 0; i < tamanho ; i++){
        float aux = floorf(X[i]*1000)/1000;
        X[i]=aux;
    }
}


void ZerarColuna(double** Coeficientes, double** matrizL, int tamanho, int colPivo){ // colPivo eh a coluna do pivo
    int i, j;

    for (i = colPivo + 1; i < tamanho; i++) {
        double mult = (-1) * Coeficientes[i][colPivo] / Coeficientes[colPivo][colPivo];
        matrizL[i][colPivo] = Coeficientes[i][colPivo] / Coeficientes[colPivo][colPivo];
        for (j = colPivo; j < tamanho; j++) {
            Coeficientes[i][j] += mult * Coeficientes[colPivo][j];
        }
        if(Coeficientes[i][colPivo] += mult * Coeficientes[colPivo][j] < 0.01){
            Coeficientes[i][colPivo] = 0;
        }
    }
}


void DiagonalL(double **matriz, int tamanho){
    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            if (i == j){
                matriz[i][i] = 1;
            }
        }
    }
}


void TrocarLinha(double** matriz, int tamanho, int linha1, int linha2){
    double aux[1][tamanho];
    for(int k = 0; k < tamanho; k++){
        aux[0][k] = matriz[linha1][k];
        matriz[linha1][k] = matriz[linha2][k];
        matriz[linha2][k] = aux[0][k];
    }
}


double ChoosePivoParcial(int coluna, int tamanho, double** Coeficientes){
    double pivo = coluna;
    int row = 0;
    double elemento = Coeficientes[coluna][coluna];

    for (int row = coluna; row < tamanho; row++){
        if(elemento < Coeficientes[row][coluna]){
            elemento = Coeficientes[row][coluna];
            pivo = row;
        }
    }
    return pivo;
}


void Gauss(double** Coeficientes, int tamanho, double **MatrizL,  double *B, double *Pb){

    double **matrizPermutacao = MatrizIdentidade(tamanho);


    for(int i = 0; i < tamanho; i++){
        int linha = ChoosePivoParcial(i, tamanho, Coeficientes);

        TrocarLinha(Coeficientes, tamanho, linha, i);
        TrocarLinha(matrizPermutacao, tamanho, linha, i);

        if(i > 0){
            TrocarLinha(MatrizL, tamanho, linha, i);
        }

        ZerarColuna(Coeficientes, MatrizL, tamanho, i);

    }

    double *aux = MultiplicacaoMatrixVetor(tamanho, matrizPermutacao, B);

    for(int i = 0; i < tamanho; i++){
        Pb[i] = aux[i];
    }

    DiagonalL(MatrizL, tamanho);
}

double* FatoracaoLU(double** Coeficientes, double* B, int tamanho){

    double ** matrizU = AlocarMatriz(tamanho);

    double *X = AlocarVetor(tamanho);

    for(int i = 0 ; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            matrizU[i][j] = Coeficientes[i][j];
        }
    }

    double *Y = AlocarVetor(tamanho);
    double **MatrizL = AlocarMatriz(tamanho);

    double *Pb = AlocarVetor(tamanho);

    Gauss(matrizU, tamanho, MatrizL, B, Pb);

    substituicoesSucessivas(Y, MatrizL, Pb, tamanho);

    substituicoesRetroativas(X, matrizU, Y, tamanho);

    return X;

}

void ElementsMatrix(double **matrix, int tamanho, double *elementos){
    int index = 0;
    for (int row = 0; row < tamanho; row++) {
        for (int col = 0; col < tamanho; col++) {
            matrix[row][col] = elementos[index];
            index ++;
        }
    }
}


int main() {

    int tamanho = 6, numParticoes = 7, numElementos = 8;

    Elemento e1, e2, e3, e4, e5, e6, e7;

    e1.inc[0] = -1;
    e1.inc[1] = 0;
    e1.id = 1;

    e2.inc[0] = 0;
    e2.inc[1] = 1;
    e2.id = 2;

    e3.inc[0] = 1;
    e3.inc[1] = 2;
    e3.id = 3;

    e4.inc[0] = 2;
    e4.inc[1] = 3;
    e4.id = 4;

    e5.inc[0] = 3;
    e5.inc[1] = 4;
    e5.id = 5;

    e6.inc[0] = 4;
    e6.inc[1] = 5;
    e6.id = 6;

    e7.inc[0] = 5;
    e7.inc[1] = -1;
    e7.id = 7;


    Elemento* elementos = AlocarVetorElementos(numParticoes);
    elementos[0] = e1;
    elementos[1] = e2;
    elementos[2] = e3;
    elementos[3] = e4;
    elementos[4] = e5;
    elementos[5] = e6;
    elementos[6] = e7;

    double nos[numElementos] = {0.2, 0.2429, 0.2858,0.3287,0.3716, 0.4145, 0.4574, 0.5};

    SetarDados(elementos, nos, tamanho, numParticoes);

    double** matrizA =  CalcularMatrizA(elementos, tamanho, numParticoes);
    ImprimirMatrix(matrizA, tamanho);

    double* vetorB = CalcularVetorB(elementos, tamanho, numParticoes);
    ImprimirVetor(vetorB, tamanho);

    double* Y = FatoracaoLU(matrizA, vetorB, tamanho);
    ImprimirVetor(Y,tamanho);

    return 0;
}



/*int tamanho = 6;
int valor = tamanho * tamanho;
double* vetor = AlocarVetor(valor);

vetor[0] = -16557.52;
vetor[1] = 8950.52;
vetor[2] = 0.0;
vetor[3] = 0.0;
vetor[4] = 0.0;
vetor[5] = 0.0;
vetor[6] = 7607.0;
vetor[7] = -16355.85;
vetor[8] = 8748.85;
vetor[9] = 0.0;
vetor[10] = 0.0;
vetor[11] = 0.0;
vetor[12] = 0.0;
vetor[13] = 7607.0;
vetor[14] = -16206.85;
vetor[15] = 8599.0;
vetor[16] = 0.0;
vetor[17] = 0.0;
vetor[18] = 0.0;
vetor[19] = 0.0;
vetor[20] = 7607.0;
vetor[21] = -16092.2;
vetor[22] = 8485.2;
vetor[23] = 0.0;
vetor[24] = 0.0;
vetor[25] = 0.0;
vetor[26] = 0.0;
vetor[27] = 7607.0;
vetor[28] = -16001.31;
vetor[29] = 8394.31;
vetor[30] = 0.0;
vetor[31] = 0.0;
vetor[32] = 0.0;
vetor[33] = 0.0;
vetor[34] = 7607.0;
vetor[35] = -15927.0;

double** matriz2 = AlocarMatriz(tamanho);

ElementsMatrix(matriz2, tamanho, vetor);

ImprimirMatrix(matriz2, tamanho);

double *vetorB = AlocarVetor(6);
vetorB[0]= -17;
vetorB[1]= -17;
vetorB[2]= -17;
vetorB[3]= -17;
vetorB[4]= -17;
vetorB[5]= -17;

double *vetorX = FatoracaoLU(matriz2, vetorB, tamanho);

ImprimirVetor(vetorX, tamanho);*/
