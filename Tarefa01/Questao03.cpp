// Andreza Fernandes de Oliveira, 384341
// ARQUIVO CORRETO
/* TAREFA 01 - QUESTÃO 03*/
// tarefa não concluida
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define M_PI 3.14159265358979323846

using namespace std;

float f(float valor, int opc_formula) { 
	return (1.0 / pow(pow(valor, 2), (1.0/3.0)));
}

float x_Exp_Simples(float a, float b, float alfa){
	return ((a+b)/2.0) + tanh(alfa)*((b-a)/2.0);
}

float x_Exp_Dupla(float a, float b, float alfa){
	return ((a+b)/2.0) + tanh((M_PI/2)*sinh(alfa))*((b-a)/2);
}

float f_simples(double a, double b, double x, int opc_formula){
	double xalfa = x_Exp_Simples(a, b, x);
	return f(xalfa, 1)* ((b-a)/pow(cosh(x), 2));
}

/*float f_dupla(double a, double b, double x){

}
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////   TRAPÉZIO   ///////////////////////////////////////////////////////////
float NewtonCodes_Fechada_Trapezio_Particao(float c_min, float c_max, float a, float b, int num_particao, int opc_formula, int tipo) {
	float Ic = 0, h, xi, xf;
	int i = 0;
	
	h = (c_max - c_min) / num_particao;
	xi = c_min;
	xf = xi + h;

	while (i < num_particao) {
		if (tipo == 1){
			Ic +=  ((xf - xi)/ 2.0) * (f_simples(a, b, xi, opc_formula) + f_simples(a, b, xf, opc_formula));
			cout << Ic << "\n";
		} 
		/*else {
			Ic = ((xf - xi)/ 2) * (f_dupla(a, b, xi) + f_dupla(a, b, xf));
		} */
		xi = xf;
		xf += h;
		i ++;	
	}
	
	return Ic;
}

float Exponencial_Simples(float a, float b, float tolerancia1, float tolerancia2, float opc_formula, int metodo, int num_particao){
	float c_min, c_max, erro = 1, Ic, Ia = 0;
	int i = 0;

	c_min = -1;
	c_max = 1;

	while( erro > tolerancia2){
		Ic = 0;

		//switch(metodo){
		//	case 1:
				Ic = NewtonCodes_Fechada_Trapezio_Particao(c_min, c_max, a, b, num_particao, opc_formula, 1);

			/*case 2:
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
				Ic = NewtonCodes_Aberta_Grau4_Tolerancia(c_min, c_max, a, b, tolerancia2, opc_formula, 1);*/
			//default:
			//	cout << "Deu pau";
			//	break;
		//}

		erro = fabs((Ic - Ia)/Ic);
		cout << "ERRO: "<<erro <<"\n";
		Ia = Ic;
		c_min -= 1;
		c_max += 1;
	}

	return Ic;
}
/*

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
*/
int main(){
	float a = 0;
	float b = 1;
	float tolerancia1 = 0.001;
	float tolerancia2 = 0.001;
	float opc_formula = 1;
	int metodo = 1;
	int num_particao = 2;
	cout << Exponencial_Simples(a, b, tolerancia1, tolerancia2, opc_formula, metodo, num_particao);
	return 0;
}
