/*
peso= principal = matris que te dan
pos= ciudad = lugar visitando
vis= visitados = 0 no visitado, 1 visitado
ady = adyacentes
refe= referencia
en costo agregue el tamaño del arreglo
*/

int costo(int matrizCostos[][MAX], int* cam, int tamano){
    int cost = 0;
    for(int i=0;i<tamano-1;i++){
        cost+=matrizCostos[cam[i]][cam[i+1]];
    }
    return cost;
}

//void BusquedaAmplitud(int origen)
//	{
//		if(origen==Destino)
//			
//	}
void anchura(bitset<MAX> visitados, int* cam, int matrizCostos[][MAX], int referencia, int* optimo, int condicion,int ciudad, int destino, int *largo){
	Cola* adyacentes = new Cola();
	int tamano;
	if(condicion==0){	//CONDICION: 0 = PARA VOLVER AL MISMO ORIGEN (DESTINO=ORIGEN), 1 = PARA IR A UN DESTINO DISTINTO DE ORIGEN
		tamano	= MAX +1;
		condicion=2;
	//	cout<<"entre 0";
	}else if(condicion==1){
			tamano	= MAX;
			visitados[ciudad] = 1;
		}else if(condicion==2){
				tamano	= MAX+1;
				visitados[ciudad] = 1;
	//			cout<<"entre 2";
			}
	
	int camino[tamano];
	cam[referencia] = ciudad;

	for(int a=0;a<tamano;a++)
		camino[a]=cam[a];


	for(int i=0;i<MAX;i++){    //   Recorre los adyacentes a ciudad
		if(matrizCostos[ciudad][i]!=INFI)		 //   Pregunta si hay camino						 
			adyacentes->encolar(i);		 //	  Encola los adyacentesacentes
	}


	if((ciudad == destino) && (visitados.all())){			 //   Llego a destino y visitadosito todos
        if(costo(matrizCostos,cam,tamano) < costo(matrizCostos,optimo,*largo)){
        	*largo=tamano;
        	for(int a=0;a<tamano;a++)
                optimo[a]=cam[a];
        }
	}


	while(!adyacentes->colavacia()){		 		//Recorre la cola
		if(visitados.test(adyacentes->tope())==0) 	//Si el tope es 0, no esta visitado
			anchura(visitados,camino,matrizCostos,referencia+1,optimo,condicion,adyacentes->desencolar(),destino,largo); // Llama recursivamente con el primer adyacente de la cola que no esta visitado
		else										//Si ya esta visitado
			adyacentes->desencolar();				//Desencola
	}
	
}



int main(){
	int *pdist, i, j, precede[MAX],s,t, posi[MAX];
	bitset<MAX> visitados;
	
	int cam[MAX+1];
	int optimo[MAX+1];
	int largo= MAX+1;
	for(int i=0;i<MAX+1;i++){
		cam[i]=0;
		optimo[i]=0;
    }
	
	//------------------------------ANCHURA-------------------------
	anchura(visitados,cam,matrizCostos,0,optimo,0,1,1,&largo);
	for(int i=0;i<MAX+1;i++)
		cam[i]=0;
	visitados.reset();
	
	anchura(visitados,cam,matrizCostos,0,optimo,1,2,1,&largo);
	
	for(int i=0;i<MAX+1;i++)
		cam[i]=0;
	visitados.reset();
	
	anchura(visitados,cam,matrizCostos,0,optimo,0,2,2,&largo);
	
	cout<<"Utilizando busqueda por amplitud llego a destino con el menor costo visitando " << largo << " ciudades en el siguiente orden: " <<endl<<" ";
                for(int j=0;j<largo;j++)
                {
                    cout<<" "<<optimo[j]<<" ";           // Muestra el camino
                }
                cout<<endl;
    cout<<"El costo del camino es: "<<costo(matrizCostos,optimo, largo)<<endl;
    cout<<endl;
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
