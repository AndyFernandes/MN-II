#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <cmath>
using namespace std;

/*struct S
{
	int tamanho;
	double estados[4][tamanho]; // eu deixo como matriz ou variaveis mesmo?
	double t[tamanho];
	double delta;
	int func[4];
};

double F(S estadoAtual, int atual, double t, int numeroFuncao){
	double resultado = 0.0;

	if(numeroFuncao == 0){
		//u1
		resultado = 
	} else if (numeroFuncao == 1){
		//u2
	} else if(numeroFuncao == 2){
		//v1
	} else if (numeroFuncao == 3){
		//v2
	}
	return resultado;
}

void metodoForwardEuller(S estado, int atual){
	estado.estados[0][atual+1] = estado.estados[0][atual] + estado.delta*F(estado, atual, estado.t[atual], estado.func[0]);
	estado.estados[1][atual+1] = estado.estados[1][atual] + estado.delta*F(estado, atual, estado.t[atual], estado.func[1]);
	estado.estados[2][atual+1] = estado.estados[2][atual] + estado.delta*F(estado, atual, estado.t[atual], estado.func[2]);
	estado.estados[3][atual+1] = estado.estados[3][atual] + estado.delta*F(estado, atual, estado.t[atual], estado.func[3]);
}

double metodoBackwardEuller(S estado, int atual){
	while(){
		estado.estados[0][atual+1] = estado.estados[0][atual] + estado.delta*F(estado, atual+1, estado.t[atual+1], estado.func[0]);
		estado.estados[1][atual+1] = estado.estados[1][atual] + estado.delta*F(estado, atual+1, estado.t[atual+1], estado.func[1]);
		estado.estados[2][atual+1] = estado.estados[2][atual] + estado.delta*F(estado, atual+1, estado.t[atual+1], estado.func[2]);
		estado.estados[3][atual+1] = estado.estados[3][atual] + estado.delta*F(estado, atual+1, estado.t[atual+1], estado.func[3]);
		//fazer o estudo de convergencia aqui
	}
}
*/

double f(double Si, double ti){
	return -4*Si - 5*cos(ti);
}

double metodoForwardEuller(double Si, double ti, double delta, double tf){
	double Si_1;
	double tcorrente = ti;

	while(tcorrente < tf){
		Si_1 = Si + delta*f(Si, tcorrente);
		tcorrente += delta;
		Si = Si_1;
		cout <<"S: " << Si;
	}
	return Si_1;
}

/*double metodoBackwardEuller(double Si, double ti_1, double delta, double tolerancia, double tf){
	double erro = 10;
	double Si_1_barra = Si;
	double Si_1;
	double tcorrente = ti;

	while(tcorrente < tf){
		while(erro > tolerancia){
		Si_1 = Si + delta*f(Si_1_barra, ti_1);
		ti_1 = tcorrente;

		Si_1_barra = Si_1;

		erro = fabs((Si_1 - Si_1_barra)/Si_1);
		}
	}

	return Si_1;
}*/

double RungeKutta2(double Si, double ti, double delta, double tf){
	double Si_1_barra, Si_1;
	double ti_1;
	double tcorrente = ti;

	while(tcorrente < tf){
		Si_1_barra = Si + delta*f(Si, tcorrente);
		ti_1 = tcorrente + delta;

		Si_1 = Si + (delta/2) * (f(Si, tcorrente) + f(Si_1, ti_1));

		Si = Si_1;
		tcorrente += delta;
		cout <<"S: " << Si;
	}

	return Si_1;
}

double RungeKutta3(double Si, double ti, double delta, double tf){
	double Si_1, Si_2, ti_2, ti_1, Si_1_barra;
	double tcorrente = ti;

	while(tcorrente < tf){
		Si_1_barra = Si + delta*f(Si, tcorrente);
		ti_1 = tcorrente + delta;

		Si_2 = Si + (delta/2)*f(Si, tcorrente);
		ti_2 = tcorrente + delta/2;

		Si_1 = Si + (delta/3) * (f(Si, tcorrente) + 2*f(Si_2, ti_2) + f(Si_1_barra, ti_1));

		Si = Si_1;
		tcorrente += delta;
		cout <<"S: " << Si;
	}

	return Si_1;
}

double RungeKutta4(double Si, double ti, double delta, double tf){
	double Si_1, Si_2, ti_2, ti_1, Si_1_barra, Si_3, ti_3;
	double tcorrente = ti;

	while(tcorrente < tf){
		Si_1_barra = Si + delta*f(Si, tcorrente);
		ti_1 = tcorrente + delta;

		Si_2 = Si + (delta/3)*f(Si, tcorrente);
		ti_2 = tcorrente + delta/3;

		Si_3 = Si + ((2*delta)/3)*f(Si, tcorrente);
		ti_3 = tcorrente + (2*delta)/3;

		Si_1 = Si + (delta/8) * (f(Si, tcorrente) + 3*f(Si_2, ti_2) + 3*f(Si_3, ti_3) + 1*f(Si_1, ti_1));;

		Si = Si_1;
		tcorrente += delta;
		cout <<"S: " << Si;
	}

	return Si_1;
}

double PrevisorCorretor2(double Si, double ti, double delta, double tf){
	double Si_1, Si_1_preditor, Si_1_corretor, ti_1; // o Si_1_corretor/preditor era pra ser S2
	double tcorrente = ti;
	while(tcorrente < tf){
		///////// FASE DE PREDIÇÃO
		Si_1 = metodoForwardEuller(Si, tcorrente, delta, tcorrente+delta);
		ti_1 = tcorrente + delta;
		Si_1_preditor = Si + delta*((-1/2)*f(Si, tcorrente) + (3/2)*f(Si_1, ti_1));
		
		///////// FASE DE CORREÇÃO
		Si_1_corretor = Si_1 + delta*((1/2)*f(Si_1, ti_1) + (1/2)*f(Si_1_preditor, ti_1+delta));
		tcorrente += delta;
		Si = Si_1;
		cout << "\nPREDITOR: " << Si_1_preditor;
		cout << "\nCORRETOR: " << Si_1_corretor;
	}
	
	return Si_1_corretor;
} // ok

double PrevisorCorretor3(double Si, double ti, double delta, double tf){
	double Si_1, Si_2, Si_2_preditor, Si_2_corretor, ti_1, ti_2;
	double tcorrente = ti;
	while(tcorrente < tf){
		///////// FASE DE PREDIÇÃO
		ti_1 = tcorrente + delta;
		ti_2 = ti_1 + delta;

		Si_1 = metodoForwardEuller(Si, tcorrente, delta, ti_1);
		Si_2 = metodoForwardEuller(Si, tcorrente, delta, ti_2);
		
		Si_2_preditor = Si + (delta/12)*(5*f(Si, tcorrente) - 16*f(Si_1, ti_1) + 23*f(Si_2, ti_2));
		
		///////// FASE DE CORREÇÃO
		Si_2_corretor = Si_1 + (delta/12)*(-1*f(Si_1, ti_1) + 8*f(Si_2, ti_2) + 5*f(Si_2_preditor, ti_2+delta));
		tcorrente = ti_1;
		Si = Si_1;
		cout << "\nPREDITOR: " << Si_2_preditor;
		cout << "\nCORRETOR: " << Si_2_corretor;
	}
	
	return Si_2_corretor;
}

double PrevisorCorretor4(double Si, double ti, double delta, double tf){
	double Si_1, Si_2, Si_3, Si_3_preditor, Si_3_corretor, ti_1, ti_2, ti_3;
	double tcorrente = ti;
	while(tcorrente < tf){
		///////// FASE DE PREDIÇÃO
		ti_1 = tcorrente + delta;
		ti_2 = ti_1 + delta;
		ti_3 = ti_2 + delta;

		Si_1 = metodoForwardEuller(Si, tcorrente, delta, ti_1);
		Si_2 = metodoForwardEuller(Si, tcorrente, delta, ti_2);
		Si_3 = metodoForwardEuller(Si, tcorrente, delta, ti_3);
		
		Si_3_preditor = Si_2 + (delta/ 24.0) * (-9.0 * f(Si, tcorrente) + 37.0 * f(Si_1, ti_1) - 59.0*f(Si_2, ti_2) + 55.0*f(Si_3, ti_3));
		
		///////// FASE DE CORREÇÃO
		Si_3_corretor = Si_3 + (delta / 24.0)*(f(Si_1, ti_1) - 5.0*f(Si_2, ti_2) + 19.0* f(Si_3,ti_3) + 9.0 * f(Si_3_preditor, ti_3 + delta));
		tcorrente = ti_3;
		Si = Si_3;
		cout << "\nPREDITOR: " << Si_3_preditor;
		cout << "\nCORRETOR: " << Si_3_corretor;
	}
	
	return Si_3_corretor;
}

int main(){
	double Si = 2;
	double ti = 0;
	double tf = 0.02;
	double delta = 0.01;
	double valor;

	cout << "\n-------------------------------------------";
	cout << "\n METODO FORWARD EULLER:\n";
	valor = metodoForwardEuller(Si, ti, delta, tf);

	cout << "\n-------------------------------------------";
	cout << "\n METODO RUNGEKUTTA 2:\n";
	valor = RungeKutta2(Si, ti, delta, tf);

	cout << "\n-------------------------------------------";
	cout << "\n METODO RUNGEKUTTA 3:\n";
	valor = RungeKutta3(Si, ti, delta, tf);

	cout << "\n-------------------------------------------";
	cout << "\n METODO RUNGEKUTTA 4:\n";
	valor = RungeKutta4(Si, ti, delta, tf);

	cout << "\n-------------------------------------------";
	cout << "\n METODO PREDITOR CORRETOR 2 PONTOS:\n";
	valor = PrevisorCorretor2(Si, ti, delta, tf);

	cout << "\n-------------------------------------------";
	cout << "\n METODO PREDITOR CORRETOR 3 PONTOS:\n";
	valor = PrevisorCorretor3(Si, ti, delta, tf);

	cout << "\n-------------------------------------------";
	cout << "\n METODO PREDITOR CORRETOR 4 PONTOS:\n";
	valor = PrevisorCorretor4(Si, ti, delta, tf);

	return 0;
}