/*
peso= principal = matris que te dan
pos= ciudad = lugar visitando
vis= visitados = 0 no visitado, 1 visitado
ady = adyacentes
refe= referencia
en costo agregue el tamaño del arreglo
*/
#include <bitset>
int costo(int peso[][MAXNODOS], int* cam, int tamano){
    int cost = 0;
    for(int i=0;k<tamano-1;i++){
        cost+=principal[cam[i]][cam[i+1]];
    }
    return cost;
}

void anchura(bitset<MAXNODOS> visitados, int ciudad, int* cam, int principal[][MAXNODOS], int referencia, int* optimo, int condicion){
	Cola* adyacentes = new Cola();
	
	if(codicion==0){	//CONDICION: 0 = PARA VOLVER AL MISMO ORIGEN (DESTINO=ORIGEN), 1 = PARA IR A UN DESTINO DISTINTO DE ORIGEN
		int tamano	= MAXNODOS +1;
		condicion=2;
	}else if(condicion==1){
			int tamano	= MAXNODOS;
			visitados[ciudad] = 1;
		}else if(condicion==2){
				int tamano	= MAXNODOS+1;
				visitados[ciudad] = 1;
			}
	
	int camino[tamano];
	cam[referencia] = ciudad;

	for(int a=0;a<tamano;a++)
		camino[a]=cam[a];


	for(int i=0;i<tamano;i++){    //   Recorre los adyacentes a ciudad
		if(principal[ciudad][i]!=INF)		 //   Pregunta si hay camino						 
			adyacentes->encolar(i);		 //	  Encola los adyacentesacentes
	}


	if((ciudad == DESTINO) && (visitados.all())){			 //   Llego a destino y visitadosito todos
        if(costo(principal,cam,tamano) < costo(principal,optimo,tamano))
            for(int a=0;a<tamano;a++)
                optimo[a]=cam[a];
	}


	while(!adyacentes->colavacia()){		 		//Recorre la cola
		if(visitados.test(adyacentes->tope())==0) 	//Si el tope es 0, no esta visitado
			anchura(vis,adyacentes->desencolar(),camino,principal,referencia+1,optimo,condicion); // Llama recursivamente con el primer adyacente de la cola que no esta visitado
		else										//Si ya esta visitado
			adyacentes->desencolar();				//Desencola
	}
	
}
