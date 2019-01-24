#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <cmath>
using namespace std;


void ZerarMatriz(double** matriz, int tamanho){
	for(int i = 0; i < tamanho; i++){
		for (int j = 0; j < tamanho; j ++){
			matriz[i][j] = 0;
		}
	}
}

void ZerarVetor(double* vetor, int tamanho){
	for(int i = 0; i < tamanho; i ++){
		vetor[i] = 0;
	}
}

double** CriarMatriz(double** matriz, int tamanho){
	for(int i = 0; i < tamanho; i++){
		matriz[i] = (double*) malloc (tamanho * sizeof(double));
	}
	
	ZerarMatriz(matriz, tamanho);
}

void CopiarMatriz(double** matriz1, double** matriz2, int tamanho){
  	ZerarMatriz(matriz2, tamanho);

  	for(int i = 0; i < tamanho; i++){
    	for(int j = 0; j < tamanho; j++){
      		matriz2[i][j] = matriz1[i][j];
    	} 
  	}
}

void ImprimirMatriz(double** matriz, int tamanho){
	cout<<"\n";
	
	for(int i = 0; i < tamanho; i++){
		for(int j = 0; j < tamanho; j++){
			cout << matriz[i][j] << " ";
		}
		cout<<"\n";				
	}
}

void ImprimirVetor(double vetor[], int tamanho){
	cout<<"\n";
	for(int i = 0; i < tamanho; i++){
			cout <<"\n [" << i << "]: "<< vetor[i];				
	}
	cout<<"\n";
}


void MatrizIdentidade(double** matriz, int tamanho){
	for(int i = 0; i < tamanho; i++){
		for(int j = 0; j < tamanho; j++){
			if (i == j){
				matriz[i][i] = 1;
			} else{
				matriz[i][j] = 0;
			}				
		}
	}
}


void Multiplicacao1xN(int tamanho, double** matriz, double* vetor, double* vetorResultado){ 
	double sum = 0;

	for (int row = 0; row < tamanho; row++) {  
	    for (int coluna = 0; coluna < tamanho; coluna++) {  
	        sum += matriz[row][coluna] * vetor[coluna];
	    } 
	    vetorResultado[row] = sum;  
	    sum = 0;
	}
}

void MultiplicacaoNxN(int tamanho, double** matriz, double** matriz2, double** resultado){ 
	ZerarMatriz(resultado, tamanho);

	for (int row = 0; row < tamanho; row++) { 
	    for (int col = 0; col < tamanho; col++) {
	    	resultado[row][col] = 0;  
	    	for(int i = 0; i < tamanho; i++){
	         	resultado[row][col] += (matriz[row][i] * matriz2[i][col]);
	    	}
	    } 
	}
}


void substituicoesSucessivas(double* X, double** Coeficientes, double* B, int tamanho){
    X[0] = B[0]/Coeficientes[0][0];
     
    for(int i = 1; i < tamanho; i++){
        double soma = 0;
        for(int j = 0; j < i; j++){
            soma += Coeficientes[i][j] * X[j];
        }
        X[i] = (B[i] - soma) / Coeficientes[i][i];
    }

    for(int i = 0; i < tamanho; i++){
        double aux = floorf(X[i]*1000)/1000;
        X[i] = aux;
    }
}

void substituicoesRetroativas(double* X, double** Coeficientes, double* B, int tamanho){
    X[tamanho-1] = B[tamanho-1]/Coeficientes[tamanho-1][tamanho-1];
 
    for(int i = tamanho-2; i >= 0; i--){
        double soma=0;
        for(int j = i+1; j <= tamanho-1; j++){
            soma += Coeficientes[i][j] * X[j];
        }
        X[i] = (B[i] - soma) / Coeficientes[i][i];
    }

    for(int i = 0; i < tamanho ; i++){
        double aux = floorf(X[i]*1000)/1000;
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

void Gauss(double** Coeficientes, int tamanho, double** MatrizL,  double* B, double* Pb){	
	double* matrizPermutacao[tamanho];
	CriarMatriz(matrizPermutacao, tamanho);
  	MatrizIdentidade(matrizPermutacao, tamanho);
  	
		
  	for(int i = 0; i < tamanho; i++){
    	int linha = ChoosePivoParcial(i, tamanho, Coeficientes);
    	
    	TrocarLinha(Coeficientes, tamanho, linha, i);
    	TrocarLinha(matrizPermutacao, tamanho, linha, i);
    	
    	if(i > 0){
      		TrocarLinha(MatrizL, tamanho, linha, i);
   		}

    	ZerarColuna(Coeficientes, MatrizL, tamanho, i);

	}
	double aux[tamanho];

	Multiplicacao1xN(tamanho, matrizPermutacao, B, aux);
  	
  	for(int i = 0; i < tamanho; i ++){
  		Pb[i] = aux[i];
  	}

  	for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            if (i == j){
                MatrizL[i][i] = 1;
            }
        }
    }
}

void FatoracaoLU(double** Coeficientes, double* B, double* X, int tamanho){
  	double Y[tamanho];
	double* MatrizL[tamanho], *MatrizU[tamanho];
	CriarMatriz(MatrizL, tamanho);
	CriarMatriz(MatrizU, tamanho);

	for(int i = 0; i < tamanho; i++){
	    for(int j = 0; j < tamanho; j++){
	        MatrizU[i][j] = Coeficientes[i][j];
	    }
	}
	
	double Pb[tamanho];

	Gauss(MatrizU, tamanho, MatrizL, B, Pb);
	
  	substituicoesSucessivas(Y, MatrizL, Pb, tamanho);
  
	substituicoesRetroativas(X, MatrizU, Y, tamanho);
}

/// MÉTODOS DOS ELEMENTOS FINITOS
double kii(double xj, double xi){
	double L = xj - xi;
	double M = xj + xi;
	return (-15 * L * log(M + L) + 15 * L * log(M - L) - 15 * (M) * log(M + L) + 15 * (M) * log(M - L)) / (2 * pow(L,2));
}

double kij(double xj, double xi){
	double L = xj - xi;
	double M = xj + xi;
	return (15 *(M + L) * (log(M + L) - log(M - L))) / (2 * pow(L,2));;
}

double kji(double xj, double xi){
	double L = xj - xi;
	double M = xj + xi;
	return (15 *(M - L) * (log(M + L) - log(M - L))) / (2 * pow(L,2));
}

double kjj(double xj, double xi){
	double L = xj - xi;
	double M = xj + xi;
	return (15 * L* log(M + L) - 15 * L * log(M - L) - 15 * M * log(M +L) + 15 * M*log(M - L)) / (2 * pow(L, 2));
}

double f(double xj, double xi){
	double l = xj - xi;
	return -4*l;
}

struct elemento{
	double* K[2];
	double xi;
	double xj;
	double f[2];
	int incidencia[2];
};

int main(){
	int tamanho = 7;
	elemento elementos[tamanho];
	double delta = 0.0428;
	double inicio = 0.2;
	double final = 0.5;

	for(int i = 0; i < tamanho; i ++){
		CriarMatriz(elementos[i].K, 2);
	}

	elementos[0].xi = inicio;
	elementos[0].xj = inicio + delta;
	elementos[0].incidencia[0] = -1;
	elementos[0].incidencia[1] = 0;

	elementos[1].xi = inicio + delta;
	elementos[1].xj = inicio + 2*delta;
	elementos[1].incidencia[0] = 0;
	elementos[1].incidencia[1] = 1;

	elementos[2].xi = inicio + 2*delta;
	elementos[2].xj = inicio + 3*delta;
	elementos[2].incidencia[0] = 1;
	elementos[2].incidencia[1] = 2;

	elementos[3].xi = inicio + 3*delta;
	elementos[3].xj = inicio + 4*delta;
	elementos[3].incidencia[0] = 2;
	elementos[3].incidencia[1] = 3;

	elementos[4].xi = inicio + 4*delta;
	elementos[4].xj = inicio + 5*delta;
	elementos[4].incidencia[0] = 3;
	elementos[4].incidencia[1] = 4;

	elementos[5].xi = inicio + 5*delta;
	elementos[5].xj = inicio + 6*delta;
	elementos[5].incidencia[0] = 4;
	elementos[5].incidencia[1] = 5;

	elementos[6].xi = inicio + 6*delta;
	elementos[6].xj = inicio + 0.5;
	elementos[6].incidencia[0] = 5;
	elementos[6].incidencia[1] = 6;

	// percorrer os elementos
	for(int k = 0; k < tamanho; k++){
		
		for(int i = 0; i < 2; i ++){
			for(int j = 0; j < 2; j++){
				elementos[k].K[i][i] = kii(elementos[k].xj, elementos[k].xi);
				elementos[k].K[i][j] = kij(elementos[k].xj, elementos[k].xi);
				elementos[k].K[j][i] = kji(elementos[k].xj, elementos[k].xi);
				elementos[k].K[j][j] = kjj(elementos[k].xj, elementos[k].xi);
			}
			elementos[k].f[i] = f(elementos[k].xj, elementos[k].xi);	
		}
	}


	double* A[6];
	CriarMatriz(A, 6);

	for(int i = 0; i < tamanho-1; i ++){
		for(int j = 0; j < tamanho-1; j++){
			A[i][j] = 0;
		}
	}
	
	// montagem matriz A
	int I, J;
	for(int k = 0; k < tamanho-1; k ++){
		for(int i = 0; i < 2; i ++){
			for(int j = 0; j < 2; j ++){
				I = elementos[k].incidencia[i];
				J = elementos[k].incidencia[j];
				
				if(I != -1 && j != -1){
					A[I][J] += elementos[k].K[i][j]; // parei aqui
				}
			}
		}
	}

	ImprimirMatriz(A, 6);

	double b[tamanho-1];
	// montagem vetor B
	for(int k = 0; k < tamanho - 1; k ++){
		for(int i = 0; i < 2; i ++){
				I = elementos[k].incidencia[i];

				if(I != -1){
					b[I] += elementos[k].f[i]; // parei aqui
				}
		}
	}

	ImprimirVetor(b, tamanho-1);
	double resultado[tamanho-1];

	
	FatoracaoLU(A, b, resultado, 6);
	ImprimirVetor(resultado, 6);
}


