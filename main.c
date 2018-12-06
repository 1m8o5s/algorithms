#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
struct st {
	char c_word[50];
	char definition[200];
	bool f;
};
int addition_of_strings_hash(char*string_, int size_) {
	int sum = 0;
	for (int i = 0; i < strlen(string_); i++) {
		sum += string_[i];
	}
	return sum % size_;
}
int xor_of_strings_hash(char*string_, int size_) {
	int sum = 0;
	for (int i = 0; i < strlen(string_); i++) {
		sum += string_[i] ^ (i + 1);
	}
	return (sum%size_) ? sum % size_ : 1;
}
void fill_hash_table(struct st *hash_table_, char*c_word_, char*definition_) {
	strcpy(hash_table_->c_word, c_word_);
	strcpy(hash_table_->definition, definition_);
	hash_table_->f = true;
}
void write_hash_table(ostream&c, struct st*hash_table_, int size_) {
	for (int i = 0; i < size_; i++) {
		c << hash_table_[i].c_word << " | " << hash_table_[i].definition << endl;
	}
}
void write_hash_table(ofstream&c, struct st*hash_table_, int size_) {
	for (int i = 0; i < size_; i++) {
		c << hash_table_[i].c_word << " | " << hash_table_[i].definition << endl;
	}
}
char*search_definition(struct st*hash_table_, int size_, char*what_word) {
	int hash_key;
	for (int i = 0; i < size_; i++) {
		hash_key = (addition_of_strings_hash(what_word, size_) + i * xor_of_strings_hash(what_word, size_)) % size_;
		if (!strcmp(hash_table_[hash_key].c_word, what_word)) {
			return hash_table_[hash_key].definition;
		}
	}
	return (char*)"not found";
}
int main() {
	int size_;
	char tmp_word[50];
	char tmp_definition[200];
	cout << "Enter size of table: ";
	cin >> size_;
	struct st* hash_table_ = (struct st*)malloc(size_ * sizeof(struct st));
	for (int i = 0; i < size_; i++) {
		hash_table_[i].f = false;
	}
	ifstream fin("file.txt");
	int hash_key;
	for (int i = 0; i < size_; i++) {
		fin.getline(tmp_word, 50);
		fin.getline(tmp_definition, 200);
		for (int j = 0; j < size_; j++) {
			hash_key = (addition_of_strings_hash(tmp_word, size_) + j * xor_of_strings_hash(tmp_word, size_)) % size_;
			if (!hash_table_[hash_key].f) {
				fill_hash_table((hash_table_ + hash_key), tmp_word, tmp_definition);
				break;
			}
		}
	}
	fin.close();
	write_hash_table(cout, hash_table_, size_);
	char word[50];
	cout << "\nenter word what you search ";
	cin >> word;
	cout << endl <<"Definition for " << word << ": "<< search_definition(hash_table_, size_, word) << endl;
	system("pause");
	return 0;
}
