#include <stdio.h>
#include <omp.h>
#include <math.h>
/**Este archivo contiene el resultado de las sumas de Riemman de la
ecuacion dada en el archivo Practica2.pdf que se encuentra en la pagina 
del curso

Ejecucion gcc Practica02AntonioMartinez.c -lm -fopenmp
@version 1.1
@author Antonio Martinez Cruz
*/


/**Recibe un double que representa la posicion en x
y te regresa el valor en "y" de la funcion
@param La posicion en x
@return El numero que representa el valor de y 
 	en el x dado
*/
double funcion(double x){
 return 100-pow(x-10,4)+(50*pow(x-10,2))-(8*x);
}

/**Regresa la aproximacion del area en el intervalo
dado a partir de la pocision x dada
@param a:donde se comenzara a hacer la suma de Riemman
       ancho el ancho del intervalo
@return el numero que representa el area de una region 
*/
double suma_De_Riemman(double a,double ancho){
    double valorDeRetorno = 0.0;
    for(int i = 0; i<5; i++, a+=ancho){
	valorDeRetorno+=funcion(a)*ancho;
     }
    return valorDeRetorno;
}	

/**Te regresa el tamaño del intervalo
@param  double intervalob  :Representa el inicio del intervalo
	double intervaloa  :Representa el final del intervalo
	double procesadores:El numero de procesadores de la entrada
@return el tamaño del intervalo representado por un double
*/
double intervalo_hilos(double intervalob,double intervaloa,double procesadores){
 return (intervaloa-intervalob)/(5*procesadores);
}


/**Funcion ejecutable,en esta se realiza la suma de Riemman 
@param int argc   El tamaño del arreglo recibido
       char**argv La cadena de caracteres recibidos
@return int el entero que dice si termino correctamente la +
	ejecucion 
*/
int main(int argc, char** argv){

	int tiempo,numHilos,idHilo;
	double suma ,sumaHilo;
	sscanf(argv[1], "%i", &numHilos);
	omp_set_num_threads(numHilos);
	
	#pragma omp parallel private(idHilo, sumaHilo)
        {
	  idHilo = omp_get_thread_num();
	  double intervalo = intervalo_hilos(3,17,numHilos);
	  double inicio    = 3+(idHilo*intervalo*5);
	  suma+=suma_De_Riemman(inicio,intervalo);
	}

	printf("suma: %lf\n",suma); 
	return 0;	
}
