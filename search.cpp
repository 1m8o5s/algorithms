#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

void write_to(ofstream& f, vector<int>&what){
	for (int i = 0; i < what.size(); i++){
		f << what[i] << " ";
	}
}
void write_to(ostream& f, vector<int>&what){
	for (int i = 0; i < what.size(); i++){
		f << what[i] << " ";
	}
}
void rand_push(vector<int>&what, int n){
	srand(time(0));
	for (int i = 0; i < n; i++)
		what.push_back(rand() % 100);
}
int search(vector<int> &where, int what){
	for (int i = 0; i < where.size(); i++)
		if (where[i] == what){
			for (; i > 0; i--)
				where[i] = where[i - 1];
			where[0] = what;
			return 0;
		}
	return -1;
}

int main(){
	vector<int> A, B, C, D;
	int n, m;
	cout << "Enter number of elements in array A: ";
	cin >> n;
	rand_push(A, n);
	cout << "Enter number of elements in array B: ";
	cin >> m;
	rand_push(B, m);
	cout << "Elements in array A: ";
	write_to(cout, A);
	cout << "\nElements in array B: ";
	write_to(cout, B);
	ofstream fout("file.txt");
	fout << "Elements in array A: ";
	write_to(fout, A);
	fout << "\nElements in array B: ";
	write_to(fout, B);
	fout.close();

	for (int i = 0; i < A.size(); i++){
		if (search(C, A[i]))
			C.push_back(A[i]);
	}
	for (int i = 0; i < C.size(); i++){
		search(B, C[i]);
		if (B[0] != C[i]){
			D.push_back(C[i]);
		}
	}
	cout << "\nElements in array D: ";
	write_to(cout, D);
	ofstream f("file2.txt");
	f << "Elements in array D: ";
	write_to(f, D);
	f.close();
	cin.get();
	cin.get();
	return 0;
}
