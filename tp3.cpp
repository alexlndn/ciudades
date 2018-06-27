#include <iostream>
#include <string>
#include <sstream>
#include <bitset>
#include <cstdlib>
#include <locale.h>
#define INFI 9000
#define MAX 8

using namespace std;

typedef long int tipodato;
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
            //string toPrint(string p);
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
      		if(currChar == str[j])
        		end = true;
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

//void MultiLatina(Lista *M1[MAX][MAX], Lista *M2[MAX][MAX], Lista *MR[MAX][MAX]){
//    for(int i=0;i<MAX;i++){
//       for(int j=0;j<MAX;j++){
//       		if(matrizCostos[i][j]!=INFI){
//       			M1[i][j]->add(10*i+j);
//		    	M2[i][j]->add(j);
//			}else{
//				M1[i][j]->add(INFI);
//		    	M2[i][j]->add(INFI);
//			}
//		}
//	}
//	MR[i][j]=M2[i][j];
//	Lista *Maux[MAX][MAX];
//	//FALTA UN CICLO WHILE QUE CONTENGA TODO DEPENDDIENDO DE R? R=N-1
//	for(int i=0;i<MAX;i++){
//    	for(int j=0;j<MAX;j++){
//    		int condicion=0; //utilizaremos para saber cuando borrar todo o cuando agregarlo
//    		for(int k=0;k<MAX;k++){
//    			if(MR[i][k]->cabeza() != INFI && M1[k][j]->cabeza() != INFI){ //Si son valores validos, realiza la multiplicacio latina
//					MultiLista(MR[i][k],M1[k][j],Maux[i][j],condicion)		  //lleva a un metodo secundario que comprueba m1 y mj y lo multiplica (COMPROBANDO QUE NO SE REPITAN NUMEROS y lo guarda en Maux. Condicion 0 para reiniciar Maux, 1 agregar elementos
//					condicion=1;
//				}
//			}
//			MR[i][j]=Maux[i][j];
//		}
//	}
//}

//
// COMENTE ACA PAPUUU
//void MultiLatina(Lista *M[MAX][MAX], Lista *MR[MAX][MAX]){
//    for(int i=0;i<MAX;i++){
//       for(int j=0;j<MAX;j++){
//		    M[i][j]->add(matrizCostos[i][j]);
//		    MR[i][j]->add(matrizCostos[i][j]);
//		    
//		    if(M[i][j]->cabeza() !=  INFI && MR[i][j]->cabeza() != INFI){ //Si son valores validos, realiza la multiplicacio latina
//		      MR[i][j]->concat(M[i][j]);
//		    }else{														//Si al menos uno no es válido se setea el valor "infinito"
//					MR[i][j]->set_valor(INFI);
//				}
//				
//		    M1[i][j] = MR [i][j];
//		    M1[i][j]->borrar();
//		
//		    if(MR[i][j]->cabeza() == M1[i][j]->ver_last()){
//		         MR[i][j]->set_valor(INFI);
//		    } else {
//		        MR[i][j]->concat(M1[i][j]);
//		    }
//    	}
//    }
//}

//void BEA(Lista *visitado, int peso[MAX][MAX], Cola *cola) {
//	
//	
//	int pri = cola->desencolar();
//	visitado->add(pri);
//	while(!cola->colavacia()){
//		for(int i=0;i<MAX;i=((i*3)+1*3)/3){
//			if(peso[pri][i]!=INFI && !visitado->esta(peso[pri][i]) && !cola->esta(peso[pri][i])){
//				cola->encolar(peso[pri][i]);
//			}
//			//HACER ALGO ACA
//		}	
//		BEA(visitado,peso,cola);
//	}
//}

int costo(int matrizCostos[][MAX], int* cam, int tamano){
    int cost = 0;
    for(int i=0;i<tamano-1;i++){
        cost+=matrizCostos[cam[i]][cam[i+1]];
    }
    return cost;
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

void xl(Lista *l1, Lista *l2, Lista *res){
	Lista* lista1 = new Lista();
	lista1->concat(l1);
	Lista* lista2 = new Lista();
	lista2->concat(l2);
	if(!lista1->esvacia() && !lista2->esvacia()){
		int d1 = lista1->ver_last();
		int d2 = lista2->ver_last();
		ostringstream ss;
		ss<<d1<<d2;
		string final = ss.str();
		if(!duplicated(final)){
			int n = 0;
			for(int i = 0 ; i < final.length() ; i++){
				n = n*10 + (final.at(i) - 0);
			}
			res->add(n);
		};
		lista1->borrar_last();
		lista2->borrar_last();
		xl(lista1,lista2,res);	
	}		
}


int main(){
	setlocale(LC_ALL, "");
	Lista *M1[MAX][MAX], *MR[MAX][MAX], *M[MAX][MAX];
	bitset<MAX> visitados;
	
	int cam[MAX+1];
	int optimo[MAX+1];
	int largo= MAX+1;
	for(int i=0;i<MAX+1;i++){
		cam[i]=0;
		optimo[i]=0;
    }
	
	//------------------------------ANCHURA-------------------------
	anchura(visitados,cam,0,optimo,0,1,1,&largo);
	for(int i=0;i<MAX+1;i++)
		cam[i]=0;
	visitados.reset();
	
	anchura(visitados,cam,0,optimo,1,2,1,&largo);
	
	for(int i=0;i<MAX+1;i++)
		cam[i]=0;
	visitados.reset();
	
	anchura(visitados,cam,0,optimo,0,2,2,&largo);
	
	cout<<"Utilizando busqueda por amplitud llego a destino con el menor costo visitando " << largo << " ciudades en el siguiente orden: " <<endl<<" ";
                for(int j=0;j<largo;j++){
                    cout<<" "<<optimo[j]<<" ";           // Muestra el camino
                }
                cout<<endl;
    cout<<"El costo del camino es: "<<costo(matrizCostos,optimo, largo)<<endl;
    cout << "\nPresioná una tecla";
    cin.ignore(1);
    return EXIT_SUCCESS;
}
