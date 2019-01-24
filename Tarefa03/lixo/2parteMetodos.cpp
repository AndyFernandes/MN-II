#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <cmath>
using namespace std;


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

void transposta(double** matriz, double** resultado, int tamanho){
	ZerarMatriz(resultado, tamanho);
	for(int i = 0; i < tamanho; i++){
		for(int j = 0; j < tamanho; j++){
			resultado[i][j] = matriz[j][i];
		}
	}
}

double norma(double* vetor, int tamanho){
	double acc = 0;
	for (int i = 0; i < tamanho; i++){
		acc += vetor[i]*vetor[i];
	}
	return sqrt(acc);
}

void normalizar(double* vetor, int tamanho, double* q){
	ZerarVetor(q, tamanho);
	double norm = norma(vetor, tamanho);
	
	for(int i = 0; i < tamanho; i ++){
		q[i] = vetor[i] / norm;
	}
}

void MultiplicacaoEscalar(double** matriz, double** resultado, int tamanho, double valor){
	ZerarMatriz(resultado, tamanho);
	for(int i = 0; i < tamanho; i++){
		for(int j = 0; j < tamanho; j++){
			resultado[i][j] = matriz[i][j] * valor;
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

double multiplicacaoTranspostoVetor(int tamanho, double* vetor1, double* vetor2){ // o resultao é um flutuante
	double result = 0;

	for(int i = 0; i < tamanho; i++){
		result += vetor1[i] * vetor2[i];
	}

	return result;
}

void MultiplicacaoVetorTransposto(int tamanho, double* vetor1, double* vetor2, double** resultado){
	ZerarMatriz(resultado, tamanho);

	for(int i = 0; i < tamanho; i++){
		for(int j = 0; j < tamanho; j++){
			resultado[i][j] = vetor1[i] * vetor2[j];
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


void calcularInversa(double** matriz, int tamanho, double** inversa){
	double x[tamanho], b[tamanho];
	double* identidade[tamanho];
	CriarMatriz(identidade, tamanho);
	MatrizIdentidade(identidade, tamanho);

	for(int i = 0; i < tamanho; i ++){
		for(int j = 0; j < tamanho; j++){
			b[j] = identidade[j][i];
		}

		FatoracaoLU(matriz, b, x, tamanho);

		for(int k = 0; k < tamanho; k++){
			inversa[k][i] = x[k];
		}
	}
}

double metodoPotenciaRegular(double** Coeficientes, double* x0, double erro, int tamanho){
	double autovalor = 0, autovalorcorrente = 0;
	double errocorrente;
	double q[tamanho];
	normalizar(x0, tamanho, q);

	Multiplicacao1xN(tamanho, Coeficientes, q, x0);

	ImprimirMatriz(Coeficientes, tamanho);

	do{
		normalizar(x0, tamanho, q);
		Multiplicacao1xN(tamanho, Coeficientes, q, x0);
		autovalorcorrente = multiplicacaoTranspostoVetor(tamanho, q, x0); 
		errocorrente = (autovalorcorrente - autovalor)/ autovalorcorrente;
		autovalor = autovalorcorrente;

	} while(errocorrente > erro);

	for(int i = 0; i < tamanho; i ++){
		x0[i] = q[i];
	}
	return autovalor;
} // OKK

double metodoPotenciaInversa(double** Coeficientes, double* x0, double erro, int tamanho){
	double* inversa[tamanho];
	double autovalor;
	CriarMatriz(inversa, tamanho);

	calcularInversa(Coeficientes, tamanho, inversa);

	autovalor = metodoPotenciaRegular(inversa, x0, erro, tamanho);
	return 1/autovalor;
}

double metodoPotenciaDeslocamento(double** Coeficientes, double* x0, double erro, double valor, int tamanho){
	double* Abarra[tamanho];
	CriarMatriz(Abarra, tamanho);

	for(int i = 0; i < tamanho; i++){
		for(int j = 0; j < tamanho; j++){
			if (i == j){
				Abarra[i][j] = Coeficientes[i][i] - valor;
			} else{
				Abarra[i][j] = Coeficientes[i][j];	
			}
			
		}
	}

	double autovalor = metodoPotenciaInversa(Abarra, x0, erro, tamanho);
	autovalor = autovalor + valor;

	return autovalor; 
}

void construirHH(double** Coeficientes, int j, int tamanho, double** Hj){
	double P[tamanho], Plinha[tamanho], N[tamanho], Nnormalizado[tamanho];
	ZerarVetor(P, tamanho);
	ZerarVetor(Plinha, tamanho);
	ZerarVetor(N, tamanho);

	for(int i = j+1; i < tamanho; i++){
		P[i] = Coeficientes[i][j];
	}

	double normma = norma(P, tamanho);

	if(P[j+1] > 0){
        Plinha[j+1] = -1*normma;
	} else {
        Plinha[j+1] = normma;
    }

	for(int i = 0; i < tamanho; i++){
		N[i] = P[i] - Plinha[i];
	}

	normalizar(N, tamanho, Nnormalizado);
	
	double* matrizNNT[tamanho], *auxiliar[tamanho];
	CriarMatriz(matrizNNT, tamanho);
	ZerarMatriz(matrizNNT, tamanho);
	CriarMatriz(auxiliar, tamanho);
	ZerarMatriz(auxiliar, tamanho);

	MultiplicacaoVetorTransposto(tamanho, Nnormalizado, Nnormalizado, matrizNNT);
	
	MultiplicacaoEscalar(matrizNNT, auxiliar, tamanho, 2);

	for(int i = 0; i < tamanho; i++){
		for(int k = 0; k < tamanho; k++){
			Hj[i][k] = Hj[i][k] - auxiliar[i][k];
		}
	}
}

void metodoHH(double** Coeficientes, int tamanho, double** H, double** Tridiagonal){
	double* Hj[tamanho];
	CriarMatriz(Hj, tamanho);

	double* Aanterior[tamanho]; //matriz do passo anterior
	CriarMatriz(Aanterior,tamanho);
	CopiarMatriz(Coeficientes, Aanterior, tamanho);

	double* Acorrente[tamanho]; // matriz do proximo passo
	CriarMatriz(Acorrente, tamanho);

	double* produto[tamanho];
	CriarMatriz(produto,tamanho);

	for(int i = 0; i < tamanho-2; i++){
		
		ZerarMatriz(produto, tamanho);

		MatrizIdentidade(Hj, tamanho);
		construirHH(Aanterior, i, tamanho, Hj);
		MultiplicacaoNxN(tamanho, Aanterior, Hj, produto);

		
		MultiplicacaoNxN(tamanho, Hj, produto, Acorrente);
		
		ZerarMatriz(produto, tamanho);

		MultiplicacaoNxN(tamanho, H, Hj, produto);
		
		CopiarMatriz(produto, H, tamanho);
		CopiarMatriz(Acorrente, Aanterior, tamanho);
	}

	CopiarMatriz(Acorrente, Tridiagonal, tamanho);
}

void construirJ(double** A, int j, int tamanho, double** J){
	MatrizIdentidade(J, tamanho);

	double teta = atan(A[j+1][j]/ A[j][j]);

	J[j][j] = cos(teta);
	J[j+1][j] = -1*sin(teta);
	J[j][j+1] = sin(teta);
	J[j+1][j+1] = cos(teta);
}

void decomposicaoQR(double** A, double** Qt, double** R, int tamanho){
	double* J[tamanho]; // to criando para passar para o construirJ
	CriarMatriz(J,  tamanho);
	MatrizIdentidade(Qt, tamanho);

	double* Acorrente[tamanho]; // vai ser o A0
	CriarMatriz(Acorrente, tamanho);
	CopiarMatriz(A, Acorrente, tamanho);

	double* produto[tamanho];
	CriarMatriz(produto, tamanho);

	for(int j = 0; j < tamanho - 1; j ++){
		
		ZerarMatriz(produto, tamanho);

		construirJ(Acorrente, j, tamanho, J);

		MultiplicacaoNxN(tamanho, J, Acorrente, produto);
		CopiarMatriz(produto, Acorrente, tamanho);

		MultiplicacaoNxN(tamanho, J, Qt, produto);
		CopiarMatriz(produto, Qt, tamanho); 

	}
	
	ZerarMatriz(produto, tamanho);

	transposta(Qt, produto, tamanho);
	CopiarMatriz(produto, Qt, tamanho);
	CopiarMatriz(Acorrente, R, tamanho);
	ImprimirMatriz(Qt, tamanho);
}

void metodoQR(double** Coeficientes, int tamanho, double erro, double* autovalores, double** X){
	double* Q[tamanho];
	CriarMatriz(Q,  tamanho);
	
	double* R[tamanho];
	CriarMatriz(R,  tamanho);
	
	double* A[tamanho];
	CriarMatriz(A,  tamanho);
	MatrizIdentidade(A, tamanho);

	MatrizIdentidade(X, tamanho);
	metodoHH(Coeficientes, tamanho, X, A);

	double* produto[tamanho];
	CriarMatriz(produto, tamanho);

	double norma = 0;
	int i = 0;
	
	do{
		//ZerarMatriz(produto, tamanho);

		decomposicaoQR(A, Q, R, tamanho);
		cout << "\nQ:";
		ImprimirMatriz(Q, tamanho);

		cout << "\nR:";
		ImprimirMatriz(R, tamanho);

		cout << "\nX:";
		ImprimirMatriz(X, tamanho);
		MultiplicacaoNxN(tamanho, R, Q, A);
		MultiplicacaoNxN(tamanho, X, Q, produto);
		
		CopiarMatriz(produto, X, tamanho);
		
		for(int i = 0; i < tamanho; i ++){
			for(int j = 0; j < tamanho; j++){
				if(i != j){
					norma += A[i][j] * A[i][j];	
				}
				
				
			}
		}
		
		norma = sqrt(norma);
		cout << "NORMA:" << norma;
		i ++;
	} while(i < 50);

	for(int i = 0; i < tamanho; i ++){
		autovalores[i] = A[i][i];
	}
	ImprimirMatriz(A, tamanho);
	CopiarMatriz(produto, X, tamanho);

}
int main(){
  	int tamanho = 3;
	double* coeficientes[tamanho], *copia[tamanho], x0[tamanho];
	double *HouseHolder[tamanho], *Tridiagonal[tamanho];
	double autovalores[tamanho], *autovetores[tamanho];
	CriarMatriz(autovetores, tamanho);

	CriarMatriz(coeficientes, tamanho);
	CriarMatriz(copia, tamanho);
	CriarMatriz(HouseHolder, tamanho);
	CriarMatriz(Tridiagonal, tamanho);
	MatrizIdentidade(HouseHolder, tamanho);

	coeficientes[0][0] = 31;
	coeficientes[0][1] = 5;
	coeficientes[0][2] = 2;

	coeficientes[1][0] = 5;
	coeficientes[1][1] = 22;
	coeficientes[1][2] = 4;

	coeficientes[2][0] = 2;
	coeficientes[2][1] = 4;
	coeficientes[2][2] = 55;

	x0[0] = 1;
  	x0[1] = 1;
  	x0[2] = 1;

  	metodoQR(coeficientes, tamanho, 0.001, autovalores, autovetores);
  	ImprimirVetor(autovalores, tamanho);
  	ImprimirMatriz(autovetores, tamanho);
  	// cout << "METODO HOUSE HOLDER:";
  	// metodoHH(coeficientes, tamanho, HouseHolder, Tridiagonal);
  	// cout << "TRIDIAGONAL::::::";
  	// ImprimirMatriz(Tridiagonal, tamanho);
  	// cout << "HouseHolder::::::";
  	// ImprimirMatriz(HouseHolder, tamanho);

	//  cout << "Potência com Deslocamento:\n";
 	//  double autovalor = metodoPotenciaDeslocamento(coeficientes, x0, 0.00001, 30, tamanho);
	// cout << "AUTOVALOR: " << autovalor;
	// cout << "AUTOVETOR:";
	// ImprimirVetor(x0, tamanho);

	return 0;
}