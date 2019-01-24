// Andreza Fernandes de Oliveira, 384341
// ARQUIVO CORRETO
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define M_PI 3.14159265358979323846

using namespace std;


float GaussLegendre_Grau2(){}

float GaussLegendre_Grau3(){}

float GaussLegendre_Grau4(){}

float GaussLegendre_Grau5(){}


void menu(){
	// vê se não é melhor modularizar isso aqui e deixar bonitinho
	int opc_formulaInt,  opc_funcao, opc_xMin, opc_xMax, opc_particao, num_particao;
	float a, b, tolerancia;	

	cout << “\n###################################################################”;
	cout << “\n###################################################################”;
	cout << “\n###################################################################”;

	cout << “\nDigite a fórmula desejada:”;
	cout << “\n1 - sen(x)”;
	cout << “\n2 - cos(x)”;
	cout << “\n3 - tan(x)”;

	cin >> opc_funcao;
	
	switch(opc_funcao){
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			cout << “\nOpção inválida! Tente novamente.”;
	}
	
	//clear
	cout << “\n###################################################################”;
	cout << “\n###################################################################”;
	cout << “\n###################################################################”;

	cout << “\nDigite a opção de partição desejada:”;
	cout << “\n1 - Tolerância”;
	cout << “\n2 - Número definido de partições”;

	cin >> opc_particao;
	
	switch(opc_particao){
		case 1:
			//clear
			cout << “\n###################################################################”;
			cout << “\n###################################################################”;
			cout << “\n###################################################################”;

			cout << “\nDigite o valor da tolerância:”;
			cin >> tolerancia;

			break;
		case 2:
			//clear
			cout << “\n###################################################################”;
			cout << “\n###################################################################”;
			cout << “\n###################################################################”;

			cout << “\nDigite o número de partições:”;
			cin >> num_particao;

			break;
		default:
			cout << “\nOpção inválida! Tente novamente.”;
	}

	//clear
	cout << “\n###################################################################”;
	cout << “\n###################################################################”;
	cout << “\n###################################################################”;

	cout << “\nDigite o xMínimo:”;
	cout << “\n1 - 0”;
	cout << “\n2 - r/2”;
	cout << “\n3 - r/4”;
	cout << “\n4 - r/8”;
	cout << “\n5 - Outro”;
	
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
			cout << “\nDigite o valor:”;
			cin >> a;
			break;
		default:
			cout << “\nOpção inválida! Tente novamente.”;

	}
	//clear

	cout << “\n###################################################################”;
	cout << “\n###################################################################”;
	cout << “\n###################################################################”;

	cout << “\nDigite o x_Máximo:”;
	cout << “\n1 - 0”;
	cout << “\n2 - r/2”;
	cout << “\n3 - r/4”;
	cout << “\n4 - r/8”;
	cout << “\n5 - Outro”;
	
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
			cout << “\nDigite o valor:”;
			cin >> b;
			break;
		default:
			cout << “\nOpção inválida! Tente novamente.”;
	}

	//clear
	cout << “\n###################################################################”;
	cout << “\n###################################################################”;
	cout << “\n###################################################################”;

	cout << “\nInforme a fórmula de integração desejada:”;
	cout << “\n1 - Newton-Codes  grau 1 - 4 FÓRMULA FECHADA”;
	cout << “\n2 - Newton-Codes  grau 1 - 4 FÓRMULA ABERTA”;
	cout << “\n3 - Gauss-Legendre 2 - 5”;
	
	cin >> opc_formulaInt;
	
	switch(opc_formulaInt){
		case 1:

			//clear
			cout << “\n###################################################################”;
			cout << “\n###################################################################”;
			cout << “\n###################################################################”;

			cout << “\nInforme o grau do polinômio”;
			cin >> grau;
			
			switch(grau){
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				default:
					cout << “\nOpção inválida! Tente novamente.”;
					break;
			}
			break;

		case 2:

			//clear
			cout << “\n###################################################################”;
			cout << “\n###################################################################”;
			cout << “\n###################################################################”;

			cout << “\nInforme o grau do polinômio”;
			cin >> grau;
			
			switch(grau){
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				default:
					cout << “\nOpção inválida! Tente novamente.”;
					break;
			}
			
			break;
		
		case 3:

			//clear
			cout << “\n###################################################################”;
			cout << “\n###################################################################”;
			cout << “\n###################################################################”;

			cout << “\nInforme o grau do polinômio”;
			cin >> grau;
			
			switch(grau){
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				default:
					cout << “\nOpção inválida! Tente novamente.”;
					break;
			}
			
			break;
		default:
			cout << “\nOpção inválida! Tente novamente.”;
	}
}


void main(){


}



https://www.ufrgs.br/numerico/livro/in-quadratura_de_gauss-legendre.html
