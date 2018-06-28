#include <iostream>
#include <string>
#include <sstream>
#include <bitset>
#include <cstdlib>
#include <locale.h>
#include <sstream>
#define INFI 9000
#define MAX 8

using namespace std;

typedef long long int tipodato;
//--------------- Clase Nodo ---------------
class Nodo{
    protected:
        tipodato dato;
        Nodo *next;
    public:
        Nodo() {next=NULL;};
        Nodo(tipodato a) {dato=a; next=NULL;};
        void set_dato(tipodato a) {dato=a; };
        void set_next(Nodo *n) {next=n; };
        tipodato get_dato() {return dato; };
        Nodo *get_next() {return next; };
        bool es_vacio() {return next==NULL;}
};
//--------------- Clase Lista ---------------
class Lista{
    protected: Nodo *czo;
    		
    public:
            Lista() {czo=NULL;};
            Lista(Nodo *n) {czo=n;};
            tipodato del();
            void add(tipodato d);
            bool esvacia();
            void borrar();
            void borrar_last();
            int last();
            tipodato cabeza();
            Lista *resto();
            string toPrint(string fin);
            void concat(Lista *l1);
            tipodato ver_last();
            void set_valor(tipodato a);
            int size();
            

};

//--------------- Metodos de Lista ---------------
int Lista::size(){
    if (this->esvacia()) return 0;
    return 1+this->resto()->size();
}

tipodato Lista::del(void){
    Nodo *aux;
    aux=czo;
    czo=czo->get_next();
    return aux->get_dato();
}

void Lista::add(tipodato d){
    Nodo *nuevo=new Nodo(d);
    nuevo->set_next(czo);
    czo=nuevo;
}

bool Lista::esvacia(void){
    return !czo;
}

tipodato Lista::cabeza(void){
  if(esvacia()){
    cout<<" Error, Cabeza de lista vacia\n"<<endl;
    return 0;
  }
  return czo->get_dato();
}

Lista *Lista::resto(void){
	Lista *l=new Lista(czo->get_next());
	return (l);
}

// le transfiere los datos de l1 a this
void Lista::concat(Lista *l1){
   if (!(l1->esvacia())){
      this->concat(l1->resto());
      this->add(l1->cabeza());
   }
}

//borra el nodo cabeza
void Lista::borrar(void){
  if(esvacia()){
  } else {
    Nodo *tmp=czo;
    czo=czo->get_next();
    delete tmp;
  }
}

void Lista::borrar_last(){
   if(!this->esvacia()){
   	if(czo->get_next()==NULL){
   		this->borrar();
	   }
	   else if((czo->get_next())->get_next()==NULL){
         delete czo->get_next();
         czo->set_next(NULL);
      	}
      	else this->resto()->borrar_last(); 
   }
}

int Lista::last(){
 if(!this->esvacia()){
    if(this->resto()->esvacia())return this->cabeza();
    return this->resto()->last();
  }return 0;
}

tipodato Lista::ver_last(){ // ver el ultimo nodo
   if(!this->esvacia()){
      if((czo->get_next())->get_next()==NULL){
		czo->get_next();
		return czo->get_dato();
      }
      else this->resto()->ver_last();
   }
}

void Lista::set_valor(tipodato a){
    Nodo *aux;
    aux = czo;
    aux->set_dato(a);
}

string Lista::toPrint(string fin){
	if(this->esvacia()){
		return "- " + fin + "";
	}else{
		ostringstream m;
		m << this->cabeza();
		m << " \n ";
		m << this->resto()->toPrint("");
		return m.str();
	}
}

//--------------- Clase Cola ---------------
class Cola:public Lista{
  public:
      Cola(void){Lista();};
      ~Cola(void);
      tipodato tope();
      bool colavacia(){this->esvacia();};
      void encolar(tipodato a) ;
      void eliminar();
      tipodato desencolar();
      tipodato ultimo();
      //string imprimir(string s);
};
//--------------- Metodos de Cola ---------------
tipodato Cola::tope(void){
	return this->last();
}

void Cola::encolar(tipodato a){
	this->add(a);
}

tipodato Cola::desencolar(void){
	tipodato temp= tope();
	this->borrar_last();
	return temp;
}

tipodato Cola::ultimo(void){
	return this->cabeza();
}


bool duplicated(std::string& str){
  	bool end = false;
  	int length = str.length();
  	for(unsigned int i = 0; i < length; i++){
    	char currChar = str[i];
    	for(unsigned int j = i+1; j < length; j++){
      		if(currChar == str[j]){
				  end = true;
			  }
        		
    	}
  	}
  	return end;
}
int matrizCostos[MAX][MAX]={
	INFI,	 150,	 180,	 210,	 340,	 310,	 280,	 600,
	 150,	INFI,	 220,	 200,	 350,	 290,	 220,	 590,
	 180,	 220,	INFI,	 350,	 440,	 240,	 200,	 700,
	 210,	 200,	 350,	INFI,	  95,    180,	 200,	 500,
	 340,	 350,	 440,	 95,	INFI,	 300,	 180,	 800,
	 310,	 290,	 240,	 180,	 300,	INFI,	 150,	 240,
	 280,	 220,	 200,	 200,	 180,	 150,	INFI,	 780,
	 600,	 590,	 700,	 500,	 800,	 240,	 780,	INFI
};

string Conversion(int a){
	switch(a){
		case 0:
			return "Madrid";
		case 1:
			return "Barcelona";
		case 2:
			return "Roma";
		case 3:
			return "Paris";
		case 4:
			return "Londres";
		case 5:
			return "Berlin";
		case 6:
			return "Amsterdam";
		case 7:
			return "Moscu";
		default:
			return "";	
	}
}

Lista *Maux[MAX][MAX];

int costo(int matrizCostos[][MAX], int* cam, int tamano){
    int cost = 0;
    for(int i=0;i<tamano-1;i++){
        cost+=matrizCostos[cam[i]][cam[i+1]];
    }
    return cost;
}

void MultiplicacionCorta(Lista *l1, Lista *l2, int condicion, int i, int j){
	if(!l1->esvacia()){
		if(!condicion){
			//delete Maux[i][j];
			Maux[i][j]=new Lista();
		}
//		Lista* listaaux1 = new Lista();
//		listaaux1->concat(l1);
		Lista* lista1 = new Lista();
		lista1->concat(l1);
		//delete [] listaaux1;
	
		if(!lista1->esvacia()){
			tipodato d1 = lista1->cabeza();
			tipodato d2 = l2->cabeza();
			ostringstream ss;
			ss<<d1;
			ostringstream sd;
			sd<<d2;
			string final="";
			string final1 = ss.str();
			string final2 = sd.str();
			if(final1.at(final1.length()-1)==final2.at(0)){
				final1.erase(final1.length()-1,1);
				final=final1+final2;
				if(!duplicated(final)){
					int n = 0;
					for(int h = 0 ; h < final.length() ; h++){
						n = n*10 + (final.at(h) - '0');
					}
					Maux[i][j]->add(n);
				}
			}
		}
		lista1->borrar();
		MultiplicacionCorta(lista1,l2, condicion,i,j);	
	}
}

void MultiplicacionLarga(Lista *l1, Lista *l2, int condicion,int i,int j){
	if(!l1->esvacia() && !l2->esvacia()){
		if(!condicion){
			Maux[i][j]=new Lista();
		}
		
		Lista* lista1 = new Lista();
		lista1->concat(l1);
		
		Lista* lista2 = new Lista();
		lista2->concat(l2);
		if(!lista1->esvacia() && !lista2->esvacia()){
			int d1 = lista1->cabeza();
			for(int k=0; k<lista2->size();k++){
				int d2 = lista2->cabeza();
				ostringstream ss;
				ss<<d1;
				ostringstream sd;
				sd<<d2;
				string final="";
				string final1 = ss.str();
				string final2 = sd.str();
				if(final1.at(final1.length()-1)==final2.at(0)){
					final1.erase(final1.length()-1,1);
					final=final1+final2;
					if(!duplicated(final)){
						int n = 0;
						for(int h = 0 ; h < final.length() ; h++){
							n = n*10 + (final.at(h) - '0');
						}
						Maux[i][j]->add(n);
					}
				}
				lista2->borrar();
			}
			lista1->borrar();
			Lista* lista2 = new Lista();
			lista2->concat(l2);
			MultiplicacionLarga(lista1,lista2, condicion,i,j);	
		}
	}
}

void MultiLatina(Lista *M1[MAX][MAX], Lista *M2[MAX][MAX], Lista *MR[MAX][MAX]){
    //Guardamos en M1 los caminos elementales de orden uno
	for(int i=0;i<MAX;i++){
       for(int j=0;j<MAX;j++){
       		if(matrizCostos[i][j]!=INFI){
       			M1[i][j]->add(10*(i+1)+j+1);
       			M2[i][j]->add(j);
			}else{
				M1[i][j]->add(INFI);
				M2[i][j]->add(INFI);
			}
		}
	}
	
	//Se setea la matriz resultante de grado 1
	for(int i=0;i<MAX;i++){
		for(int j=0;j<MAX;j++){
			MR[i][j]=M1[i][j];
		}
	}
	
	int condicion;
	//calculamos la matriz de grado 2
	for (int r = 1 ; r < MAX-1 ; r++){
		for(int i=0;i<MAX;i++){
    		for(int j=0;j<MAX;j++){
    			condicion=0; //utilizaremos para saber cuando borrar todo o cuando agregarlo
    			for(int k=0;k<MAX;k++){
    				if(MR[i][k]->cabeza() != INFI && M1[k][j]->cabeza() != INFI){ //Si son valores validos, realiza la multiplicacio latina
						MultiplicacionCorta(MR[i][k],M1[k][j],condicion,i,j)	;	  //lleva a un metodo secundario que comprueba m1 y mj y lo multiplica (COMPROBANDO QUE NO SE REPITAN NUMEROS y lo guarda en Maux. Condicion 0 para reiniciar Maux, 1 agregar elementos
						condicion=1;
					}
				}
			}
		}
		// Despues de realizar todos los calculos necesarios
		// Seteamos la matriz resultante del nuevo grado
		
		for(int k=0;k<MAX;k++){
			for(int x=0;x<MAX;x++){
				if(Maux[k][x]->esvacia()){
					MR[k][x]->set_valor(INFI);
				}else{
					MR[k][x]=Maux[k][x];
				}
			}
		}
	}

}


void BuscarCaminoMasCortito(Lista *Mfinal[MAX][MAX], int origen, int destino, int *Optima){
	int Actual[MAX];
	for(int i=0;i<MAX;i++){
		Actual[i]=0;
	}
	Lista *A = new Lista();
	A->concat(Mfinal[origen][destino]);
	while(!A->esvacia()){	
		ostringstream numero;
		numero<< A->cabeza();
		A->borrar();
		string stringnumero = numero.str();
		for(int j=0;j<stringnumero.length();j++){
				Actual[j]=(stringnumero.at(j)-'0')-1;
		}
		if(costo(matrizCostos,Actual,MAX) < costo(matrizCostos,Optima,MAX)){
			for(int a=0;a<MAX;a++)
                Optima[a]=Actual[a];
		}
	}
	Lista *B=new Lista();
	B->concat(Mfinal[destino][origen]);	
	while(!B->esvacia()){	
		ostringstream numero;
		numero<< B->cabeza();
		B->borrar();
		string stringnumero = numero.str();
		int r=0;
		for(int j=stringnumero.length()-1;j>=0;j--){
				Actual[r]=(stringnumero.at(j)-'0')-1;
				r++;
		}
		if(costo(matrizCostos,Actual,MAX) < costo(matrizCostos,Optima,MAX)){
			for(int a=0;a<MAX;a++)
                Optima[a]=Actual[a];
		}
	}
}



void anchura(bitset<MAX> visitados, int* cam, int referencia, int* optimo, int condicion,int ciudad, int destino, int *largo){
	Cola* adyacentes = new Cola();
	int tamano;
	
	//Condicion 0: origen = destino
			// en la condicion 0 no se guarda como visitada la primer ciudad
			// en la proxima iteracion entra en condicion 2
	//Condicion 1: origen != destino
	//Condicion 2: origen = destino, se guarda el visitado
	if(condicion==0){	
		tamano = MAX + 1;
		condicion = 2;
	}else if(condicion==1){
		tamano = MAX;
		visitados[ciudad] = 1;
	}else if(condicion==2){
		tamano = MAX + 1;
		visitados[ciudad] = 1;
	}
	
	int camino[tamano];
	cam[referencia] = ciudad;

	for(int a=0;a<tamano;a++)
		camino[a]=cam[a];


	for(int i=0;i<MAX;i++){    //   Recorre los adyacentes a ciudad
		if(matrizCostos[ciudad][i]!=INFI)		 //   Pregunta si hay camino						 
			adyacentes->encolar(i);		 //	  Encola los adyacentes
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
			anchura(visitados,camino,referencia+1,optimo,condicion,adyacentes->desencolar(),destino,largo); // Llama recursivamente con el primer adyacente de la cola que no esta visitado
		else										//Si ya esta visitado
			adyacentes->desencolar();				//Desencola
	}
	
}

int main(){
	setlocale(LC_ALL, "");
	cout << "*\t ALGORITMO DE RECORRIDO DE UN GRAFO\t*\n\n";
	cout << "# POSIBLES PARTIDAS: " << Conversion(1) << " | " << Conversion(2) << endl;
	cout << "# POSIBLES DESTINOS: " << Conversion(1) << " | " << Conversion(2) << endl << endl;
	
	Lista *M1[MAX][MAX], *M2[MAX][MAX], *MR[MAX][MAX];
	bitset<MAX> visitados;
	
	for(int i = 0 ; i < MAX ; i++){
		for(int j = 0 ; j < MAX ; j++){
			M1[i][j] = new Lista();
			M2[i][j] = new Lista();
			MR[i][j] = new Lista();
		}
	}
	
	int cam[MAX+1];
	int optimo[MAX+1];
	int largo= MAX+1;
	for(int i=0;i<MAX+1;i++){
		cam[i]=0;
		optimo[i]=0;
    }
    
    for(int i = 0 ; i < MAX ; i++){
		for(int j = 0 ; j < MAX ; j++){
			Maux[i][j] = new Lista();
		}
	}
    //-------------------------------------------------------------
    cout<<"ALGORITMO DE KAUFMANN y MALGRANGE:"<<endl;   
    MultiLatina(M1, M2, MR);
    int CamHamiltoniano[MAX]={0,0,0,0,0,0,0,0};
	BuscarCaminoMasCortito(MR, 1, 2, CamHamiltoniano);
	cout<<"Llego a destino, con el menor costo, visitando todas las ciudades en el siguiente orden: " <<endl<<" ";
	for(int j=0;j<MAX;j++){
        cout <<Conversion(CamHamiltoniano[j]);
		if(j != MAX-1){
			cout << " --> ";
		}
    }
    cout << ". El costo total es de " << costo(matrizCostos, CamHamiltoniano ,MAX) << endl;
	
	//------------------------------ANCHURA-------------------------
	cout<<endl<<"ALGORITMO DE BUSQUEDA EN AMPLITUD:"<<endl;
	anchura(visitados,cam,0,optimo,0,1,1,&largo);
	for(int i=0;i<MAX+1;i++)
		cam[i]=0;
	visitados.reset();
	
	anchura(visitados,cam,0,optimo,1,1,2,&largo);
	
	for(int i=0;i<MAX+1;i++)
		cam[i]=0;
	visitados.reset();
	
	anchura(visitados,cam,0,optimo,0,2,2,&largo);
	
	cout<<"Llego a destino, con el menor costo, visitando todas las ciudades en el siguiente orden: " <<endl<<" ";
                for(int j=0;j<largo;j++){
                    cout << Conversion(optimo[j]);
                    if(j != largo-1){
						cout << " --> ";
					}
                }
    cout << ". El costo total es de " << costo(matrizCostos,optimo, largo)<<endl;
    cout << "\nPresioná una tecla";
    cin.ignore(1);
    return EXIT_SUCCESS;
}
