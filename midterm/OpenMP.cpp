#include <iostream>
#include <chrono>
#include <omp.h>
#define NUM_THREADS 4
using namespace std;

int main(int argc, char** argv) {
	float a = 0, b = 6, area = 0, h, x;
	int i,tid,n=100;
	double start,end,time;
	start = omp_get_wtime();
	h = (b - a) / n;
	#pragma omp parallel shared(area) num_threads(NUM_THREADS)
	{
		tid = omp_get_thread_num();
		printf("Thread %d",tid);
		#pragma omp for schedule(static,4)
		for(i = a; i < n; i++){
		x = a + (i * h);
		area = area + ((-3*x*x)+(x));
		}		
	}
	area = h * ((((-3*a*a) + (a)) / 2) + (((-3*b*b) + (b)) / 2) + area); 
	printf("Alan: %.3f\n",area);
	end = omp_get_wtime();
	time = end - start;
	std::cout<<"Süre: "<< time <<" saniye"<<std::endl;
	return 0;
}
