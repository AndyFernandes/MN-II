// Andreza Fernandes de Oliveira, 384341
// ARQUIVO DE TESTE PARA TESTAR AS FUNÇÕES DESENVOLVIDAS

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define M_PI 3.14159265358979323846

using namespace std;


float f(float valor, int opc_formula) { 
	switch(opc_formula) {
		case 1:
			return sin(valor);
		case 2:
			return cos(valor);
		case 3:
			return tan(valor);
		default:
			cout << "\nErro, houve algum imprevisto com a fórmula passada.";
			return -100000;
			break;
	}

	return -100000;
}

float NewtonCodes_Aberta_Grau4_Tolerancia(float a, float b, float tolerancia, int opc_formula){
	float Ic, Ia = 0, h, xi, xf, x1, x2, x3, h_aux, fator = 0.3, erro = 10;
	int i = 0, num_particao = 1;
	
	while ( erro > tolerancia) {
		i = 0;
		h = (b + a) / num_particao;
		h_aux = (b - a)/(num_particao*6);
		xi = a + h_aux;
		Ic = 0;

		while (i < num_particao){
			x1 = xi + h_aux;
			x2 = x1 + h_aux;
			x3 = x2 + h_aux;
			xf = x3 + h_aux;
			//cout << "\nXI:" << xi << "\n X1:" << x1 << "\n X2:" << x2 <<"\n XF:"<< xf <<  "\n H_AUX:" << h_aux << "\n PARTICAO:" << i; 
			Ic += fator * h_aux * (11*f(xi, opc_formula) - 14*f(x1, opc_formula) + 26*f(x2, opc_formula) - 14*f(x3, opc_formula) + 11*f(xf, opc_formula)); 
			xi = xf + 2*h_aux;
			i ++;
		}

		erro = Ic - Ia; 
		Ia = Ic;
		num_particao += 1;
	}
	
	return Ic;
}


int main(){
	cout <<"\n" << NewtonCodes_Aberta_Grau4_Tolerancia(0, M_PI/2, 1, 2);
	return NULL;
}