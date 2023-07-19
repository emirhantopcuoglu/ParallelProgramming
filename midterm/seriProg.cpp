#include <iostream>
#include <chrono>
using namespace std;
int main(int argc, char** argv) {
	/* n = 1 için alan -306 çýkmakta. Klasik integral çözümü sonucu ise -198
	Yani yaklaþýk (n=1 için) %54'lük bir hata gerçekleþmekte. Ayný þekilde:
	n = 20 için alan: -198.270 (%0.136 hata oraný)
	n = 60 için alan: -198.030 (%0.015 hata oraný)
	n = 100 için alan: -198.011 (%0.005 hata oraný)
	*/
	auto start = chrono::steady_clock::now();
	float a = 0, b = 6, n = 100, area = 0, h, x;
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
	auto end = chrono::steady_clock::now();
	cout << "Gecen sure: " << chrono:: duration_cast<chrono::microseconds>(end-start).count()<<" mikrosaniye\n";
	
	return 0;
}
