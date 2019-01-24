// Andreza Fernandes de Oliveira, 384341
// ARQUIVO CORRETO
/* TAREFA 01 - QUESTÃO 04*/
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
		OBSERVAÇÕES:		- Conforme o menu: 	1 = sin(x)	
												2 = cos(x)	
												3 = tan(x)


*/

float f(float valor, int opc_formula) { 
	switch(opc_formula) {
		case 1:
			return sin(valor);
		case 2:
			return cos(valor);
		case 3:
			return tan(valor);
		default:
			cout << "\nERRO, HOUVE ALGUM IMPREVISTO COM A FORMULA PASSADA.";
			return -100000;
			break;
	}

	return -100000;
}

float x(float a, float b, float alfa){
	return ((a+b)/2) + alfa*((b-a)/2);
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////   FÓRMULAS DE NEWTON   ///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*

		OBSERVAÇÕES:
							- VARIÁVEIS: 		- H = Distância entre b e a, no caso quando há partições fica (b + a)/num_particoes. Famoso DeltaX
												- H_AUX = Distância entre cada ponto
												- ERRO = Padronizei como 10
												- FATOR = Refere-se as frações que antecedem o h nas fórmulas fechadas de integração.
												- XI = X inicial
												- XF = X final
												- OPC_FORMULA = Se trata da fórmula inicialmente que se deseja integrar
												- A = limite inferior
												- B = limite superior
												- IC = Integral Acumulativa (no caso ela é soma das fatias integradas)
												- IA = Integral Anterior
*/

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

		erro = Ic - Ia; 
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


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////   FÓRMULAS DE GAUSS   ///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////   GAUSS - LEGENDRE  2 PONTOS   //////////////////////////////////////////////////

float GaussLegendre_2Pontos_Particao(float a, float b, int opc_formula, int num_particao){
	float w = 1, alfa[2], Ic = 0, I = 0, xi, xf, h;
	int j = 0;

	alfa[1] = 0.5773502691;
	alfa[0] = -1 * alfa[1];
	
	h = (b - a)/num_particao;
	xi = a;
	
	while(j < num_particao){
		Ic = 0;
		xf = xi + h;
		
		for(int i = 0; i < 2; i++){
			Ic += w * f(x(xi, xf, alfa[i]), opc_formula);
		}
		
		Ic = Ic * (h/2);
		I += Ic; 
		xi = xf;
		j++;
		
	}

	return  I;
}

float GaussLegendre_2Pontos_Tolerancia(float a, float b, int opc_formula, float tolerancia){
	float w = 1, alfa[2], Ic, I, Ia = 0.0, xi, xf, h, erro = 10.00;
	int j = 0, num_particao = 1;

	alfa[1] = 0.5773502691;
	alfa[0] = -1 * alfa[1];

	while (erro > tolerancia){
		I = 0;
		Ic = 0;
		j = 0;
		h = (b - a)/num_particao;
		xi = a;
		
		while(j < num_particao){
			Ic = 0;
			xf = xi + h;
		
			for(int i = 0; i < 2; i++){
				Ic += w * f(x(xi, xf, alfa[i]), opc_formula);
			}
		
			Ic = Ic * (h/2);
			I += Ic; 
			xi = xf;
			j++;
		
		}
		
		erro = I - Ia;
		Ia = I;
		num_particao += 1;

	}

	return  I;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////   GAUSS - LEGENDRE  3 PONTOS   //////////////////////////////////////////////////

float GaussLegendre_3Pontos_Particao(float a, float b, int opc_formula, int num_particao){
	float w[3], alfa[3], Ic = 0, I = 0, xi, xf, h;
	int j = 0;

	alfa[2] = 0.7745966692;
	alfa[1] = 0;
	alfa[0] = -1 * alfa[2];
	
	w[0] = 0.5555555555;
	w[1] = 	0.8888888888;
	w[2] = w[0];

	h = (b - a)/num_particao;
	xi = a;

	while(j < num_particao){
		Ic = 0;
		xf = xi + h;
		
		for(int i = 0; i < 3; i++){
			Ic += w[i] * f(x(xi, xf, alfa[i]), opc_formula);
		}
		
		Ic = Ic * (h/2);
		I += Ic; 
		xi = xf;
		j++;
		
	}	

	return I;
}

float GaussLegendre_3Pontos_Tolerancia(float a, float b, int opc_formula, float tolerancia){
	float w[3], alfa[3], Ic, I, Ia = 0.0, xi, xf, h, erro = 10.00;
	int j = 0, num_particao = 1;

	alfa[2] = 0.7745966692;
	alfa[1] = 0;
	alfa[0] = -1 * alfa[2];
	
	w[0] = 0.5555555555;
	w[1] = 	0.8888888888;
	w[2] = w[0];

	while (erro > tolerancia){
		I = 0;
		Ic = 0;
		j = 0;
		h = (b - a)/num_particao;
		xi = a;
		
		while(j < num_particao){
			Ic = 0;
			xf = xi + h;
		
			for(int i = 0; i < 3; i++){
				Ic += w[i] * f(x(xi, xf, alfa[i]), opc_formula);
			}
			
			Ic = Ic * (h/2);
			I += Ic; 
			xi = xf;
			j++;
		
			}
		
		erro = I - Ia;
		Ia = I;
		num_particao += 1;

	}

	return  I;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////   GAUSS - LEGENDRE 4 PONTOS   //////////////////////////////////////////////////

float GaussLegendre_4Pontos_Particao(float a, float b, int opc_formula, int num_particao){
	float w[4], alfa[4], Ic = 0, I = 0, xi, xf, h;
	int j = 0;

	alfa[3] = 0.8611363115;
	alfa[2] = 0.3399810435;
	alfa[1] = -1 * alfa[2];
	alfa[0] = -1 * alfa[3];
	
	w[0] = 0.3478548451;
	w[1] = 0.6521451548;
	w[2] = w[1];
	w[3] = w[0];

	h = (b - a)/num_particao;
	xi = a;

	while(j < num_particao){
		Ic = 0;
		xf = xi + h;

		for(int i = 0; i < 4; i++){
			Ic += w[i] * f(x(xi, xf, alfa[i]), opc_formula);
		}
		
		Ic = Ic * (h/2);
		I += Ic; 
		xi = xf;
		j++;
	}

	return I;
}

float GaussLegendre_4Pontos_Tolerancia(float a, float b, int opc_formula, float tolerancia){
	float w[4], alfa[4], Ic, I, Ia = 0.0, xi, xf, h, erro = 10.00;
	int j = 0, num_particao = 1;

	alfa[3] = 0.8611363115;
	alfa[2] = 0.3399810435;
	alfa[1] = -1 * alfa[2];
	alfa[0] = -1 * alfa[3];
	
	w[0] = 0.3478548451;
	w[1] = 0.6521451548;
	w[2] = w[1];
	w[3] = w[0];


	while (erro > tolerancia){
		I = 0;
		Ic = 0;
		j = 0;
		h = (b - a)/num_particao;
		xi = a;
		
		while(j < num_particao){
			Ic = 0;
			xf = xi + h;
		
			for(int i = 0; i < 4; i++){
				Ic += w[i] * f(x(xi, xf, alfa[i]), opc_formula);
			}
			
			Ic = Ic * (h/2);
			I += Ic; 
			xi = xf;
			j++;
		
			}
		
		erro = I - Ia;
		Ia = I;
		num_particao += 1;

	}

	return  I;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////   GAUSS - LEGENDRE  5 PONTOS   //////////////////////////////////////////////////

float GaussLegendre_5Pontos_Particao(float a, float b, int opc_formula, int num_particao){
	float w[5], alfa[5], Ic = 0, I = 0, xi, xf, h;
	int j = 0;

	alfa[4] = 0.9061798459;
	alfa[3] = 0.5384693101;
	alfa[2] = 0;
	alfa[1] = -1 * alfa[3];
	alfa[0] = -1 * alfa[4];
	
	w[0] = 0.2369268850;
	w[1] = 0.4786286704;
	w[2] = 0.5688888888;
	w[3] = w[1];
	w[4] = w[0];

	h = (b - a)/num_particao;
	xi = a;

	while(j < num_particao){
		Ic = 0;
		xf = xi + h;

		for(int i = 0; i < 5; i++){
			Ic += w[i] * f(x(xi, xf, alfa[i]), opc_formula);
		}
		
		Ic = Ic * (h/2);
		I += Ic; 
		xi = xf;
		j++;
	}

	return I;
}

float GaussLegendre_5Pontos_Tolerancia(float a, float b, int opc_formula, float tolerancia){
	float w[5], alfa[5], Ic, I, Ia = 0.0, xi, xf, h, erro = 10.00;
	int j = 0, num_particao = 1;

	alfa[4] = 0.9061798459;
	alfa[3] = 0.5384693101;
	alfa[2] = 0;
	alfa[1] = -1 * alfa[3];
	alfa[0] = -1 * alfa[4];
	
	w[0] = 0.2369268850;
	w[1] = 0.4786286704;
	w[2] = 0.5688888888;
	w[3] = w[1];
	w[4] = w[0];


	while (erro > tolerancia){
		I = 0;
		Ic = 0;
		j = 0;
		h = (b - a)/num_particao;
		xi = a;
		
		while(j < num_particao){
			Ic = 0;
			xf = xi + h;
		
			for(int i = 0; i < 5; i++){
				Ic += w[i] * f(x(xi, xf, alfa[i]), opc_formula);
			}
			
			Ic = Ic * (h/2);
			I += Ic; 
			xi = xf;
			j++;
		
			}
		
		erro = I - Ia;
		Ia = I;
		num_particao += 1;

	}

	return  I;
}

int main(){
	int opc_formulaInt,  opc_funcao, opc_xMin, opc_xMax, opc_particao, num_particao, grau;
	float a, b, tolerancia;	

	do{
		cout << "\n\n###################################################################";
		cout << "\n###################################################################";
		cout << "\n###################################################################";

		cout << "\n\nESCOLHA A FORMULA:";
		cout << "\n\n1 - SIN(X)";
		cout << "\n2 - COS(X)";
		cout << "\n3 - TAN(X)";
		cout << "\n0 - SAIR";

		cin >> opc_funcao;
	
		switch(opc_funcao){
			case 1:
				opc_funcao = 1;
				break;
			case 2:
				opc_funcao = 2;
				break;
			case 3:
				opc_funcao = 3;
				break;
			case 0:
				break;
			default:
				cout << "\n\nOPCAO INVALIDA! TENTE NOVAMENTE.";
				opc_funcao = -1;
				break;
		}
	} while(opc_funcao == -1 && opc_funcao != 0);
	
	//clear
	do{
		cout << "\n\n###################################################################";
		cout << "\n###################################################################";
		cout << "\n###################################################################";

		cout << "\n\nESCOLHA A FORMA DE PARTICAO:";
		cout << "\n\n1 - TOLERANCIA";
		cout << "\n2 - NUMERO DEFINIDO DE PARTICOES";
		cout << "\n0 - SAIR";

		cin >> opc_particao;
	
		switch(opc_particao){
			case 1:
				//clear
				cout << "\n\n###################################################################";
				cout << "\n###################################################################";
				cout << "\n###################################################################";

				cout << "\n\nDIGITE A TOLERANCIA:";
				cin >> tolerancia;

				break;
			case 2:
				//clear
				cout << "\n\n###################################################################";
				cout << "\n###################################################################";
				cout << "\n###################################################################";

				cout << "\n\nDIGITE O NUMERO DE PARTICOES:";
				cin >> num_particao;

				break;
			case 0:
				break;
			default:
				cout << "\n\nOPCAO INVALIDA! TENTE NOVAMENTE.";
				opc_particao = -1;
				break;
		}
	} while(opc_particao == -1 && opc_particao != 0);

	//clear
	do{
		cout << "\n\n###################################################################";
		cout << "\n###################################################################";
		cout << "\n###################################################################";

		cout << "\n\nESCOLHA O X_MINIMO:";
		cout << "\n\n1 - 0";
		cout << "\n2 - r/2";
		cout << "\n3 - r/4";
		cout << "\n4 - r/8";
		cout << "\n5 - OUTRO";
		cout << "\n0 - SAIR";
	
		cin >> opc_xMin;
		
		switch(opc_xMin){
			case 1:
				a = 0.;
				break;
			case 2:
				a = M_PI/  2;
				break;
			case 3:
				a = M_PI / 4;
				break;
			case 4:
				a = M_PI / 8;
				break;
			case 5:
				cout << "\n\nDIGITE O VALOR:";
				cin >> a;
				break;
			case 0:
				break;
			default:
				cout << "\n\nOPCAO INVALIDA! TENTE NOVAMENTE.";
				opc_xMin = -1;
				break;
		}
	} while (opc_xMin == -1 && opc_xMin != 0);

	//clear
	do{
		cout << "\n\n###################################################################";
		cout << "\n###################################################################";
		cout << "\n###################################################################";	

		cout << "\n\nESCOLHA O X_MAXIMO:";
		cout << "\n\n1 - 0";
		cout << "\n2 - r/2";
		cout << "\n3 - r/4";
		cout << "\n4 - r/8";
		cout << "\n5 - OUTRO";
		cout << "\n0 - SAIR";
	
		cin >> opc_xMax;

		switch(opc_xMax){
			case 1:
				b = 0.;
				break;
			case 2:
				b = M_PI / 2;
				break;
			case 3:
				b = M_PI / 4;
				break;
			case 4:
				b = M_PI / 8;
				break;
			case 5:
				cout << "\n\nDIGITE O VALOR:";
				cin >> b;
				break;
			case 0:
				break;
			default:
				cout << "\n\nOPCAO INVALIDA! TENTE NOVAMENTE.";
				opc_xMax = -1;
				break;
		}
	} while (opc_xMax == -1 && opc_xMax != 0);

	//clear
	do{
		cout << "\n\n###################################################################";
		cout << "\n###################################################################";
		cout << "\n###################################################################";

		cout << "\n\nESCOLHA A FORMULA DE INTEGRACAO:";
		cout << "\n\n1 - NEWTON-CODES GRAU 1 - 4 FÓRMULA FECHADA";
		cout << "\n2 - NEWTON-CODES GRAU 1 - 4 FÓRMULA ABERTA";
		cout << "\n3 - GAUSS-LEGENDRE 2 - 5 PONTOS";
		cout << "\n0 - SAIR";
	
		cin >> opc_formulaInt;
	
		switch(opc_formulaInt){
			case 1:	
				//clear
				do{
					cout << "\n\n###################################################################";
					cout << "\n###################################################################";
					cout << "\n###################################################################";

					cout << "\n\nESCOLHA O GRAU:";
					cout << "\n\n1 - GRAU 1";
					cout << "\n2 - GRAU 2";
					cout << "\n3 - GRAU 3";
					cout << "\n4 - GRAU 4";
					cout << "\n0 - SAIR";
					cin >> grau;
			
					switch(grau){
					case 1:
						if (opc_particao == 1){
							cout << "\n\nINTEGRAL = " << NewtonCodes_Fechada_Trapezio_Tolerancia(a, b, num_particao, opc_funcao);
						} else{
							cout << "\n\nINTEGRAL = " << NewtonCodes_Fechada_Trapezio_Particao(a, b, num_particao, opc_funcao);
						}
						break;
					case 2:
						if (opc_particao == 1){
							cout << "\n\nINTEGRAL = " << NewtonCodes_Fechada_Grau2_Tolerancia(a, b, tolerancia, opc_funcao);
						} else {
							cout << "\n\nINTEGRAL = " << NewtonCodes_Fechada_Grau2_Particao(a, b, num_particao, opc_funcao);
						}
						break;
					case 3:
						if (opc_particao == 1){
							cout << "\n\nINTEGRAL = " << NewtonCodes_Fechada_Grau3_Tolerancia(a, b, tolerancia, opc_funcao);
						} else {
							cout << "\n\nINTEGRAL = " << NewtonCodes_Fechada_Grau3_Particao(a, b, num_particao, opc_funcao);
						}
						break;
					case 4:
						if (opc_particao == 1){
							cout << "\n\nINTEGRAL = " << NewtonCodes_Fechada_Grau4_Tolerancia(a, b, tolerancia, opc_funcao);
						} else {
							cout << "\n\nINTEGRAL = " << NewtonCodes_Fechada_Grau4_Particao(a, b, num_particao, opc_funcao);
						}
						break;
					case 0:
						break;
					default:
						cout << "\n\nOPCAO INVALIDA! TENTE NOVAMENTE..";
						grau = -1;
						break;
					}
				} while (grau == -1 && grau != 0);
			break;

			case 2:
			//clear
				do{
					cout << "\n\n###################################################################";
					cout << "\n###################################################################";
					cout << "\n###################################################################";

					cout << "\n\nESCOLHA O GRAU:";
					cout << "\n\n1 - GRAU 1";
					cout << "\n2 - GRAU 2";
					cout << "\n3 - GRAU 3";
					cout << "\n4 - GRAU 4";
					cout << "\n0 - SAIR";
					cin >> grau;
				
					switch(grau){
						case 1:
							if (opc_particao == 1){
								cout << "\n\nINTEGRAL = " << NewtonCodes_Aberta_Trapezio_Tolerancia(a, b, tolerancia, opc_funcao);
							} else {
								cout << "\n\nINTEGRAL = " << NewtonCodes_Aberta_Trapezio_Particao(a, b, num_particao, opc_funcao);
							}
							break;
						case 2:
							if (opc_particao == 1){
								cout << "\n\nINTEGRAL = " << NewtonCodes_Aberta_Grau2_Tolerancia(a, b, tolerancia, opc_funcao);
							} else {
								cout << "\n\nINTEGRAL = " << NewtonCodes_Aberta_Grau2_Particao(a, b, num_particao, opc_funcao);
							}
							break;
						case 3:
							if (opc_particao == 1){
								cout << "\n\nINTEGRAL = " << NewtonCodes_Aberta_Grau3_Tolerancia(a, b, tolerancia, opc_funcao);
							} else {
								cout << "\n\nINTEGRAL = " << NewtonCodes_Aberta_Grau3_Particao(a, b, num_particao, opc_funcao);
							}							
							break;
						case 4:
							if (opc_particao == 1){
								cout << "\n\nINTEGRAL = " << NewtonCodes_Aberta_Grau4_Tolerancia(a, b, tolerancia, opc_funcao);
							} else {
								cout << "\n\nINTEGRAL = " << NewtonCodes_Aberta_Grau4_Particao(a, b, num_particao, opc_funcao);
							}						
							break;
						case 0:
							break;
						default:
							cout << "\n\nOPCAO INVALIDA! TENTE NOVAMENTE.";
							grau = -1;
							break;
						}
				} while (grau == -1 && grau != 0 );
				break;

			case 3:
			//clear
				do{
					cout << "\n###################################################################";
					cout << "\n###################################################################";
					cout << "\n###################################################################";

					cout << "\n\nESCOLHA O NUMERO DE PONTOS:";
					cout << "\n\n2 - 2 PONTOS";
					cout << "\n3 - 3 PONTOS";
					cout << "\n4 - 4 PONTOS";
					cout << "\n5 - 5 PONTOS";
					cout << "\n0 - SAIR";
					cin >> grau;
			
					switch(grau){
						case 2:
							if (opc_particao == 1){
								cout << "\n\nINTEGRAL = " << GaussLegendre_2Pontos_Tolerancia(a, b, opc_funcao, tolerancia);
							} else {
								cout << "\n\nINTEGRAL = " << GaussLegendre_2Pontos_Particao(a, b, opc_funcao, num_particao);
							}		
							break;
						case 3:
							if (opc_particao == 1){
								cout << "\n\nINTEGRAL = " << GaussLegendre_3Pontos_Tolerancia(a, b, opc_funcao, tolerancia);
							} else {
								cout << "\n\nINTEGRAL = " << GaussLegendre_3Pontos_Particao(a, b, opc_funcao, num_particao);
							}
							break;
						case 4:
							if (opc_particao == 1){
								cout << "\n\nINTEGRAL = " << GaussLegendre_4Pontos_Tolerancia(a, b,  opc_funcao, tolerancia);
							} else {
								cout << "\n\nINTEGRAL = " << GaussLegendre_4Pontos_Particao(a, b, opc_funcao, num_particao);
							}
							break;
						case 5:
							if (opc_particao == 1){
								cout << "\n\nINTEGRAL = " << GaussLegendre_5Pontos_Tolerancia(a, b, opc_funcao, tolerancia);
							} else {
								cout << "\n\nINTEGRAL = " << GaussLegendre_5Pontos_Particao(a, b, opc_funcao, num_particao);
							}
							break;
						case 0:
							break;
						default:
							cout << "\n\nOPCAO INVALIDA! TENTE NOVAMENTE.";
							grau = -1;
							break;
					}
				} while (grau == -1 && grau != 0 );
				break;
		case 0:
			break;
		default:
			cout << "\n\nOPCAO INVALIDA! TENTE NOVAMENTE.";
			opc_formulaInt = -1;
			break;
		}
	} while (opc_formulaInt == -1 && opc_formulaInt != 0);
}
