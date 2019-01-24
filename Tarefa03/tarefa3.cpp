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
double kii(double L,double xj, double xi){
	double M = xj + xi;
	return (-15 * L * log(M + L) + 15 * L * log(M - L) - 15 * M * log(M + L) + 15 * M * log(M - L)) / (2.0 * pow(L,2));
}

double kij(double L,double xj, double xi){
	double M = xj + xi;
	return (15 *(M + L) * (log(M + L) - log(M - L))) / (2.0 * pow(L,2));;
}

double kji(double L, double xj, double xi){
	double M = xj + xi;
	return (15 *(M - L) * (log(M + L) - log(M - L))) / (2.0 * pow(L,2));
}

double kjj(double L, double xj, double xi){
	double M = xj + xi;
	return (15 * L* log(M + L) - 15 * L * log(M - L) - 15 * M * log(M +L) + 15 * M*log(M - L)) / (2.0 * pow(L, 2));
}

double f(double L, double xj, double xi){
	return (-8.0 * L) / 2.0;
}

struct elemento{
	double* K[2];
	double xi;
	double xj;
	int id;
	double f[2];
	int incidencia[2];
};

int main(){
	int num_particoes = 7;
	int tamanho = 6;
	int num_elementos = 7;
	elemento elementos[num_elementos];


	for(int i = 0; i < num_elementos; i ++){
		CriarMatriz(elementos[i].K, 2);
	}

	elementos[0].xi = 0.2;
	elementos[0].xj = 0.2429;
	elementos[0].incidencia[0] = -1;
	elementos[0].incidencia[1] = 0;
	elementos[0].id = 1;

	elementos[1].xi = 0.2429;
	elementos[1].xj = 0.2858;
	elementos[1].incidencia[0] = 0;
	elementos[1].incidencia[1] = 1;
	elementos[1].id = 2;

	elementos[2].xi = 0.2858;
	elementos[2].xj = 0.3287;
	elementos[2].incidencia[0] = 1;
	elementos[2].incidencia[1] = 2;
	elementos[2].id = 3;

	elementos[3].xi = 0.3287;
	elementos[3].xj = 0.3716;
	elementos[3].incidencia[0] = 2;
	elementos[3].incidencia[1] = 3;
	elementos[3].id = 4;

	elementos[4].xi = 0.3716;
	elementos[4].xj = 0.4145;
	elementos[4].incidencia[0] = 3;
	elementos[4].incidencia[1] = 4;
	elementos[4].id = 5;

	elementos[5].xi = 0.4145;
	elementos[5].xj = 0.4574;
	elementos[5].incidencia[0] = 4;
	elementos[5].incidencia[1] = 5;
	elementos[5].id = 6;

	elementos[6].xi = 0.4574;
	elementos[6].xj = 0.5;
	elementos[6].incidencia[0] = 5;
	elementos[6].incidencia[1] = -1;
	elementos[6].id = 7;
	// percorrer os elementos
	double Le =  (0.5 - 0.2)/num_particoes;
	for(int k = 0; k < num_elementos; k++){
		
		double M = elementos[k].xj + elementos[k].xi;
		elementos[k].K[0][0] = ( -15.0 * Le*log(M + Le)
                                       + 15.0 *Le*log(M - Le)
                                       - 15.0 *M*log(M +Le)
                                       + 15.0*M*log(M - Le)) / (2.0 * pow(Le,2));
		elementos[k].K[0][1] = (15.0 *(M + Le) * (log(M + Le) - log(M - Le))) / (2.0 * pow(Le,2));
		elementos[k].K[1][0] = (15.0 *(M - Le) * (log(M + Le) - log(M - Le))) / (2.0 * pow(Le,2));
		elementos[k].K[1][1] = (15.0 * Le*log(M + Le) - 15.0 *Le*log( M - Le) - 15.0 *M*log(M +Le) + 15.0*M*log(M - Le)) / (2.0 * pow(Le, 2));
			
			

		elementos[k].f[0] = f(Le, elementos[k].xj, elementos[k].xi);
		elementos[k].f[1] = f(Le, elementos[k].xj, elementos[k].xi);
				
	}

	double* A[tamanho];
	CriarMatriz(A, tamanho);

	for(int i = 0; i < tamanho; i ++){
		for(int j = 0; j < tamanho; j++){
			A[i][j] = 0;
		}
	}
	
	// montagem matriz A
	int I, J;
	for(int k = 0; k < num_particoes; k ++){
		for(int i = 0; i < 2; i ++){
			for(int j = 0; j < 2; j ++){
				I = elementos[k].incidencia[i];
				J = elementos[k].incidencia[j];
				
				if(I != -1 && J != -1){
					A[I][J] += elementos[k].K[i][j];
				}
			}
		}
	}
	
	

	double b[tamanho];
	// montagem vetor B
	for(int k = 0; k < num_particoes; k ++){
		for(int i = 0; i < 2; i ++){
				I = elementos[k].incidencia[i];

				if(I != -1){
					b[I] += elementos[k].f[i]; 
				}
		}
	}

	ImprimirVetor(b, tamanho);
	double resultado[tamanho];


  ImprimirMatriz(A, tamanho);

	FatoracaoLU(A, b, resultado, tamanho);
	resultado[0] = resultado[0];
	resultado[1] = resultado[1];
	resultado[2] = resultado[2];
	resultado[3] = resultado[3];
	resultado[4] = resultado[4];
	resultado[5] = resultado[5];


	ImprimirVetor(resultado, tamanho);
}


