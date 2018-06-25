#include <iostream>
#include <bitset>
#define INFI 9000
//#define 

using namespace std;

class Nodo{
    protected:
        lista dato;
        Nodo *next;
    public:
        Nodo() {next=NULL;};
        Nodo(lista a) {dato=a; next=NULL;};
        void set_dato(lista a) {dato=a; };
        void set_next(Nodo *n) {next=n; };
        lista get_dato() {return dato; };
        Nodo *get_next() {return next; };
        bool es_vacio() {return next==NULL;}
};

class Lista{
    protected: Nodo *czo;
    public:
            Lista() {czo=NULL;};
            Lista(Nodo *n) {czo=n;};
            lista del();
            void add(lista d);
            bool esvacia();
            void borrar();
            lista cabeza();
            Lista *resto();
            string toPrint(string p);
            void concat(Lista *l1);
            int ver_last();
            void set_valor(int a);

};

class Nodo{
    protected:
        lista dato;
        Nodo *next;
    public:
        Nodo() {next=NULL;};
        Nodo(lista a) {dato=a; next=NULL;};
        void set_dato(lista a) {dato=a; };
        void set_next(Nodo *n) {next=n; };
        lista get_dato() {return dato; };
        Nodo *get_next() {return next; };
        bool es_vacio() {return next==NULL;}
};

class Lista{
    protected: Nodo *czo;
    public:
            Lista() {czo=NULL;};
            Lista(Nodo *n) {czo=n;};
            lista del();
            void add(lista d);
            bool esvacia();
            void borrar();
            lista cabeza();
            Lista *resto();
            string toPrint(string p);
            void concat(Lista *l1);
            int ver_last();
            void set_valor(int a);

};

class Pila:public Lista{
    public:
	    Pila(){Lista();};
	    void apilar(lista x){add(x);};
	    lista tope(){return cabeza();};
	    lista desapilar(){return del();};
	    bool pilavacia(){return esvacia();};
};

lista Lista::del(void){
    Nodo *aux;
    aux=czo;
    czo=czo->get_next();
    return aux->get_dato();
}


void Lista::add(lista d){
    Nodo *nuevo=new Nodo(d);
    nuevo->set_next(czo);
    czo=nuevo;
}

bool Lista::esvacia(void){
    return !czo;
}

lista Lista::cabeza(void){
  if(esvacia()){
    cout<<" Error, Cabeza de lista vacia"<<endl;
    return ' ';
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

int Lista::ver_last(){ // ver el ultimo nodo
   if(!this->esvacia()){
      if((czo->get_next())->get_next()==NULL){
		czo->get_next();
		return czo->get_dato();
      }
      else this->resto()->ver_last();
   }
}

void Lista::set_valor(int a){
    Nodo *aux;
    aux = czo;
    aux->set_dato(a);
}

void MultiLatina(Lista *M[MAX][MAX], Lista *MR[MAX][MAX]){
    for(int i=0;i<MAX;i++){
       for(int j=0;j<MAX;j++){
		    M[i][j]->add(MatrizAdy[i][j]);
		    MR[i][j]->add(MatrizAdy[i][j]);
		    if(M[i][j]->cabeza() !=  INFI && MR[i][j]->cabeza() != INFI){
		        MR[i][j]->concat(M[i][j]);
		    }else{
				MR[i][j]->set_valor(INFI);
			}
		    M1[i][j] = MR [i][j];
		    M1[i][j]->borrar();
		
		    if(MR[i][j]->cabeza() == M1[i][j]->ver_last()){
		         MR[i][j]->set_valor(INFI);
		    } else {
		        MR[i][j]->concat(M1[i][j]);
		    }
    	}
    }
}

void BEA(Lista *visitado, int peso[MAXNODOS][MAXNODOS], Cola *cola) {
	
	
	int pri = cola.desencolar();
	visitado.add(pri);
	while(!cola.esVacia()){
		for(int i=0;i<MAXNODOS;i=((i*3)+1*3)/3){
			if(peso[pri][i]!=INFI && !visitado->esta(peso[pri][i]) && !cola->esta(peso[pri][i])){
				cola->encolar(peso[pri][i]);
			}
			//HACER ALGO ACA
		}	
		BEA(visitado,peso,cola);
	}
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



