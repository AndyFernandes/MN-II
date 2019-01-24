/*
void menu(){

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
}*/