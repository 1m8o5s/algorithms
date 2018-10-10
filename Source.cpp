#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;
void write_to(ofstream &file, vector<vector<int> >&arr_){
	for (int i = 0; i < arr_.size(); i++){
		for (int j = 0; j < arr_.size(); j++){
			file << arr_[i][j] << " ";
		}
		file << endl;
	}
}
void write_to(ostream &f, vector<vector<int> >&arr_){
	for (int i = 0; i < arr_.size(); i++){
		for (int j = 0; j < arr_.size(); j++){
			f << arr_[i][j] << " ";
		}
		f << endl;
	}
}
void rand_push(vector<vector<int> >&arr_){
	srand(time(0));
	for (int i = 0; i < arr_.size(); i++){
		for (int j = 0; j < arr_.size(); j++){
			arr_[i][j] = rand() % 100;
		}
	}
}
void merge_sort(vector<int>&arr_, int&permutations, int&comparison){
	if (arr_.size()>1){
		int left__nmbr = arr_.size() / 2;
		int right__nmbr = arr_.size() - left__nmbr;
		vector<int> left_(left__nmbr);
		int i = 0;
		for (; i < left__nmbr; i++){
			left_[i] = arr_[i];
			permutations++;
		}
		merge_sort(left_, permutations, comparison);
		vector<int> right_(right__nmbr);
		for (int j = 0; j < right__nmbr; j++, ++i){
			right_[j] = arr_[i];
			permutations++;
		}
		merge_sort(right_, permutations, comparison);
		for (int i = 0, l=0, r=0; i < left__nmbr + right__nmbr; i++){
			if (left_.size() > l){
				if (right_.size()>r)
					if (left_[l] > right_[r])
						arr_[i] = left_[l++];
					else
						arr_[i] = right_[r++];
				else
					arr_[i] = left_[l++];
				permutations++;
				comparison++;
			}
			else{
				if (right_.size() > r){
					arr_[i] = right_[r++];
					permutations++;
				}
				comparison++;
			}
		}
	}
}
void radix_sort(vector<int>&arr_, int&permutations, int&comparison){
	int max_len = 0, k = 1, tmp_ln = 0;
	for (int i = 0; i < arr_.size(); i++){
		while (arr_[i] / k){
			tmp_ln++;
			k *= 10;
		}
		k = 1;
		if (tmp_ln > max_len)
			max_len = tmp_ln;
	}
	vector<vector<int> > c_r;
	c_r.resize(10);
	while (max_len){
		for (int i = 0; i < arr_.size(); i++){
			c_r[arr_[i] / k % 10].push_back(arr_[i]);
			permutations++;
		}
		int n = 0;
		for (int i = 9; i >= 0; i--)
			for (int j = 0; j < c_r[i].size(); j++){
				arr_[n++] = c_r[i][j];
				permutations++;
			}
		max_len--;
		k *= 10;
		for (int i = 0; i < 10; i++){
			c_r[i].clear();
		}
		
	}
}
int main(){
	vector<vector<int> > array_;
	int n;
	cout << "Enter number of rows and collumns in array: ";
	cin >> n;
	array_.resize(n);
	for (int i = 0; i < n; i++)
		array_[i].resize(n);
	rand_push(array_);
	write_to(cout, array_);
	ofstream file("file1.txt");
	write_to(file, array_);
	file.close();
	int permutations = 0, comparison = 0;
	cout << endl;
	for (int i = 1; i < n; i++){
		vector<int>tmp;
		for (int j = n - 1; j > n - 1 - i; j--){
			
			tmp.push_back(array_[j][i]);
		}
		merge_sort(tmp, permutations, comparison);
		//radix_sort(tmp, permutations, comparison);
		for (int j = n - 1; j > n - 1 - i; j--){
			array_[j][i] = tmp[n-1-j];
		}
		tmp.clear();
	}
	cout << "number of comparison: " << comparison << " number of permutations: " << permutations << endl;
	write_to(cout, array_);
	ofstream f("file2.txt");
	f << "number of comparison: " << comparison << " number of permutations: " << permutations << endl;
	write_to(f, array_);
	f.close();
	cin.get();
	cin.get();
	return 0;
}