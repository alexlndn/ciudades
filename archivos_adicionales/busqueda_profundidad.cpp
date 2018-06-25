// pagina 217 Alfred V. Aho  1988 Addison Wesley
// Busqueda en Profundidad
#include <cstdlib>
#include <iostream>
#define INFI  9000
#define MAXNODOS  5
#define no_visitado 0
#define visitado 1


void BPF(int v, int peso[][MAXNODOS], int marca[]);

using namespace std;

int main(int argc, char *argv[])
{   int peso[MAXNODOS][MAXNODOS]={INFI, INFI,    1,    1, INFI,
                                  INFI, INFI,    1, INFI, INFI,
                                     1,    1, INFI,    1,    1,
                                     1, INFI,    1, INFI,    1,
                                  INFI, INFI,    1,    1, INFI      
                                 };
    int marca[MAXNODOS];

    int i, j, v, s,t;
    
    for(i=0;i<MAXNODOS;i++) marca[i]=no_visitado;
    
    for(v=0;v<MAXNODOS;v++){
        if (marca[v]==no_visitado)
			BPF(v,peso,marca);
    }                
  
    cout<<endl<<"Matriz de pesos";   
    for(i=0;i<MAXNODOS;i++){
           cout<<"\n";                 
           for(j=0;j<MAXNODOS;j++){
                  printf(" %5i",peso[i][j]);                 
           }                 
    }
    cout<<endl<<"Arreglo de marcas"<<endl;   
    for(i=0;i<MAXNODOS;i++){
            cout<<i<<"  "<<marca[i]<<endl;                 
    }
    cout<<endl<<endl<<endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}

void BPF(int v, int peso[][MAXNODOS], int marca[]){
   int w;
   marca[v]=visitado;
   cout<<"v="<<v<<endl;
   for(w=0;w<MAXNODOS;w++){
       if((peso[v][w]==1)&&(marca[w]==no_visitado))
	   		BPF(w,peso,marca);
   }      
}


