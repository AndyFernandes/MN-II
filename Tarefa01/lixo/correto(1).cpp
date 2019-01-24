// Andreza Fernandes de Oliveira, 384341
// ARQUIVO CORRETO
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define M_PI 3.14159265358979323846

using namespace std;

// OBSERVAÇÃO: VERIFICAR CORRETUDO DE TODAS ELAS, APÓS PRONTAS. COMPARAR RESULTADOS COM A ARINA, E NEXT
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////   FUNÇÕES AUXILIARES   //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
		OBSERVAÇÕES:		- Conforme o menu: 	1. sin(x)	2. cos(x)	3. tan(x)

*/

// Função para o cálculo do valor da função no ponto x
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////   FÓRMULAS DE INTEGRAÇÃO   ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////   TRAPÉZIO   ///////////////////////////////////////////////////////////

float NewtonCodes_Fechada_Trapezio_Particao(float a, float b, int num_particao, int opc_formula) {
	float Ic = 0, h, xi, xf;
	int i = 0;
	
	h = (a + b) / num_particao;
	xi = a;
	xf = a + h;

	while (i < num_particao) {
		Ic += ( (xf - xi) / 2 ) * ( f(xi, opc_formula) + f(xf, opc_formula) );
		xi = xf;
		xf += h;
		i ++;	
	}
	
	return Ic;
}

// Ia = Integra anterior | Ic = Integral acumulativa | xi = X inicial do intervalo | xf = X final do intervalo | h = distância entre xi e xf
float NewtonCodes_Fechada_Trapezio_Tolerancia(float a, float b, float tolerancia, int opc_formula) {	
	float Ic, Ia, h, xi, xf, erro;
	int i = 0, num_particao = 1;
	
	xi = a;
	xf = b;
	erro = 10;
	
	while ( erro > tolerancia) {
		i = 0;
		h = (a + b) / num_particao;
		xi = a;
		xf = xi + h;
		Ic = 0;
		while ( i < num_particao ) {
			Ic += ( (xf - xi) / 2 ) * ( f(xi, opc_formula) + f(xf, opc_formula) );
			xi = xf;
			xf += h;
			i ++;	
		}

		erro = Ic - Ia; // vê se é assim
		Ia = Ic;
		num_particao += 1;
	}

	return Ic;
}

float NewtonCodes_Aberta_Trapezio_Particao(float a, float b, int num_particao, int opc_formula){
	float Ic = 0, h, xi, xf, x1, x2, h_aux;
	int i = 0;
	
	h = (b + a) / num_particao;
	h_aux = (a + b) / (num_particao*3); 
	xi = a + h_aux;

	while (i < num_particao) {
		xf = xi + h_aux;
		Ic += ( h / 2 ) * ( f(xi, opc_formula) + f(xf, opc_formula) );
		//cout << "\n Xi:" << xi << "\n Xf:" << xf << "\n Ic:" << Ic << "\n Particao" << i;
		xi = xf + 2*h_aux;
		i ++;	
	}
	
	return Ic;	
}


float NewtonCodes_Aberta_Trapezio_Tolerancia(float a, float b, float tolerancia, int opc_formula) {	
	float Ic, Ia = 0, h, xi, xf, x1, x2, h_aux, erro = 10;
	int i = 0, num_particao = 1;

	
	while ( erro > tolerancia) {
		i = 0;
		h = (a + b) / num_particao;
		h_aux = (b - a) / (num_particao*3); 
		xi = a + h_aux;
		Ic = 0;

		while ( i < num_particao ) {
			xf = xi + h_aux;
			Ic += ( h / 2 ) * ( f(xi, opc_formula) + f(xf, opc_formula) );
			cout << "\n Xi:" << xi << "\n Xf:" << xf << "\n Ic:" << Ic << "\n Particao" << num_particao;
			xi = xf + 2*h_aux;
			i ++;	
		}

		erro = Ic - Ia;
		Ia = Ic;
		num_particao += 1;
	}

	return Ic;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////   NEWTON - GRAU 2   /////////////////////////////////////////////////////

float NewtonCodes_Fechada_Grau2_Particao(float a, float b, int num_particao, int opc_formula){
	float Ic = 0, h, xi, xf, x1, h_aux;
	int i = 0;
	
	h = (b + a) / num_particao;
	xi = a;
	
	while (i < num_particao){
		xf = xi + h;
		h_aux = (xf - xi)/2;
		x1 = xi + h_aux;
		//cout << "XI:" << xi <<"\n XF:"<< xf << "\n X1:" << x1 << "\n H_AUX:" << h_aux << "\n PARTICAO:" << num_particao; 
		Ic += (h_aux/3) * (f(xi, opc_formula) + 4*f(x1, opc_formula) + f(xf, opc_formula)); 
		xi = xf;
		i ++;
	}
	
	return Ic;
}

float NewtonCodes_Fechada_Grau2_Tolerancia(float a, float b, float tolerancia, int opc_formula){
	float Ic, Ia = 0, h, xi, xf, x1, h_aux, erro = 10;
	int i = 0, num_particao = 1;
	
	while ( erro > tolerancia) {
		i = 0;
		h = (a + b) / num_particao;
		xi = a;
		Ic = 0;
		while (i < num_particao){
			xf = xi + h;
			h_aux = (xf - xi)/2;
			x1 = xi + h_aux;
			//cout << "XI:" << xi <<"\n XF:"<< xf << "\n X1:" << x1 << "\n H_AUX:" << h_aux << "\n PARTICAO:" << num_particao; 
			Ic += (h_aux/3) * (f(xi, opc_formula) + 4*f(x1, opc_formula) + f(xf, opc_formula)); 
			xi = xf;
			i ++;
	}

		erro = Ic - Ia; 
		Ia = Ic;
		num_particao += 1;
	}
	
	return Ic;
}

float NewtonCodes_Aberta_Grau2_Particao(float a, float b, int num_particao, int opc_formula){ // tá bugando algo aqui
	float Ic = 0, h, xi, xf, x1, h_aux, fator = 1.3333333;
	int i = 0;
	
	h_aux = (b - a)/(num_particao*4);
	xi = a + h_aux;

	while (i < num_particao){
		xf = xi + 2*h_aux;
		x1 = xi + h_aux;
		cout << "\nXI:" << xi <<"\n XF:"<< xf << "\n X1:" << x1 << "\n PARTICAO:" << i << "\n"; 
		Ic += (h_aux * fator * (2*f(xi, opc_formula) - f(x1, opc_formula) + 2*f(xf, opc_formula))); 
		xi = xf + 2*h_aux;
		i ++;
	}
	
	return Ic;
}

float NewtonCodes_Aberta_Grau2_Tolerancia(float a, float b, float tolerancia, int opc_formula){
	float Ic, Ia = 0, h, xi, xf, x1, h_aux, erro = 10, fator = 1.3333333;
	int i = 0, num_particao = 1;
	
	while ( erro > tolerancia) {
		i = 0;
		h_aux = (b - a)/(num_particao*4);
		xi = a + h_aux;
		Ic = 0;
		while (i < num_particao){
			xf = xi + 2*h_aux;
			x1 = xi + h_aux;
			cout << "\nXI:" << xi <<"\n XF:"<< xf << "\n X1:" << x1 << "\n PARTICAO:" << num_particao << "\n"; 
			Ic += (h_aux * fator * (2*f(xi, opc_formula) - f(x1, opc_formula) + 2*f(xf, opc_formula))); 
			xi = xf + 2*h_aux;
			i ++;
	}

		erro = Ic - Ia; 
		Ia = Ic;
		num_particao += 1;
	}
	
	return Ic;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////   NEWTON - GRAU 3   /////////////////////////////////////////////////////

float NewtonCodes_Fechada_Grau3_Particao(float a, float b, int num_particao, int opc_formula){
	float Ic = 0, h, xi, xf, x1, x2, h_aux, fator = 0.375;
	int i = 0;
	
	h = (b + a) / num_particao;
	xi = a;

	while (i < num_particao){
		xf = xi + h;
		h_aux = (xf - xi)/3;
		x1 = xi + h_aux;
		x2 = xi + 2*h_aux;
		//cout << "\nXI:" << xi << "\n X1:" << x1 << "\n X2:" << x2 <<"\n XF:"<< xf <<  "\n H_AUX:" << h_aux << "\n PARTICAO:" << i; 
		Ic += fator * h_aux * (f(xi, opc_formula) + 3*f(x1, opc_formula) + 3*f(x2, opc_formula) + f(xf, opc_formula)); 
		xi = xf;
		i ++;
		
	}
	
	return Ic;
}

float NewtonCodes_Fechada_Grau3_Tolerancia(float a, float b, float tolerancia, int opc_formula){
	float Ic, Ia = 0, h, xi, xf, x1, x2, h_aux, fator = 0.375, erro = 10;
	int i = 0, num_particao = 1;
	
	while ( erro > tolerancia) {
		i = 0;
		h = (a + b) / num_particao;
		xi = a;
		Ic = 0;

		while (i < num_particao){
			xf = xi + h;
			h_aux = (xf - xi)/3;
			x1 = xi + h_aux;
			x2 = xi + 2*h_aux;
			//cout << "XI:" << xi <<"\n XF:"<< xf << "\n X1:" << x1 << "\n H_AUX:" << h_aux << "\n PARTICAO:" << num_particao; 
			Ic += fator * h_aux * (f(xi, opc_formula) + 3*f(x1, opc_formula) + 3*f(x2, opc_formula) + f(xf, opc_formula));
			xi = xf;
			i ++;
		}

		erro = Ic - Ia; 
		Ia = Ic;
		num_particao += 1;
	}
	
	return Ic;
}

float NewtonCodes_Aberta_Grau3_Particao(float a, float b, int num_particao, int opc_formula){
	float Ic = 0, h, xi, xf, x1, x2, h_aux, fator = 0.20833333;
	int i = 0;
	
	h = (b + a) / num_particao;
	h_aux = (b - a)/(num_particao*5);
	xi = a + h_aux;

	while (i < num_particao){
		x1 = xi + h_aux;
		x2 = x1 + h_aux;
		xf = x2 + h_aux;
		//cout << "\nXI:" << xi << "\n X1:" << x1 << "\n X2:" << x2 <<"\n XF:"<< xf <<  "\n H_AUX:" << h_aux << "\n PARTICAO:" << i; 
		Ic += fator * h_aux * (11*f(xi, opc_formula) + f(x1, opc_formula) + f(x2, opc_formula) + 11*f(xf, opc_formula)); 
		xi = xf + 2*h_aux;
		i ++;
		
	}
	
	return Ic;
}

float NewtonCodes_Aberta_Grau3_Tolerancia(float a, float b, float tolerancia, int opc_formula){
	float Ic, Ia = 0, h, xi, xf, x1, x2, h_aux, fator = 0.20833333, erro = 10;
	int i = 0, num_particao = 1;
	
	while ( erro > tolerancia) {
		i = 0;
		Ic = 0;
		h = (a + b) / num_particao;
		h_aux = (b - a)/(num_particao*5);
		xi = a + h_aux;

		while (i < num_particao){
			x1 = xi + h_aux;
			x2 = x1 + h_aux;
			xf = x2 + h_aux;
			//cout << "\nXI:" << xi << "\n X1:" << x1 << "\n X2:" << x2 <<"\n XF:"<< xf <<  "\n H_AUX:" << h_aux << "\n PARTICAO:" << i; 
			Ic += fator * h_aux * (11*f(xi, opc_formula) + f(x1, opc_formula) + f(x2, opc_formula) + 11*f(xf, opc_formula)); 
			xi = xf + 2*h_aux;
			i ++;
		}

		erro = Ic - Ia; 
		Ia = Ic;
		num_particao += 1;
	}
	
	return Ic;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////   NEWTON - GRAU 4   /////////////////////////////////////////////////////

float NewtonCodes_Fechada_Grau4_Particao(float a, float b, int num_particao, int opc_formula){
	float Ic = 0, h, xi, xf, x1, x2, x3, h_aux, fator = 0.0444444;
	int i = 0;
	
	h = (b + a) / num_particao;
	xi = a;

	while (i < num_particao){
		xf = xi + h;
		h_aux = (xf - xi)/4;
		x1 = xi + h_aux;
		x2 = xi + 2*h_aux;
		x3 = xi + 3*h_aux;
		//cout << "\nXI:" << xi << "\n X1:" << x1 << "\n X2:" << x2 <<"\n XF:"<< xf <<  "\n H_AUX:" << h_aux << "\n PARTICAO:" << i; 
		Ic += fator * h_aux * (7*f(xi, opc_formula) + 32*f(x1, opc_formula) + 12*f(x2, opc_formula) + 32*f(x3, opc_formula) + 7*f(xf, opc_formula)); 
		xi = xf;
		i ++;
		
	}
	
	return Ic;
}

float NewtonCodes_Fechada_Grau4_Tolerancia(float a, float b, float tolerancia, int opc_formula){
	float Ic, Ia = 0, h, xi, xf, x1, x2, x3, h_aux, fator = 0.0444444, erro = 10;
	int i = 0, num_particao = 1;
	
	while ( erro > tolerancia) {
		i = 0;
		h = (a + b) / num_particao;
		xi = a;
		Ic = 0;

		while (i < num_particao){
			xf = xi + h;
			h_aux = (xf - xi)/4;
			x1 = xi + h_aux;
			x2 = xi + 2*h_aux;
			x3 = xi + 3*h_aux;
			//cout << "\nXI:" << xi << "\n X1:" << x1 << "\n X2:" << x2 <<"\n XF:"<< xf <<  "\n H_AUX:" << h_aux << "\n PARTICAO:" << i; 
			Ic += fator * h_aux * (7*f(xi, opc_formula) + 32*f(x1, opc_formula) + 12*f(x2, opc_formula) + 32*f(x3, opc_formula) + 7*f(xf, opc_formula)); 
			xi = xf;
			i ++;
		}
		
		erro = Ic - Ia; 
		Ia = Ic;
		num_particao += 1;
	}
	
	return Ic;
}

float NewtonCodes_Aberta_Grau4_Particao(float a, float b, int num_particao, int opc_formula){
	float Ic = 0, h, xi, xf, x1, x2, x3, h_aux, fator = 0.3;
	int i = 0;
	
	h = (b + a) / num_particao;
	h_aux = (b - a)/(num_particao*6);
	xi = a + h_aux;

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
	
	return Ic;
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
