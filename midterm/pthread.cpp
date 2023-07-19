#include <iostream>
#include <chrono>
#include <pthread.h>
#define NUM_THREADS 10
using namespace std;
void *function(void *args){
	float a = 0, b = 6, n = 20, area = 0, h, x;
	int i;
	h = (b - a) / n;
	// f(x1) + f(x2) + ... + f(xn-1):
	for(i = a; i < n; i++){
		x = a + (i * h);
		area = area + ((-3*x*x)+(x));
	}
	// h * [f(x0)/2 + f(xn)/2 +(f(x1) + f(x2) + ... + f(xn-1))]:
	area = h * ((((-3*a*a) + (a)) / 2) + (((-3*b*b) + (b)) / 2) + area); 
	printf("Alan: %.3f\n",area);
	return 0;
}

int main(int argc, char** argv) {
	auto start = chrono::steady_clock::now();
	pthread_t myThread[NUM_THREADS];
	int i,t;
	for(i = 0; i < NUM_THREADS; i++){
		t = pthread_create(&myThread[i],NULL,function,NULL);
		if(t != 0){
			printf("Thread oluþturulamadý!");
		}
	}
	for(i = 1; i < NUM_THREADS; i++){
		pthread_join(myThread[i],NULL);
	}
	auto end = chrono::steady_clock::now();
	cout << "Geçen süre: " << chrono:: duration_cast<chrono::microseconds>(end-start).count()<<" mikrosaniye\n";
	return 0;
}
