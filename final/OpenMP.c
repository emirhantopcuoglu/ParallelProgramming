#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define ARRAYSIZE 16
int main(int argc, char *argv[]) {
	int i, j, tid;
	// x degerleri: 
	double x[] = {0.2, 0.4, 0.6, 0.8, 1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 2.6, 2.8, 3, 3.2};
	// f(x)  degerleri: 
	double a[] = {0.67, 1.24, 2.10, 3.39, 5.25, 7.83, 11.28, 15.74, 21.35, 28.25, 36.59, 46.52, 58.18, 71.71, 87.25, 104.95};
	double alpha[ARRAYSIZE];
	double b[ARRAYSIZE];
	double c[ARRAYSIZE];
	double d[ARRAYSIZE];
	double h[ARRAYSIZE];
	double l[ARRAYSIZE];
	double m[ARRAYSIZE];
	double z[ARRAYSIZE];
	omp_set_num_threads(8); // 8 Thread kullanýlacak
	#pragma omp parallel{
	//Adým 1:
	#pragma omp for
	for(i = 0; i < ARRAYSIZE; i++){
		h[i] = x[i+1] - x[i];
	}
	//Adým 2:
	#pragma omp for
	for(i = 1; i < ARRAYSIZE; i++){
		alpha[i] = ((3/h[i]) * (a[i+1] - a[i])) - ((3/h[i-1]) * (a[i] - a[i-1]));
	}
	//Adým 3:
	l[0] = 1;
	m[0] = 0;
	z[0] = 0;
	//Adým 4:
	#pragma omp for
	for(i = 1; i < ARRAYSIZE; i++){
		l[i] = (2 * (x[i+1] - x[i-1])) - (h[i-1] * m[i-1]);
		m[i] = h[i] / l[i];
		z[i] = (alpha[i] - (h[i-1] * z[i-1])) / l[i];
	}
	//Adým 5:
	l[ARRAYSIZE-1] = 1;
	z[ARRAYSIZE-1] = 0;
	c[ARRAYSIZE-1] = 0;
	//Adým 6:
	#pragma omp for
	for(j = ARRAYSIZE-1; j >= 0; j--){
		c[j] = z[j] - (m[j] * c[j+1]);
		b[j] = ((a[j+1] - a[j]) / h[j]) - ((h[j] * ((c[j+1]) + (2*c[j]))) / 3);
		d[j] = (c[j+1] - c[j]) / (3 * h[j]); 
	}
	//Adým 7:
	#pragma omp for
	for(j = 0; j < ARRAYSIZE; j++){
		tid = omp_get_thread_num();
		printf("Thread %d : a%d = %.3lf, b%d = %.3lf, c%d = %.3lf, d%d = %.3lf \n",tid,j,a[j],j,b[j],j,c[j],j,d[j]);
	}
	}
	return 0;
}


