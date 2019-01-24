// Andreza Fernandes de Oliveira, 384341
// ARQUIVO CORRETO
/* TAREFA 01 - QUESTÃO 03*/
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
			cout << "\nERRO, HOUVE ALGUM IMPREVISTO COM A FORMULA PASSADA.";
			return -100000;
			break;
	}

	return -100000;
}

float x(float a, float b, float alfa){
	return ((a+b)/2) + alfa*((b-a)/2);
}

float x_Exp_Simples(float a, float b, float alfa){
	return ((a+b)/2) + tanh(alfa)*((b-a)/2);
}

float x_Exp_Dupla(float a, float b, float alfa){
	return ((a+b)/2) + tanh((M_PI/2)*sinh(alfa))*((b-a)/2);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////   TRAPÉZIO   ///////////////////////////////////////////////////////////
float NewtonCodes_Fechada_Trapezio_Particao(float c_min, float c_max, float a, float b, int num_particao, int opc_formula, int tipo) {
	float Ic = 0, h, xi, xf;
	int i = 0;
	
	h = (c_min + c_max) / num_particao;
	xi = c_min;
	xf = xi + h;

	while (i < num_particao) {
		if (tipo == 1){
			Ic +=  ( (xf - xi)/ 2) * ( f(x_Exp_Simples(a, b, xi), opc_formula)*(((b-a)/2)*(1/cosh(xi))) + f(x_Exp_Simples(a, b, xf), opc_formula)*(((b-a)/2)*(1/cosh(xf))));
		} else {
			Ic = ( (xf - xi)/ 2) * ( f(x_Exp_Dupla(a, b, xi), opc_formula)*((M_PI*(b-a))/4)*(cosh(xi)/(cosh((M_PI/2)*sinh(xi))*cosh((M_PI/2)*sinh(xi)))) + f(x_Exp_Dupla(a, b, xf), opc_formula)*((M_PI*(b-a))/4)*(cosh(xf)/(cosh((M_PI/2)*sinh(xf))*cosh((M_PI/2)*sinh(xf)))));
		} 
		xi = xf;
		xf += h;
		i ++;	
	}
	
	return Ic;
}

// Ia = Integra anterior | Ic = Integral acumulativa | xi = X inicial do intervalo | xf = X final do intervalo | h = distância entre xi e xf
float NewtonCodes_Fechada_Trapezio_Tolerancia(float c_min, float c_max, float a, float b, float tolerancia, int opc_formula, int tipo) {	
	float Ic, Ia, h, xi, xf, erro;
	int i = 0, num_particao = 1;
	
	erro = 10;
	
	while ( erro > tolerancia) {
		i = 0;
		h = (c_min + c_max) / num_particao;
		xi = c_min;
		xf = xi + h;
		Ic = 0;
		while ( i < num_particao ) {
			if (tipo == 1){
				Ic += ( (xf - xi) / 2 ) * ( f(x_Exp_Simples(a, b, xi), opc_formula)*(((b-a)/2)*(1/cosh(xi))) + f(x_Exp_Simples(a, b, xf), opc_formula)*(((b-a)/2)*(1/cosh(xf))) );
			} else {
				Ic = ( (xf - xi)/ 2) * ( f(x_Exp_Dupla(a, b, xi), opc_formula)*((M_PI*(b-a))/4)*(cosh(xi)/(cosh((M_PI/2)*sinh(xi))*cosh((M_PI/2)*sinh(xi)))) + f(x_Exp_Dupla(a, b, xf), opc_formula)*((M_PI*(b-a))/4)*(cosh(xf)/(cosh((M_PI/2)*sinh(xf))*cosh((M_PI/2)*sinh(xf)))));
			}
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

float NewtonCodes_Aberta_Trapezio_Particao(float c_min, float c_max, float a, float b, int num_particao, int opc_formula, int tipo){
	float Ic = 0, h, xi, xf, x1, x2, h_aux;
	int i = 0;
	
	h = (c_min + c_max) / num_particao;
	h_aux = (c_min + c_max) / (num_particao*3); 
	xi = c_min + h_aux;

	while (i < num_particao) {
		xf = xi + h_aux;
		if (tipo == 1){
			Ic += ( h / 2 ) * ( f(x_Exp_Simples(a, b, xi), opc_formula)*(((b-a)/2)*(1/cosh(xi))) + f(x_Exp_Simples(a, b, xf), opc_formula)*(((b-a)/2)*(1/cosh(xf))) );
		} else {
			Ic += ( h / 2 ) * ( f(x_Exp_Dupla(a, b, xi), opc_formula)*((M_PI*(b-a))/4)*(cosh(xi)/(cosh((M_PI/2)*sinh(xi))*cosh((M_PI/2)*sinh(xi)))) + f(x_Exp_Dupla(a, b, xf), opc_formula)*((M_PI*(b-a))/4)*(cosh(xf)/(cosh((M_PI/2)*sinh(xf))*cosh((M_PI/2)*sinh(xf)))));
		}

		xi = xf + 2*h_aux;
		i ++;	
	}
	
	return Ic;	
}


float NewtonCodes_Aberta_Trapezio_Tolerancia(float c_min, float c_max, float a, float b, float tolerancia, int opc_formula, int tipo) {	
	float Ic, Ia = 0, h, xi, xf, x1, x2, h_aux, erro = 10;
	int i = 0, num_particao = 1;

	
	while ( erro > tolerancia) {
		i = 0;
		h = (c_min + c_max) / num_particao;
		h_aux = (c_max - c_min) / (num_particao*3); 
		xi = c_min + h_aux;
		Ic = 0;

		while ( i < num_particao ) {
			xf = xi + h_aux;
			if (tipo == 1){
				Ic += ( h / 2 ) * ( f(x_Exp_Simples(a, b, xi), opc_formula)*(((b-a)/2)*(1/cosh(xi))) + f(x_Exp_Simples(a, b, xf), opc_formula)*(((b-a)/2)*(1/cosh(xf))) );
			} else{
				Ic += ( h / 2 ) * ( f(x_Exp_Dupla(a, b, xi), opc_formula)*((M_PI*(b-a))/4)*(cosh(xi)/(cosh((M_PI/2)*sinh(xi))*cosh((M_PI/2)*sinh(xi)))) + f(x_Exp_Dupla(a, b, xf), opc_formula)*((M_PI*(b-a))/4)*(cosh(xf)/(cosh((M_PI/2)*sinh(xf))*cosh((M_PI/2)*sinh(xf)))));
			}
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

float NewtonCodes_Fechada_Grau2_Particao(float c_min, float c_max, float a, float b, int num_particao, int opc_formula, int tipo){
	float Ic = 0, h, xi, xf, x1, h_aux;
	int i = 0;
	
	h = (c_max + c_min) / num_particao;
	xi = c_min;
	
	while (i < num_particao){
		xf = xi + h;
		h_aux = (xf - xi)/2;
		x1 = xi + h_aux;
		if (tipo == 1){
			Ic += (h_aux/3) * (f(x_Exp_Simples(a, b, xi), opc_formula)*(((b-a)/2)*(1/cosh(xi))) + 4*f(x_Exp_Simples(a, b, x1), opc_formula)*(((b-a)/2)*(1/cosh(x1))) + f(x_Exp_Simples(a, b, xf), opc_formula)*(((b-a)/2)*(1/cosh(xf)))); 
		} else {			
			Ic += (h_aux/3) * (f(x_Exp_Dupla(a, b, xi), opc_formula)*((M_PI*(b-a))/4)*(cosh(xi)/(cosh((M_PI/2)*sinh(xi))*cosh((M_PI/2)*sinh(xi)))) + 4*f(x_Exp_Dupla(a, b, x1), opc_formula)*((M_PI*(b-a))/4)*(cosh(x1)/(cosh((M_PI/2)*sinh(x1))*cosh((M_PI/2)*sinh(x1)))) + f(x_Exp_Simples(a, b, xf), opc_formula)*((M_PI*(b-a))/4)*(cosh(xf)/(cosh((M_PI/2)*sinh(xf))*cosh((M_PI/2)*sinh(xf))))); 
		}
		xi = xf;
		i ++;
	}
	
	return Ic;
}

float NewtonCodes_Fechada_Grau2_Tolerancia(float c_min, float c_max, float a, float b, float tolerancia, int opc_formula, int tipo){
	float Ic, Ia = 0, h, xi, xf, x1, h_aux, erro = 10;
	int i = 0, num_particao = 1;
	
	while ( erro > tolerancia) {
		i = 0;
		h = (c_min + c_max) / num_particao;
		xi = c_min;
		Ic = 0;
		while (i < num_particao){
			xf = xi + h;
			h_aux = (xf - xi)/2;
			x1 = xi + h_aux;
			if (tipo == 1){
				Ic += (h_aux/3) * (f(x_Exp_Simples(a, b, xi), opc_formula)*(((b-a)/2)*(1/cosh(xi))) + 4*f(x_Exp_Simples(a, b, x1), opc_formula)*(((b-a)/2)*(1/cosh(x1))) + f(x_Exp_Simples(a, b, xf), opc_formula)*(((b-a)/2)*(1/cosh(xf)))); 
			} else {
				Ic += (h_aux/3) * (f(x_Exp_Dupla(a, b, xi), opc_formula)*((M_PI*(b-a))/4)*(cosh(xi)/(cosh((M_PI/2)*sinh(xi))*cosh((M_PI/2)*sinh(xi)))) + 4*f(x_Exp_Dupla(a, b, x1), opc_formula)*((M_PI*(b-a))/4)*(cosh(x1)/(cosh((M_PI/2)*sinh(x1))*cosh((M_PI/2)*sinh(x1)))) + f(x_Exp_Simples(a, b, xf), opc_formula)*((M_PI*(b-a))/4)*(cosh(xf)/(cosh((M_PI/2)*sinh(xf))*cosh((M_PI/2)*sinh(xf))))); 
			}
			xi = xf;
			i ++;
	}

		erro = Ic - Ia; 
		Ia = Ic;
		num_particao += 1;
	}
	
	return Ic;
}

float NewtonCodes_Aberta_Grau2_Particao(float c_min, float c_max, float a, float b, int num_particao, int opc_formula, int tipo){ // tá bugando algo aqui
	float Ic = 0, h, xi, xf, x1, h_aux, fator = 1.3333333;
	int i = 0;
	
	h_aux = (c_max - c_min)/(num_particao*4);
	xi = c_min + h_aux;

	while (i < num_particao){
		xf = xi + 2*h_aux;
		x1 = xi + h_aux;
		if (tipo == 1){
			Ic += (h_aux * fator * (2*f(x_Exp_Simples(a, b, xi), opc_formula)*(((b-a)/2)*(1/cosh(xi))) - f(x_Exp_Simples(a, b, x1), opc_formula)*(((b-a)/2)*(1/cosh(x1))) + 2*f(x_Exp_Simples(a, b, xf), opc_formula)*(((b-a)/2)*(1/cosh(xf))))); 
		} else {
			Ic += (h_aux * fator * (2*f(x_Exp_Dupla(a, b, xi), opc_formula)*((M_PI*(b-a))/4)*(cosh(xi)/(cosh((M_PI/2)*sinh(xi))*cosh((M_PI/2)*sinh(xi)))) - f(x_Exp_Dupla(a, b, x1), opc_formula)*((M_PI*(b-a))/4)*(cosh(x1)/(cosh((M_PI/2)*sinh(x1))*cosh((M_PI/2)*sinh(x1)))) + 2*f(x_Exp_Dupla(a, b, xf), opc_formula)*((M_PI*(b-a))/4)*(cosh(xf)/(cosh((M_PI/2)*sinh(xf))*cosh((M_PI/2)*sinh(xf)))))); 
		}
		xi = xf + 2*h_aux;
		i ++;
	}
	
	return Ic;
}

float NewtonCodes_Aberta_Grau2_Tolerancia(float c_min, float c_max, float a, float b, float tolerancia, int opc_formula, int tipo){
	float Ic, Ia = 0, h, xi, xf, x1, h_aux, erro = 10, fator = 1.3333333;
	int i = 0, num_particao = 1;
	
	while ( erro > tolerancia) {
		i = 0;
		h_aux = (c_max - c_min)/(num_particao*4);
		xi = c_min + h_aux;
		Ic = 0;
		while (i < num_particao){
			xf = xi + 2*h_aux;
			x1 = xi + h_aux;
			if (tipo == 1){
				Ic += (h_aux * fator * (2*f(x_Exp_Simples(a, b, xi), opc_formula)*(((b-a)/2)*(1/cosh(xi))) - f(x_Exp_Simples(a, b, x1), opc_formula)*(((b-a)/2)*(1/cosh(x1))) + 2*f(x_Exp_Simples(a, b, xf), opc_formula)*(((b-a)/2)*(1/cosh(xf))))); 
			} else {
				Ic += (h_aux * fator * (2*f(x_Exp_Dupla(a, b, xi), opc_formula)*((M_PI*(b-a))/4)*(cosh(xi)/(cosh((M_PI/2)*sinh(xi))*cosh((M_PI/2)*sinh(xi)))) - f(x_Exp_Dupla(a, b, x1), opc_formula)*((M_PI*(b-a))/4)*(cosh(x1)/(cosh((M_PI/2)*sinh(x1))*cosh((M_PI/2)*sinh(x1)))) + 2*f(x_Exp_Dupla(a, b, xf), opc_formula)*((M_PI*(b-a))/4)*(cosh(xf)/(cosh((M_PI/2)*sinh(xf))*cosh((M_PI/2)*sinh(xf)))))); 
			}
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

float NewtonCodes_Fechada_Grau3_Particao(float c_min, float c_max, float a, float b, int num_particao, int opc_formula, int tipo){
	float Ic = 0, h, xi, xf, x1, x2, h_aux, fator = 0.375;
	int i = 0;
	
	h = (c_min + c_max) / num_particao;
	xi = c_min;

	while (i < num_particao){
		xf = xi + h;
		h_aux = (xf - xi)/3;
		x1 = xi + h_aux;
		x2 = xi + 2*h_aux;
		if (tipo == 1){
			Ic += fator * h_aux * (f(x_Exp_Simples(a, b, xi), opc_formula)*(((b-a)/2)*(1/cosh(xi))) + 3*f(x_Exp_Simples(a, b, x1), opc_formula)*(((b-a)/2)*(1/cosh(x1))) + 3*f(x_Exp_Simples(a, b, x2), opc_formula)*(((b-a)/2)*(1/cosh(x2))) + f(x_Exp_Simples(a, b, xf), opc_formula)*(((b-a)/2)*(1/cosh(xf)))); 
		} else {
			Ic += fator * h_aux * (f(x_Exp_Dupla(a, b, xi), opc_formula)*((M_PI*(b-a))/4)*(cosh(xi)/(cosh((M_PI/2)*sinh(xi))*cosh((M_PI/2)*sinh(xi)))) + 3*f(x_Exp_Dupla(a, b, x1), opc_formula)*((M_PI*(b-a))/4)*(cosh(x1)/(cosh((M_PI/2)*sinh(x1))*cosh((M_PI/2)*sinh(x1)))) + 3*f(x_Exp_Dupla(a, b, x2), opc_formula)*((M_PI*(b-a))/4)*(cosh(x2)/(cosh((M_PI/2)*sinh(x2))*cosh((M_PI/2)*sinh(x2)))) + f(x_Exp_Dupla(a, b, xf), opc_formula)*((M_PI*(b-a))/4)*(cosh(xf)/(cosh((M_PI/2)*sinh(xf))*cosh((M_PI/2)*sinh(xf))))); 
		}
		xi = xf;
		i ++;
		
	}
	
	return Ic;
}

float NewtonCodes_Fechada_Grau3_Tolerancia(float c_min, float c_max, float a, float b, float tolerancia, int opc_formula, int tipo){
	float Ic, Ia = 0, h, xi, xf, x1, x2, h_aux, fator = 0.375, erro = 10;
	int i = 0, num_particao = 1;
	
	while ( erro > tolerancia) {
		i = 0;
		h = (c_min + c_max) / num_particao;
		xi = c_min;
		Ic = 0;

		while (i < num_particao){
			xf = xi + h;
			h_aux = (xf - xi)/3;
			x1 = xi + h_aux;
			x2 = xi + 2*h_aux;
			if (tipo == 1){
				Ic += fator * h_aux * (f(x_Exp_Simples(a, b, xi), opc_formula)*(((b-a)/2)*(1/cosh(xi))) + 3*f(x_Exp_Simples(a, b, x1), opc_formula)*(((b-a)/2)*(1/cosh(x1))) + 3*f(x_Exp_Simples(a, b, x2), opc_formula)*(((b-a)/2)*(1/cosh(x2))) + f(x_Exp_Simples(a, b, xf), opc_formula)*(((b-a)/2)*(1/cosh(xf)))); 
			} else {
				Ic += fator * h_aux * (f(x_Exp_Dupla(a, b, xi), opc_formula)*((M_PI*(b-a))/4)*(cosh(xi)/(cosh((M_PI/2)*sinh(xi))*cosh((M_PI/2)*sinh(xi)))) + 3*f(x_Exp_Dupla(a, b, x1), opc_formula)*((M_PI*(b-a))/4)*(cosh(x1)/(cosh((M_PI/2)*sinh(x1))*cosh((M_PI/2)*sinh(x1)))) + 3*f(x_Exp_Dupla(a, b, x2), opc_formula)*((M_PI*(b-a))/4)*(cosh(x2)/(cosh((M_PI/2)*sinh(x2))*cosh((M_PI/2)*sinh(x2)))) + f(x_Exp_Dupla(a, b, xf), opc_formula)*((M_PI*(b-a))/4)*(cosh(xf)/(cosh((M_PI/2)*sinh(xf))*cosh((M_PI/2)*sinh(xf)))));			
			}
			
			xi = xf;
			i ++;
		}

		erro = Ic - Ia; 
		Ia = Ic;
		num_particao += 1;
	}
	
	return Ic;
}

float NewtonCodes_Aberta_Grau3_Particao(float c_min, float c_max, float a, float b, int num_particao, int opc_formula, int tipo){
	float Ic = 0, h, xi, xf, x1, x2, h_aux, fator = 0.20833333;
	int i = 0;
	
	h = (c_max + c_min) / num_particao;
	h_aux = (c_max - c_min)/(num_particao*5);
	xi = c_min + h_aux;

	while (i < num_particao){
		x1 = xi + h_aux;
		x2 = x1 + h_aux;
		xf = x2 + h_aux;
		if (tipo == 1){
			Ic += fator * h_aux * (11*f(x_Exp_Simples(a, b, xi), opc_formula)*(((b-a)/2)*(1/cosh(xi))) + f(x_Exp_Simples(a, b, x1), opc_formula)*(((b-a)/2)*(1/cosh(x1))) + f(x_Exp_Simples(a, b, x2), opc_formula)*(((b-a)/2)*(1/cosh(x2))) + 11*f(x_Exp_Simples(a, b, xf), opc_formula)*(((b-a)/2)*(1/cosh(xf)))); 
		} else {
			Ic += fator * h_aux * (11*f(x_Exp_Dupla(a, b, xi), opc_formula)*((M_PI*(b-a))/4)*(cosh(xi)/(cosh((M_PI/2)*sinh(xi))*cosh((M_PI/2)*sinh(xi)))) + f(x_Exp_Dupla(a, b, x1), opc_formula)*((M_PI*(b-a))/4)*(cosh(x1)/(cosh((M_PI/2)*sinh(x1))*cosh((M_PI/2)*sinh(x1)))) + f(x_Exp_Dupla(a, b, x2), opc_formula)*((M_PI*(b-a))/4)*(cosh(x2)/(cosh((M_PI/2)*sinh(x2))*cosh((M_PI/2)*sinh(x2)))) + 11*f(x_Exp_Dupla(a, b, xf), opc_formula)*((M_PI*(b-a))/4)*(cosh(xf)/(cosh((M_PI/2)*sinh(xf))*cosh((M_PI/2)*sinh(xf)))));
		}
		xi = xf + 2*h_aux;
		i ++;
		
	}
	
	return Ic;
}

float NewtonCodes_Aberta_Grau3_Tolerancia(float c_min, float c_max, float a, float b, float tolerancia, int opc_formula, int tipo){
	float Ic, Ia = 0, h, xi, xf, x1, x2, h_aux, fator = 0.20833333, erro = 10;
	int i = 0, num_particao = 1;
	
	while ( erro > tolerancia) {
		i = 0;
		Ic = 0;
		h = (c_max + c_min) / num_particao;
		h_aux = (c_max - c_min)/(num_particao*5);
		xi = c_min + h_aux;

		while (i < num_particao){
			x1 = xi + h_aux;
			x2 = x1 + h_aux;
			xf = x2 + h_aux;
			if (tipo == 1){
				Ic += fator * h_aux * (11*f(x_Exp_Simples(a, b, xi), opc_formula)*(((b-a)/2)*(1/cosh(xi))) + f(x_Exp_Simples(a, b, x1), opc_formula)*(((b-a)/2)*(1/cosh(x1))) + f(x_Exp_Simples(a, b, x2), opc_formula)*(((b-a)/2)*(1/cosh(x2))) + 11*f(x_Exp_Simples(a, b, xf), opc_formula)*(((b-a)/2)*(1/cosh(xf))));
			} else {			
				Ic += fator * h_aux * (11*f(x_Exp_Dupla(a, b, xi), opc_formula)*((M_PI*(b-a))/4)*(cosh(xi)/(cosh((M_PI/2)*sinh(xi))*cosh((M_PI/2)*sinh(xi)))) + f(x_Exp_Dupla(a, b, x1), opc_formula)*((M_PI*(b-a))/4)*(cosh(x1)/(cosh((M_PI/2)*sinh(x1))*cosh((M_PI/2)*sinh(x1)))) + f(x_Exp_Dupla(a, b, x2), opc_formula)*((M_PI*(b-a))/4)*(cosh(x2)/(cosh((M_PI/2)*sinh(x2))*cosh((M_PI/2)*sinh(x2)))) + 11*f(x_Exp_Dupla(a, b, xf), opc_formula)*((M_PI*(b-a))/4)*(cosh(xf)/(cosh((M_PI/2)*sinh(xf))*cosh((M_PI/2)*sinh(xf)))));
			}
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

float NewtonCodes_Fechada_Grau4_Particao(float c_min, float c_max, float a, float b, int num_particao, int opc_formula, int tipo){
	float Ic = 0, h, xi, xf, x1, x2, x3, h_aux, fator = 0.0444444;
	int i = 0;
	
	h = (c_min + c_max) / num_particao;
	xi = c_min;

	while (i < num_particao){
		xf = xi + h;
		h_aux = (xf - xi)/4;
		x1 = xi + h_aux;
		x2 = xi + 2*h_aux;
		x3 = xi + 3*h_aux;
		if (tipo == 1){
			Ic += fator * h_aux * (7*f(x_Exp_Simples(a, b, xi), opc_formula)*(((b-a)/2)*(1/cosh(xi))) + 32*f(x_Exp_Simples(a, b, x1), opc_formula)*(((b-a)/2)*(1/cosh(x1))) + 12*f(x_Exp_Simples(a, b, x2), opc_formula)*(((b-a)/2)*(1/cosh(x2))) + 32*f(x_Exp_Simples(a, b, x3), opc_formula)*(((b-a)/2)*(1/cosh(x3))) + 7*f(x_Exp_Simples(a, b, xf), opc_formula)*(((b-a)/2)*(1/cosh(xf)))); 
		} else {
			Ic += fator * h_aux * (7*f(x_Exp_Dupla(a, b, xi), opc_formula)*((M_PI*(b-a))/4)*(cosh(xi)/(cosh((M_PI/2)*sinh(xi))*cosh((M_PI/2)*sinh(xi)))) + 32*f(x_Exp_Dupla(a, b, x1), opc_formula)*((M_PI*(b-a))/4)*(cosh(x1)/(cosh((M_PI/2)*sinh(x1))*cosh((M_PI/2)*sinh(x1)))) + 12*f(x_Exp_Dupla(a, b, x2), opc_formula)*((M_PI*(b-a))/4)*(cosh(x2)/(cosh((M_PI/2)*sinh(x2))*cosh((M_PI/2)*sinh(x2)))) + 32*f(x_Exp_Dupla(a, b, x3), opc_formula)*((M_PI*(b-a))/4)*(cosh(x3)/(cosh((M_PI/2)*sinh(x3))*cosh((M_PI/2)*sinh(x3)))) + 7*f(x_Exp_Dupla(a, b, xf), opc_formula)*((M_PI*(b-a))/4)*(cosh(xf)/(cosh((M_PI/2)*sinh(xf))*cosh((M_PI/2)*sinh(xf))))); 
		}
		xi = xf;
		i ++;
		
	}
	
	return Ic;
}

float NewtonCodes_Fechada_Grau4_Tolerancia(float c_min, float c_max, float a, float b, float tolerancia, int opc_formula, int tipo){
	float Ic, Ia = 0, h, xi, xf, x1, x2, x3, h_aux, fator = 0.0444444, erro = 10;
	int i = 0, num_particao = 1;
	
	while ( erro > tolerancia) {
		i = 0;
		h = (c_min + c_max) / num_particao;
		xi = c_min;
		Ic = 0;

		while (i < num_particao){
			xf = xi + h;
			h_aux = (xf - xi)/4;
			x1 = xi + h_aux;
			x2 = xi + 2*h_aux;
			x3 = xi + 3*h_aux;
			if (tipo == 1){
				Ic += fator * h_aux * (7*f(x_Exp_Simples(a, b, xi), opc_formula)*(((b-a)/2)*(1/cosh(xi))) + 32*f(x_Exp_Simples(a, b, x1), opc_formula)*(((b-a)/2)*(1/cosh(x1))) + 12*f(x_Exp_Simples(a, b, x2), opc_formula)*(((b-a)/2)*(1/cosh(x2))) + 32*f(x_Exp_Simples(a, b, x3), opc_formula)*(((b-a)/2)*(1/cosh(x3))) + 7*f(x_Exp_Simples(a, b, xf), opc_formula)*(((b-a)/2)*(1/cosh(xf)))); 
			} else {	
 				Ic += fator * h_aux * (7*f(x_Exp_Dupla(a, b, xi), opc_formula)*((M_PI*(b-a))/4)*(cosh(xi)/(cosh((M_PI/2)*sinh(xi))*cosh((M_PI/2)*sinh(xi)))) + 32*f(x_Exp_Dupla(a, b, x1), opc_formula)*((M_PI*(b-a))/4)*(cosh(x1)/(cosh((M_PI/2)*sinh(x1))*cosh((M_PI/2)*sinh(x1)))) + 12*f(x_Exp_Dupla(a, b, x2), opc_formula)*((M_PI*(b-a))/4)*(cosh(x2)/(cosh((M_PI/2)*sinh(x2))*cosh((M_PI/2)*sinh(x2)))) + 32*f(x_Exp_Dupla(a, b, x3), opc_formula)*((M_PI*(b-a))/4)*(cosh(x3)/(cosh((M_PI/2)*sinh(x3))*cosh((M_PI/2)*sinh(x3)))) + 7*f(x_Exp_Dupla(a, b, xf), opc_formula)*((M_PI*(b-a))/4)*(cosh(xf)/(cosh((M_PI/2)*sinh(xf))*cosh((M_PI/2)*sinh(xf))))); 
			}
			xi = xf;
			i ++;
		}
		
		erro = Ic - Ia; 
		Ia = Ic;
		num_particao += 1;
	}
	
	return Ic;
}

float NewtonCodes_Aberta_Grau4_Particao(float c_min, float c_max, float a, float b, int num_particao, int opc_formula, int tipo){
	float Ic = 0, h, xi, xf, x1, x2, x3, h_aux, fator = 0.3;
	int i = 0;
	
	h = (c_max + c_min) / num_particao;
	h_aux = (c_max - c_min)/(num_particao*6);
	xi = c_min + h_aux;

	while (i < num_particao){
		x1 = xi + h_aux;
		x2 = x1 + h_aux;
		x3 = x2 + h_aux;
		xf = x3 + h_aux;
		if (tipo == 1){
			Ic += fator * h_aux * (11*f(x_Exp_Simples(a, b, xi), opc_formula)*(((b-a)/2)*(1/cosh(xi))) - 14*f(x_Exp_Simples(a, b, x1), opc_formula)*(((b-a)/2)*(1/cosh(x1))) + 26*f(x_Exp_Simples(a, b, x2), opc_formula)*(((b-a)/2)*(1/cosh(x2))) - 14*f(x_Exp_Simples(a, b, x3), opc_formula)*(((b-a)/2)*(1/cosh(x3))) + 11*f(x_Exp_Simples(a, b, xf), opc_formula)*(((b-a)/2)*(1/cosh(xf)))); 
		} else {
			Ic += fator * h_aux * (11*f(x_Exp_Dupla(a, b, xi), opc_formula)*((M_PI*(b-a))/4)*(cosh(xi)/(cosh((M_PI/2)*sinh(xi))*cosh((M_PI/2)*sinh(xi)))) - 14*f(x_Exp_Dupla(a, b, x1), opc_formula)*((M_PI*(b-a))/4)*(cosh(x1)/(cosh((M_PI/2)*sinh(x1))*cosh((M_PI/2)*sinh(x1)))) + 26*f(x_Exp_Dupla(a, b, x2), opc_formula)*((M_PI*(b-a))/4)*(cosh(x2)/(cosh((M_PI/2)*sinh(x2))*cosh((M_PI/2)*sinh(x2)))) - 14*f(x_Exp_Dupla(a, b, x3), opc_formula)*((M_PI*(b-a))/4)*(cosh(x3)/(cosh((M_PI/2)*sinh(x3))*cosh((M_PI/2)*sinh(x3)))) + 11*f(x_Exp_Dupla(a, b, xf), opc_formula)*((M_PI*(b-a))/4)*(cosh(xf)/(cosh((M_PI/2)*sinh(xf))*cosh((M_PI/2)*sinh(xf)))));
		}
		xi = xf + 2*h_aux;
		i ++;
		
	}
	
	return Ic;
}

float NewtonCodes_Aberta_Grau4_Tolerancia(float c_min, float c_max, float a, float b, float tolerancia, int opc_formula, int tipo){
	float Ic, Ia = 0, h, xi, xf, x1, x2, x3, h_aux, fator = 0.3, erro = 10;
	int i = 0, num_particao = 1;
	
	while ( erro > tolerancia) {
		i = 0;
		h = (c_min + c_max) / num_particao;
		h_aux = (c_max - c_min)/(num_particao*6);
		xi = c_min + h_aux;
		Ic = 0;

		while (i < num_particao){
			x1 = xi + h_aux;
			x2 = x1 + h_aux;
			x3 = x2 + h_aux;
			xf = x3 + h_aux;
			if (tipo == 1){
				Ic += fator * h_aux * (11*f(x_Exp_Simples(a, b, xi), opc_formula)*(((b-a)/2)*(1/cosh(xi))) - 14*f(x_Exp_Simples(a, b, x1), opc_formula)*(((b-a)/2)*(1/cosh(x1))) + 26*f(x_Exp_Simples(a, b, x2), opc_formula)*(((b-a)/2)*(1/cosh(x2))) - 14*f(x_Exp_Simples(a, b, x3), opc_formula)*(((b-a)/2)*(1/cosh(x3))) + 11*f(x_Exp_Simples(a, b, xf), opc_formula)*(((b-a)/2)*(1/cosh(xf))));  
			} else {
				Ic += fator * h_aux * (11*f(x_Exp_Dupla(a, b, xi), opc_formula)*((M_PI*(b-a))/4)*(cosh(xi)/(cosh((M_PI/2)*sinh(xi))*cosh((M_PI/2)*sinh(xi)))) - 14*f(x_Exp_Dupla(a, b, x1), opc_formula)*((M_PI*(b-a))/4)*(cosh(x1)/(cosh((M_PI/2)*sinh(x1))*cosh((M_PI/2)*sinh(x1)))) + 26*f(x_Exp_Dupla(a, b, x2), opc_formula)*((M_PI*(b-a))/4)*(cosh(x2)/(cosh((M_PI/2)*sinh(x2))*cosh((M_PI/2)*sinh(x2)))) - 14*f(x_Exp_Dupla(a, b, x3), opc_formula)*((M_PI*(b-a))/4)*(cosh(x3)/(cosh((M_PI/2)*sinh(x3))*cosh((M_PI/2)*sinh(x3)))) + 11*f(x_Exp_Dupla(a, b, xf), opc_formula)*((M_PI*(b-a))/4)*(cosh(xf)/(cosh((M_PI/2)*sinh(xf))*cosh((M_PI/2)*sinh(xf)))));
			}
			xi = xf + 2*h_aux;
			i ++;
		}

		erro = Ic - Ia; 
		Ia = Ic;
		num_particao += 1;
	}
	
	return Ic;
}

float Exponencial_Simples(float a, float b, float tolerancia1, float tolerancia2, float opc_formula, int metodo, int num_particao){
	float c_min, c_max, erro = 10, Ic, Ia = 0;
	int i = 0;

	c_min = -1;
	c_max = 1;

	while( erro > tolerancia2){
		Ic = 0;

		switch(metodo){
			case 1:
				Ic = NewtonCodes_Fechada_Trapezio_Particao(c_min, c_max, a, b, num_particao, opc_formula, 1);
			case 2:
				Ic = NewtonCodes_Fechada_Trapezio_Tolerancia(c_min, c_max, a, b, tolerancia2, opc_formula, 1);
			case 3:
				Ic = NewtonCodes_Aberta_Trapezio_Particao(c_min, c_max, a, b, num_particao, opc_formula, 1);
			case 4:
				Ic = NewtonCodes_Aberta_Trapezio_Tolerancia(c_min, c_max, a, b, tolerancia2, opc_formula, 1);
			case 5:
				Ic = NewtonCodes_Fechada_Grau2_Particao(c_min, c_max, a, b, num_particao, opc_formula, 1);
			case 6:
				Ic = NewtonCodes_Fechada_Grau2_Tolerancia(c_min, c_max, a, b, tolerancia2, opc_formula, 1);
			case 7:
				Ic = NewtonCodes_Aberta_Grau2_Particao(c_min, c_max, a, b, num_particao, opc_formula, 1);
			case 8:
				Ic = NewtonCodes_Aberta_Grau2_Tolerancia(c_min, c_max, a, b, tolerancia2, opc_formula, 1);
			case 9:
				Ic = NewtonCodes_Fechada_Grau3_Particao(c_min, c_max, a, b, num_particao, opc_formula, 1);
			case 10:
				Ic = NewtonCodes_Fechada_Grau3_Tolerancia(c_min, c_max, a, b, tolerancia2, opc_formula, 1);
			case 11:
				Ic = NewtonCodes_Aberta_Grau3_Particao(c_min, c_max, a, b, num_particao, opc_formula, 1);
			case 12:
				Ic = NewtonCodes_Aberta_Grau3_Tolerancia(c_min, c_max, a, b, tolerancia2, opc_formula, 1);
			case 13:
				Ic = NewtonCodes_Fechada_Grau4_Particao(c_min, c_max, a, b, num_particao, opc_formula, 1);
			case 14:
				Ic = NewtonCodes_Fechada_Grau4_Tolerancia(c_min, c_max, a, b, tolerancia2, opc_formula, 1);
			case 15:
				Ic = NewtonCodes_Aberta_Grau4_Particao(c_min, c_max, a, b, num_particao, opc_formula, 1);
			case 16:
				Ic = NewtonCodes_Aberta_Grau4_Tolerancia(c_min, c_max, a, b, tolerancia2, opc_formula, 1);
		}

		erro = (Ic - Ia)/Ic;
		Ia = Ic;
		c_min -= 1;
		c_max += 1;
	}

	return Ic;
}

float Exponencial_Dupla(float a, float b, float tolerancia1, float tolerancia2, float opc_formula, int metodo, int num_particao){
	float c_min, c_max, erro = 10, Ic, Ia = 0;
	int i = 0;

	c_min = -1;
	c_max = 1;

	while( erro > tolerancia2){
		Ic = 0;

		switch(metodo){
			case 1:
				Ic = NewtonCodes_Fechada_Trapezio_Particao(c_min, c_max, a, b, num_particao, opc_formula, 2);
			case 2:
				Ic = NewtonCodes_Fechada_Trapezio_Tolerancia(c_min, c_max, a, b, tolerancia2, opc_formula, 2);
			case 3:
				Ic = NewtonCodes_Aberta_Trapezio_Particao(c_min, c_max, a, b, num_particao, opc_formula, 2);
			case 4:
				Ic = NewtonCodes_Aberta_Trapezio_Tolerancia(c_min, c_max, a, b, tolerancia2, opc_formula, 2);
			case 5:
				Ic = NewtonCodes_Fechada_Grau2_Particao(c_min, c_max, a, b, num_particao, opc_formula, 2);
			case 6:
				Ic = NewtonCodes_Fechada_Grau2_Tolerancia(c_min, c_max, a, b, tolerancia2, opc_formula, 2);
			case 7:
				Ic = NewtonCodes_Aberta_Grau2_Particao(c_min, c_max, a, b, num_particao, opc_formula, 2);
			case 8:
				Ic = NewtonCodes_Aberta_Grau2_Tolerancia(c_min, c_max, a, b, tolerancia2, opc_formula, 2);
			case 9:
				Ic = NewtonCodes_Fechada_Grau3_Particao(c_min, c_max, a, b, num_particao, opc_formula, 2);
			case 10:
				Ic = NewtonCodes_Fechada_Grau3_Tolerancia(c_min, c_max, a, b, tolerancia2, opc_formula, 2);
			case 11:
				Ic = NewtonCodes_Aberta_Grau3_Particao(c_min, c_max, a, b, num_particao, opc_formula, 2);
			case 12:
				Ic = NewtonCodes_Aberta_Grau3_Tolerancia(c_min, c_max, a, b, tolerancia2, opc_formula, 2);
			case 13:
				Ic = NewtonCodes_Fechada_Grau4_Particao(c_min, c_max, a, b, num_particao, opc_formula, 2);
			case 14:
				Ic = NewtonCodes_Fechada_Grau4_Tolerancia(c_min, c_max, a, b, tolerancia2, opc_formula, 2);
			case 15:
				Ic = NewtonCodes_Aberta_Grau4_Particao(c_min, c_max, a, b, num_particao, opc_formula, 2);
			case 16:
				Ic = NewtonCodes_Aberta_Grau4_Tolerancia(c_min, c_max, a, b, tolerancia2, opc_formula, 2);
		}

		erro = (Ic - Ia)/Ic;
		Ia = Ic;
		c_min -= 1;
		c_max += 1;
	}

	return Ic;
}
int main(){

	int opc_formulaInt,  opc_funcao, opc_xMin, opc_xMax, opc_metodo, opc_particao, num_particao, grau;
	float a, b, tolerancia1, tolerancia2;	

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
					cin >> tolerancia2;

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

	do{
		cout << "\n\n###################################################################";
		cout << "\n###################################################################";
		cout << "\n###################################################################";

		cout << "\n\nESCOLHA A FORMULA DE INTEGRACAO:";
		cout << "\n\n1 - NEWTON-CODES GRAU 1 - 4 FÓRMULA FECHADA";
		cout << "\n2 - NEWTON-CODES GRAU 1 - 4 FÓRMULA ABERTA";
		cout << "\n0 - SAIR";
	
		cin >> opc_formulaInt;
	
		switch(opc_formulaInt){
			case 1:	
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
								opc_formulaInt = 1;
							} else{
								opc_formulaInt = 2;
							}
							break;
						case 2:
							if (opc_particao == 1){
								opc_formulaInt = 5;
							} else {
								opc_formulaInt = 6;
							}
							break;
						case 3:
							if (opc_particao == 1){
								opc_formulaInt = 9;
							} else {
								opc_formulaInt = 10;
							}
							break;
						case 4:
							if (opc_particao == 1){
								opc_formulaInt = 13;
							} else {
								opc_formulaInt = 14;
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
								opc_formulaInt = 3;
							} else{
								opc_formulaInt = 4;
							}
							break;
						case 2:
							if (opc_particao == 1){
								opc_formulaInt = 7;
							} else {
								opc_formulaInt = 8;
							}
							break;
						case 3:
							if (opc_particao == 1){
								opc_formulaInt = 11;
							} else {
								opc_formulaInt = 12;
							}
							break;
						case 4:
							if (opc_particao == 1){
								opc_formulaInt = 15;
							} else {
								opc_formulaInt = 16;
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
	
	do{
		cout << "\n\n###################################################################";
		cout << "\n###################################################################";
		cout << "\n###################################################################";

		cout << "\n\nESCOLHA A FORMULA DE INTEGRACAO:";
		cout << "\n\n1 - EXPONENCIAL SIMPLES";
		cout << "\n2 - EXPONENCIAL DUPLA";
		cout << "\n0 - SAIR";
	
		cin >> opc_metodo;

		cout << "\n\n###################################################################";
		cout << "\n###################################################################";
		cout << "\n###################################################################";

		cout << "\n\nINFORME A TOLERÂNCIA E1:";
		cin >> tolerancia1;

		cout << "\n\n###################################################################";
		cout << "\n###################################################################";
		cout << "\n###################################################################";

		cout << "\n\nINFORME A TOLERÂNCIA E2:";
		cin >> tolerancia2;

		switch(opc_metodo){
			case 1:	
				cout << "\n\nINTEGRAL = " << Exponencial_Simples(a, b, tolerancia1, tolerancia2, opc_funcao, opc_formulaInt, num_particao);
			case 2:
				cout << "\n\nINTEGRAL = " << Exponencial_Dupla(a, b, tolerancia1, tolerancia2, opc_funcao, opc_formulaInt, num_particao);
			case 0:
				break;
			default:
				cout << "\n\nOPCAO INVALIDA! TENTE NOVAMENTE.";
				opc_metodo = -1;
				break;
		}
	} while (opc_metodo == -1 && opc_metodo != 0);
	return 0;
}