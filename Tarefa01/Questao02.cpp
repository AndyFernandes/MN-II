
// Andreza Fernandes de Oliveira, 384341
// ARQUIVO CORRETO
/* TAREFA 01 - QUESTÃO 02*/
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

float raiz_GaussChebyshen(int k, int n){
	return cos((2*k + 1)*M_PI)/(2*n - 1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////   FÓRMULAS GAUSS-HERMITE   ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////   GAUSS - HERMITE  2 PONTOS   //////////////////////////////////////////////////

float GaussHermite_2Pontos(int opc_formula){
	float w[2], x[2], I=0;

	w[0] = 0.8862269254;
	w[1] = 0.8862269254;

	x[0] = -1 * 0.7071067811;
	x[1] = 0.7071067811;

	for(int i = 0; i < 2; i++){
		I += w[i] * f(x[i], opc_formula);
	}

	return I;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////   GAUSS - HERMITE  3 PONTOS   //////////////////////////////////////////////////

float GaussHermite_3Pontos(int opc_formula){
	float w[3], x[3], I=0;

	w[0] = 0.2954089751;
	w[1] = 1.181635900;
	w[2] = 0.2954089751;

	x[0] = -1 * 1.224744871;
	x[1] = 0;
	x[2] = 1.224744871;

	for(int i = 0; i < 3; i++){
		I += w[i] * f(x[i], opc_formula);
	}

	return I;

}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////   GAUSS - HERMITE  4 PONTOS   //////////////////////////////////////////////////

float GaussHermite_4Pontos(int opc_formula){
	float w[4], x[4], I=0;

	w[0] = 0.08131283544;
	w[1] = 0.8049140900;
	w[2] = 0.8049140900;
	w[3] = 0.08131283544;

	x[0] = -1 * 1.650680123;
	x[1] = -1 * 0.5246476323;
	x[2] = 0.5246476323;
	x[3] = 1.650680123;

	for(int i = 0; i < 4; i++){
		I += w[i] * f(x[i], opc_formula);
	}

	return I;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////   FÓRMULAS GAUSS-LAGUERRE   //////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////   GAUSS - LAGUERRE  2 PONTOS   //////////////////////////////////////////////////

float GaussLaguerre_2Pontos(int opc_formula){
	float w[2], x[2], I=0;

	w[0] = 0.8535533905;
	w[1] = 0.1464466094;

	x[0] = 0.5857864376;
	x[1] = 3.414213562;

	for(int i = 0; i < 2; i++){
		I += w[i] * f(x[i], opc_formula);
	}

	return I;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////   GAUSS - LAGUERRE  3 PONTOS   //////////////////////////////////////////////////

float GaussLaguerre_3Pontos(int opc_formula){
	float w[3], x[3], I=0;

	w[0] = 0.7110930099;
	w[1] = 0.2785177335;
	w[2] = 0.01038925650;

	x[0] = 0.4157745567;
	x[1] = 2.294280360;
	x[2] = 6.289945082;

	for(int i = 0; i < 3; i++){
		I += w[i] * f(x[i], opc_formula);
		cout << "\n" << I;
	}

	return I;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////   GAUSS - LAGUERRE  4 PONTOS   //////////////////////////////////////////////////

float GaussLaguerre_4Pontos(int opc_formula){
	float w[4], x[4], I=0;

	w[0] = 0.6031541043;
	w[1] = 0.3574186924;
	w[2] = 0.03888790851;
	w[3] = 0.0005392947055 ;

	x[0] = 0.3225476896;
	x[1] = 1.745761101;
	x[2] = 4.536620296;
	x[3] = 9.395070912;

	for(int i = 0; i < 4; i++){
		I += w[i] * f(x[i], opc_formula);
	}

	return I;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////   FÓRMULAS GAUSS-CHEBYSHEN   /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float GaussChebyshen(int opc_formula, int n){
	float w, I=0;

	w = M_PI / (n+1);

	for(int i = 0; i < 2; i++){
		I += f(raiz_GaussChebyshen(i, n), opc_formula);
	}

	return w*I;
}

void menu(){
	int opc_formulaInt,  opc_funcao, pontos;

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

		cout << "\n\nESCOLHA A FORMULA DE INTEGRACAO:";
		cout << "\n\n1 - GAUSS-LAGUERRE 2 - 4 PONTOS";
		cout << "\n2 - GAUSS-HERMITE 2 - 4 PONTOS";
		cout << "\n3 - GAUSS-CHEBYSHEN";
		cout << "\n0 - SAIR";
	
		cin >> opc_formulaInt;
	
		switch(opc_formulaInt){
			case 1:	
				//clear
				do{
					cout << "\n\n###################################################################";
					cout << "\n###################################################################";
					cout << "\n###################################################################";

					cout << "\n\nESCOLHA O NUMERO DE PONTOS:";
					cout << "\n\n1 - 2 PONTOS";
					cout << "\n2 - 3 PONTOS";
					cout << "\n3 - 4 PONTOS";
					cout << "\n0 - SAIR";
		
					cin >> pontos;
			
					switch(pontos){
					case 1:
						cout << "\n\nINTEGRAL = " << GaussLaguerre_2Pontos(opc_funcao);
						break;

					case 2:
						cout << "\n\nINTEGRAL = " << GaussLaguerre_3Pontos(opc_funcao);			
						break;

					case 3:
						cout << "\n\nINTEGRAL = " << GaussLaguerre_4Pontos(opc_funcao);
						break;

					case 0:
						break;
					default:
						cout << "\n\nOPCAO INVALIDA! TENTE NOVAMENTE..";
						pontos = -1;
						break;
					}
				} while (pontos == -1 && pontos != 0);
				break;

			case 2:
			//clear
				do{
					cout << "\n\n###################################################################";
					cout << "\n###################################################################";
					cout << "\n###################################################################";

					cout << "\n\nESCOLHA O NUMERO DE PONTOS:";
					cout << "\n\n1 - 2 PONTOS";
					cout << "\n2 - 3 PONTOS";
					cout << "\n3 - 4 PONTOS";
					cout << "\n0 - SAIR";
		
					cin >> pontos;
			
					switch(pontos){
					case 1:
						cout << "\n\nINTEGRAL = " << GaussHermite_2Pontos(opc_funcao);
						break;

					case 2:
						cout << "\n\nINTEGRAL = " << GaussHermite_3Pontos(opc_funcao);			
						break;

					case 3:
						cout << "\n\nINTEGRAL = " << GaussHermite_4Pontos(opc_funcao);
						break;

					case 0:
						break;
					default:
						cout << "\n\nOPCAO INVALIDA! TENTE NOVAMENTE..";
						pontos = -1;
						break;
					}
				} while (pontos == -1 && pontos != 0);
				break;

			case 3:
				cout <<"\n\nDIGITE A QUANTIDADE DE PONTOS:";
				cin >> pontos;

				cout << "\n\nINTEGRAL = " << GaussChebyshen(opc_funcao, pontos);
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

int main(){
	return 0;
}
