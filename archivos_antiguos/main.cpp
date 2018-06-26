#include <iostream>
#include <bitset>
#include <cstdlib>
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
class Pila:public Lista{
    public:
	    Pila(){Lista();};
	    void apilar(tipodato x){add(x);};
	    tipodato tope(){return cabeza();};
	    tipodato desapilar(){return del();};
	    bool pilavacia(){return esvacia();};
};

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
    cout<<" Error, Cabeza de lista vacia"<<endl;
    return 0;
  }
  return czo->get_dato();
}

Lista *Lista::resto(void){
	Lista *l=new Lista(czo->get_next());
	return (l);
}

void Lista::concat(Lista *l1)
{// le transfiere los datos de l1 a this
   if (!(l1->esvacia())){
      this->concat(l1->resto());
      this->add(l1->cabeza());
   }
}

void Lista::borrar(void)
{ //borra el nodo cabeza
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

//string Cola::imprimir(string s){
//	return this->toPrint(s);
//}

//void MultiLatina(Lista *M[MAX][MAX], Lista *MR[MAX][MAX]){
//    for(int i=0;i<MAX;i++){
//       for(int j=0;j<MAX;j++){
//		    M[i][j]->add(MatrizAdy[i][j]);
//		    MR[i][j]->add(MatrizAdy[i][j]);
//		    if(M[i][j]->cabeza() !=  INFI && MR[i][j]->cabeza() != INFI){
//		        MR[i][j]->concat(M[i][j]);
//		    }else{
//				MR[i][j]->set_valor(INFI);
//			}
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


