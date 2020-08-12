/*
 * merge.cxx
 *
 * Copyright 2016 Gabriel Vargas <gabreta@VmGabriel96>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */


#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <vector.h>

using namespace std;

double timeval_diff(struct timeval *a, struct timeval *b)
{
    return
	(double)(a->tv_sec + (double)a->tv_usec/1000000) -
	(double)(b->tv_sec + (double)b->tv_usec/1000000);
}

// En el código usamos la clase vector (#include <vector.h>) para crear los vectores,
// obviamente funciona igual de bien si se utilizan los arrays tipo C: TIPO V[]
template <class T, class U>
void fusiona(vector<T>& v, U ini, U med, U fin) {
    vector<T> aux(fin - ini + 1);
    int i = ini; // Índice de la parte izquierda
    int j = med + 1; // Índice de la parte derecha
    int k = 0; // Índice del vector aux
 
 
    /* Mientras ninguno de los indices llegue a su fin vamos realizando
       comparaciones. El elemento más pequeño se copia al vector aux */
    while (i <= med && j <= fin) {
        if (v[i] < v[j]) {
            aux[k] = v[i];
            i++;
        }
        else {
            aux[k] = v[j];
            j++;
        }
        k++;
    }
 
    /* Uno de los dos sub-vectores ya ha sido copiado del todo, simplemente
       debemos copiar todo el sub-vector que nos falte */
    while (i <= med) {
        aux[k] = v[i];
        i++;
        k++;
    }
 
    while (j <= fin) {
        aux[k] = v[j];
        j++;
        k++;
    }
 
    /* Copiamos los elementos ordenados de aux al vector original v */
    for (int n = 0; n < aux.size(); ++n) v[ini + n] = aux[n];
}
 
template <class T, class U>
void merge_sort(vector<T>& v, U ini, U fin) {
    /* Si ini = fin el sub-vector es de un solo elemento y, por lo tanto
       ya está ordenado por definición */
    if (ini < fin) {
/*Considerar que el valor de med siempre es redondeado hacia abajo.*/
        int med = (ini + fin)/2;
        merge_sort(v, ini, med);
        merge_sort(v, med + 1, fin);
        fusiona(v, ini, med, fin);
    }
}

int main(int argc, char **argv)
{
	int n;
    for (n=50;n<=500;n+=10)
    {
	struct timeval t_ini, t_fin;
	double secs;
	
	int * num = new int[n];
	llenar(num,n);
	//cout<<"Funcion sin Ordenar"<<endl;
	//cout<<"------------------"<<endl;
	//cout<<"------------------"<<endl;
	//cout<<"Funcion Ordenada"<<endl;
	//cout<<"------------------"<<endl;
	gettimeofday(&t_ini, NULL);
	merge_sort(num,0,n);
	gettimeofday(&t_fin, NULL);

	secs = timeval_diff(&t_fin, &t_ini);

	//cout<<"------------------"<<endl;

	cout<<"Time with "<<n<<" is "<<secs<<endl;
    }
    return 0;
}
