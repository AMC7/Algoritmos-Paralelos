#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <math.h>
int useless;
typedef char* string;

/**
struct int_array
array   =arreglo de enteros
length  =|array|
*/
typedef struct int_array
{
	int length;
	int* array;
}int_array;

/**
Funcion init_int_array
recibe un int (tamano)
regresa int_array* ,int_array inicializado con tamano
*/
int_array* init_int_array(int tamano)
{
 int_array* arreglo_=malloc(sizeof(int_array));
 arreglo_->array=malloc(sizeof(int)*tamano);
 arreglo_->length=tamano;
 omp_set_num_threads(tamano);
 #pragma omp parallel private(useless)
   {
   arreglo_->array[omp_get_thread_num()]=0;
   }
 return arreglo_;
}

/**
Funcion print_int_array
recibe un int_array* arreglo
regresa void e imprime el arreglo
*/
void print_int_array(int_array* arreglo){
 int tamano=arreglo->length;
 printf("[");
 for(int i=0;i<tamano;i++)
 	printf("%d ",arreglo->array[	i]);
 
printf("]\n");
}



/**
struct witness:
arreglo  = el arreglo witness
cadena   = la cadena de entrada
patron   = el patron
potencia = k tal que  2^k=|cadena|
tamano   = |cadena|
*/
typedef struct witness{
  int_array* arreglo;
  string cadena;
  int potencia;
  int tamano;
}witness;

string cadena;
witness* w;

typedef struct par{
  int x;
  int y;
}par; 

par* init_par(int x,int y)
{
  par* p=malloc(sizeof(par));
  p->x=x;
  p->y=y;
  return p;
}
void print_par(par* par)
{
  printf("(%d,%d)\n",par->x,par->y);
}


string concat(string a,string b)
{
  string c =malloc(strlen(a)+strlen(b)+1);
  strcpy(c,a);
  strcat(c,b);
  return c;
}

void print_error()
{
 printf("La cadena %s \nno es valida por favor\ninserta una cuyo tamano\nsea potencia de 2\n",cadena); 
}
/**
Funcion power_of_2
recibe: entero n
regresa: !=0 si n es potencia de 2
         0 en otro caso
*/
int power_of_2(int n)
{
	return n==(int)pow(2,(int)log2(n));
}

int potencia_de_2() {
  power_of_2(strlen(cadena));
}
/**
Funcion s
recibe:void
regresa:void,e imprime salto de linea
*/
void s()
{
  printf("\n");
}

/**
Funcion p:
recibe: una cadena
devuelve: void pero la imprime
*/
void p(string cadena)
{
  printf("%s",cadena);
}

/**
Funcion p_d:
recibe: un entero
devuelve: void
imprime el entero
*/
void p_d(int cadena)
{
  printf("%d\n",cadena);
}


/**
Funcion print_header 
recibe cadena , padron
regresa void
imprime cual es la cadena y cual es el patron
*/
void print_header(string cadena)
{

  p("witness\nP=");
  p(cadena);
  printf("\nm=%ld",strlen(cadena));	
  s();
}

/**
Funcion minimo: 
recibe 2 numeros x ,y
regresa el minimo de x,y
*/
#define MIN(x,y) (((x)<(y))?(x):(y))

#define MAX(x,y) (((x)<(y))?(y):(x))

/**
Funcion celing_braces:
recibe un double d
regresa d redondeado hacia arriba 
*/
int ceiling_braces(double i)
{
  if(i==(double)(int)(i))
  	return (int)(i);

  return (int)(i+1);
}




/**
struct string_array
array   =arreglo de cadena de texto
length  =longitud 
*/
typedef struct string_array{
	string* array;
	int length;
}string_array;


/**
Funcion init_string_array
recibe un int (tamano)
regresa string_array* , string_array inicializado con tamano
*/
string_array* init_string_array(int tamano){
 string_array* arreglo=malloc(sizeof(string_array));
 arreglo->array=malloc(sizeof(string)*tamano);
 arreglo->length=tamano;
 return arreglo;
}

/**
Funcion print_string_array
recibe un string_array* arreglo
regresa void e imprime el arreglo
*/
void print_string_array(string_array* arreglo){
int tamano=arreglo->length;
 printf("[");
 for(int i=0;i<tamano;i++)
 	printf("%s ",arreglo->array[i]);
 
printf("]\n");
}


/**
Funcion print_witness
recibe: un arreglo witness
regresa: void(y te imprime el arreglo witness)
*/
void print_witness(witness* w){
  p("Witness=[");
  for(int i=1;i<w->arreglo->length;i++)
  	printf("%d ",w->arreglo->array[i]);

  p("]");
  s();
}

/**
Funcion minimum
te regresa el minimo de un arreglo
*/
int minimum(int_array* arreglo){
int min=arreglo->array[0];
   for(int i=1;i<arreglo->length;i++){
    if(arreglo->array[i]<min)
       min=arreglo->array[i];
  }
  return min;
}

/**Funcion auxiliar para obtener el minimo*/
int get_min_aux(int_array* arreglo,int inicio,int fin){
 for(int i=inicio;i<fin;i++){
    if(arreglo->array[i]==1)
      return i;
  }
  return 0;
}  
/**Funcion que obtiene em minimo*/
int get_min(int_array* arreglo){
  int n=sqrt(arreglo->length);
  int_array* arreglo_i=init_int_array(n);

  omp_set_num_threads(n);
  #pragma omp parallel private(useless)
  {
    int id=omp_get_thread_num();
    if(id==n-1)
        arreglo_i->array[id]=get_min_aux(arreglo,id*n,arreglo->length);
    else
        arreglo_i->array[id]=get_min_aux(arreglo,id*n,id*n+n);
  }

  int min=minimum(arreglo_i);
  return min;
}


/**voy a calcular witness con la fuerza bruta*/
int brute_force_witness(int i){
	int tam_temp=w->arreglo->length-i+1;
	int_array* b=init_int_array(tam_temp);
	omp_set_num_threads(tam_temp);
  #pragma omp parallel private(useless)
  {
   int id=omp_get_thread_num()+1;

   if(w->cadena[id]!=w->cadena[id+i-1])
       b->array[id]=1;	
   else 
   	b->array[id]=0; 
  }
  return get_min(b);
}

/**
funcion duel
Te regreda el duel de una pareja
*/
void duel(witness* w,par* p)
{
  int j_=MAX(p->x,p->y); 	
  int i_=MIN(p->x,p->y);

  int k=w->arreglo->array[j_-i_+1];
    //CASO 1
    if(k<=w->tamano-j_+1){
        if(w->cadena[k+j_-1	]!=w->cadena[k])
         {
           w->arreglo->array[j_]=k;
         }
         if (w->cadena[k+j_-1]!=w->cadena[k+j_-i_])
         { 
          w->arreglo->array[i_]=k+j_-i_;
         }
      //CASO 2
      }else{
        if(w->cadena[k-i_+1]!=w->cadena[k+j_-i_])
          {	
          w->arreglo->array[j_]=k-i_+1;	
          }
        if (w->cadena[k-i_+1]!=w->cadena[k])
          {
          w->arreglo->array[i_]=k-i_+1;
          } 
      }             
}

/**
Funcion divide_en_bloques
Funcion que divide una cadena en bloques
*/
void divide_en_bloques(int** b,string a,int indice)
{
   int a_=indice;
   int counter=0;
   for(int i=0;i<strlen(a)/2;i++)
     if(i<a_)
       b[counter][i%indice]=i;
     else
       {
       b[++counter][i%indice]=i;
       a_+=indice;
       }
}

typedef struct bloques{
  int** array;
  int length;
  int indice;
}bloques;

/**
Funcion print_bloques
Imprime todos los bloques
*/
void print_bloques(bloques* bl)
{
  for(int i=0;i<bl->length;i++){
     for(int j=0;j<bl->indice;j++)
        printf("%d ",bl->array[i][j]);

     s();
  }   
}

/**
Funcion print_bloque
Imprime un bloque
*/
void print_bloque(bloques* bl,int i)
{
  for(int j=0;j<bl->indice;j++)
        printf("%d ",bl->array[i][j]);

     s();
}

/**
Funcion init_bloques
Inicializa los bloques dado un indice
*/
bloques* init_bloques(int indice,witness* w)
{
  string cadena=w->cadena;
  bloques* b_ =malloc(sizeof(bloques));
  b_->length=strlen(cadena)/(2*indice); 
  b_->indice=indice;

  /**Iniciamos el arreglo en el heap*/
  b_->array=malloc(sizeof(int*)*b_->length);
   for(int i=0;i<b_->length;i++)
   {
    b_->array[i]=malloc(sizeof(int)*indice);
   }
   
   /**Asignamos en i el valor del iesimo bloque*/
   int a_=indice;
   int counter=0;
   for(int i=0;i<w->tamano/2;i++)
     if(i<a_)
       b_->array[counter][i%indice]=i+1;
     else
       {
       b_->array[++counter][i%indice]=i+1;
       a_+=indice;
       }
	
	return b_;
}



/**
Funcion encuentra_candidato
Encuentra un candidato en un bloque del arreglo witness
*/
int encuentra_candidato(witness* w,bloques* b,int a)
{
  int* arreglo=b->array[a];
  for(int i=2;i<b->indice;i++)
  {
    int pos=arreglo[i];
    if(w->arreglo->array[pos]==0)
      return i;
   }
}

/**
Funcion get_candidatos
Obtiene los candidatos de un arreglo witness
*/
par* get_candidatos(witness* w,bloques* b,int a)
{ 
  par* par=malloc(sizeof(par));
  int c=0;
  int* arreglo=b->array[a];
  
  for(int iw=0;iw<b->indice;iw++)
  {
    int i=arreglo[iw];
    if(w->arreglo->array[i]==0)
	      if(c==0)
	       {
	        c++;
	        par->x=i;
	       }else
	       {
	        par->y=i;
	       } 
    }   
 return par;
}

/**Funcion witness_fuerza_bruta
Calcula todo el arreglo con fuerza bruta
(solo se uso para testing)
*/
void witness_fuerza_bruta()
{

 for(int i=2;i<w->arreglo->length;i++)
  {
    w->arreglo->array[i]=brute_force_witness(i);
  } 
  print_witness(w);    
}

/**Funcion init_witness
recibe  : cadena y patron
regresa : la estructura witness inicializada
*/
void init_witness(){
   print_header(cadena);
   w=malloc(sizeof(witness));
   w->arreglo= init_int_array(ceiling_braces((double)strlen(cadena)/(double)2)+1);
   cadena=concat(" ",cadena);
   w->tamano=strlen(cadena);
   w->cadena=cadena;
   w->potencia=log2(strlen(cadena));
   //witness_fuerza_bruta();
}

/**
Funcion main
recibe  : el tamano de los argumentos argc y sus valores argv[]
regresa : entero que te dice si el programa termino bien
*/
int main(int argc,char *argv[])
{
  cadena=argv[1];
  if(potencia_de_2())
  {
   //Paso 1
   init_witness();
   //Paso 2
   for(int i=1;i<w->potencia;i++)
      {
      	//2.1
      	bloques* b=init_bloques(pow(2,i),w); 
        int candidato=encuentra_candidato(w,b,0);
        w->arreglo->array[candidato]=brute_force_witness(candidato);
        
        //2.2
        if(w->arreglo->array[candidato]==0)
          break;

        //2.3
         omp_set_num_threads(b->length);
         #pragma omp parallel private(useless)
         {
          int id=omp_get_thread_num();
          par* par=get_candidatos(w,b,id);
          duel(w,par);
         }
      }
      print_witness(w);  
  }else
    print_error();
}
