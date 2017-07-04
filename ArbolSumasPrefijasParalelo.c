#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <omp.h>
int numero_de_elemento;

void print(int longitud,int a[])
{
printf("[");
for(int i=0;i<longitud;i++){
  printf("%d ",a[i]);
 }
printf("]\n");
}

void crea_arreglo_aleatorio(int x,int arreglo[])
{
 srand(time(NULL));
 for(int i=0;i<x;i++){
  arreglo[i]=rand()%100;
 }	
}

int sumas_prefijas(int *arga,int length,int **b,int**c ){
  for(int h=0;h<length;h++){

  }
}


int main(int argc,char *argv[]){
if(argc!=2){
 printf("La ejecucion debe de ser:\n ./practica3 n\n");	
 return -1;
}else if(atoi(argv[1])>13){
 printf("Escribiste un exponente demasiado grande\n");
 return -1;	
}else{
 /**La inicializacion del arreglo principal*/	
  int logn=atoi(argv[1]);
  int n=pow(2,logn);
  int a[n];
  crea_arreglo_aleatorio(n,a);
  
 int j;
  print(n,a);
 
	
  /**Inicializacion de los arreglos secundarios*/
   int b[logn+1][n];
   int c[logn+1][n];
    
	 for(int i=0;i<logn+1;i++)
	    for(int j=0;j<n;j++){
	  	  b[i][j]=0; 	
	  	  c[i][j]=0;
	     }	
	 
	  
   /**Parte 1*/
  /**Copio todos los elementos dentro de la matriz b*/  
  omp_set_num_threads(n);
	#pragma omp parallel private(j)
    {
      j=omp_get_thread_num();	
	  b[0][j]=a[j];
	 
	}

   
  /**Parte 2*/
  /**Subo en el arbol haciendo las sumas*/  
     int hilos=n;
     for(int h=0;h<logn;h++){
     	hilos/= 2;
        omp_set_num_threads(hilos);	
	    #pragma omp parallel private(j)
        {
          j= omp_get_thread_num();	
          b[h+1][j]=b[h][(2*j)+1]+b[h][2*j];
	    }
	  }

    
	  /**Parte 3*/
     /**Bajo en el arbol obteniendo ya los valores correctos*/
      hilos=1;
      for(int h=logn;h>-1;h--){
      omp_set_num_threads(n/pow(2,h)); 
 
	    #pragma omp parallel private(j)
        {
         j = omp_get_thread_num()+1;	
         if(j%2==0){
     	  c[h][j-1]=c[h+1][(j-1)/2];
          }else if(j==1){
          c[h][0]=b[h][0];
          }else{
  		  c[h][(j-1)]=c[h+1][(j-2)/2]+b[h][j-1];
  		  }
          
	  
	    }
	  }

	  /**Imprimo el resultado del arreglo*/
       printf("[");
	    for(int j=0;j<n;j++){
	      printf("%d ",c[0][j]);
	     }	
       printf("]\n");




	  
 

	  

 }
}
