#include <iostream>
using namespace std;

int sum_(int a, int b, int &count){
	if (!a)
		return b;
	if (!b)
		return a;
	count++;
	return sum_(b - b / abs(b), a, count) + b / abs(b);
}
int sum2_(int a, int b, int &count){
	int a1 = a, summa = b;
	while (a1){
		summa++;
		a1--;
		count++;
	}
	return summa;
}
int main(){
	int i = 0, j = 0;
	cout << sum_(0, -1, i);
	cout << endl << i;
	cout << endl << sum2_(3, 4, j);
	cout << endl << j;
	cin.get();
	return 0;
}
