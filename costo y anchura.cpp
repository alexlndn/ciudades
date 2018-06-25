/*
peso= principal = matris que te dan
pos= ciudad = lugar visitando
vis= visitados = 0 no visitado, 1 visitado
ady = adyacentes
refe= referencia
en costo agregue el tamaño del arreglo
*/
#define MAX 8

int costo(int peso[][MAX], int* cam, int tamano){
    int cost = 0;
    for(int i=0;i<tamano-1;i++){
        cost+=matrizCostos[cam[i]][cam[i+1]];
    }
    return cost;
}

void anchura(bitset<MAX> visitados, int ciudad, int* cam, int matrizCostos[][MAX], int referencia, int* optimo, int condicion){
	Cola* adyacentes = new Cola();
	int tamano;
	if(condicion==0){	//CONDICION: 0 = PARA VOLVER AL MISMO ORIGEN (DESTINO=ORIGEN), 1 = PARA IR A UN DESTINO DISTINTO DE ORIGEN
		tamano	= MAX +1;
		condicion=2;
	}else if(condicion==1){
			tamano	= MAX;
			visitados[ciudad] = 1;
		}else if(condicion==2){
				tamano	= MAX+1;
				visitados[ciudad] = 1;
			}
	
	int camino[tamano];
	cam[referencia] = ciudad;

	for(int a=0;a<tamano;a++)
		camino[a]=cam[a];


	for(int i=0;i<tamano;i++){    //   Recorre los adyacentes a ciudad
		if(matrizCostos[ciudad][i]!=INFI)		 //   Pregunta si hay camino						 
			adyacentes->encolar(i);		 //	  Encola los adyacentesacentes
	}


	if((ciudad == DESTINO) && (visitados.all())){			 //   Llego a destino y visitadosito todos
        if(costo(matrizCostos,cam,tamano) < costo(matrizCostos,optimo,tamano))
            for(int a=0;a<tamano;a++)
                optimo[a]=cam[a];
	}


	while(!adyacentes->colavacia()){		 		//Recorre la cola
		if(visitados.test(adyacentes->tope())==0) 	//Si el tope es 0, no esta visitado
			anchura(visitados,adyacentes->desencolar(),camino,matrizCostos,referencia+1,optimo,condicion); // Llama recursivamente con el primer adyacente de la cola que no esta visitado
		else										//Si ya esta visitado
			adyacentes->desencolar();				//Desencola
	}
	
}
