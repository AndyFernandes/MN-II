#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


/*
	NEWTON-CODES
		FECHADA
			- FÓRMULA INTEGRAL GERAL
			- REGRA DO TRAPÉZIO
			- POLINÔMIO GRAU 1, 2, 3, 4

		ABERTA
			- REGRA DO TRAPÉZIO
			- POLINÔMIO GRAU 1, 2, 3, 4

	GAUSS-LEGENDRE
		


*/



void menu(){
	int opc_h = 0;
	int opc_intervalo = 0;
	float x_min = 0., x_max = 0.;
	int n_particoes = 0;
	float tolerancia = 0.;
	int opc_formula = 0; 
	int opc_grau;


	do{

		cout << "\n Digite o valor de x_min:";
		cin >> x_min;

		cout << "\n Digite o valor de x_max:";
		cin >> x_max;

		do{ 
			cout << "\n Qual a forma de integração que você deseja?";
			cout << "\n 1. Numero definido de partições";
			cout << "\n 2. Tolerância ";
			cin >> opc_h;

			switch(opc_h){
				case 1:
					cout << "\n Defina o numero de partições desejada:";
					cin >> n_particoes;
					break;
				
				case 2:
					cout << "\n Define a tolerância desejada:";
					cin >> tolerancia;
					break;

				default:
					cout << "\n Opção inválida, por favor, tente novamente.";
					break;
			}
		} while (opc_h != 1 || opc_h != 2);

		
		do{
			cout << "\n Qual a formula que você deseja utilizar?";
			cout << "\n 1. Newton-Codes FILOSOFIA FECHADA";
			cout << "\n 2. Newton-Codes FILOSOFIA ABERTA";
			cout << "\n 3. Gauss-Legendre";
			cin >> opc_formula

			switch(opc_formula){
				case 1:
					cout << "\n Defina o grau do polinômio:";
					cin >> opc_grau;

					switch(opc_grau){
						case 1:
						case 2:
						case 3:
						case 4:
						default:
					}

					break;
				
				case 2:
					cout << "\n Defina o grau do polinômio:";
					cin >> opc_grau;

					switch(opc_grau){
						case 1:
						case 2:
						case 3:
						case 4:
						default:
					}
					break;

				case 3:
					cout << "\n Defina o grau do polinômio:";
					cin >> opc_grau;

					switch(opc_grau){
						case 2:
						case 3:
						case 4:
						case 5:
						default:
					}
					break;

				default:
					cout << "\n Opção inválida, por favor, tente novamente.";
					break;

			}
		} while(opc_formula != 1 || opc_formula != 2 || opc_formula != 3);
		




	} while();
}