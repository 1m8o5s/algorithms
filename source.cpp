#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
struct st{
	int data;
	bool is_empty;
	struct st*next;
};
void push(vector<struct st*>&arr, struct st*root, struct st*gg, int data){
	if (!root){
		arr.resize(1);
		arr[0] = (struct st*)malloc(sizeof(struct st));
		arr[0]->data = data;
		arr[0]->is_empty = false;
		arr[0]->next = (struct st*)malloc(sizeof(struct st));
		arr[0]->next->is_empty = true;
		arr[0]->next->next = (struct st*)malloc(sizeof(struct st));
		arr[0]->next->next->is_empty = true;
		return;
	}
	int root_id = 0;
	for (; root_id < arr.size(); root_id++){
		if (arr[root_id]->data == root->data){
			break;
		}
	}
	if (gg->is_empty){
		if (data < arr[root_id]->data){
			arr[root_id]->next->data = data;
			arr[root_id]->next->is_empty = false;
		}
		else{
			arr[root_id]->next->next->data = data;
			arr[root_id]->next->next->is_empty = false;
		}
		struct st *tmp = (struct st*)malloc(sizeof(struct st));
		tmp->data = data;
		tmp->is_empty = false;
		tmp->next = (struct st*)malloc(sizeof(struct st));
		tmp->next->is_empty = true;
		tmp->next->next = (struct st*)malloc(sizeof(struct st));
		tmp->next->next->is_empty = true;
		arr.push_back(tmp);
		return;
	}
	if (data < arr[root_id]->data){
		push(arr, gg, arr[root_id]->next, data);
	}
	else{
		push(arr, gg, arr[root_id]->next->next, data);
	}
}
void write(vector<struct st*> ss, int root, ofstream& file_){
	int temp = 0;
	for (; temp < ss.size(); temp++){
		if (ss[temp]->data == root){
			break;
		}
	}
	if (temp<ss.size()){
		file_ << ss[temp]->data << endl;
		write(ss, ss[temp]->next->data, file_);
		write(ss, ss[temp]->next->next->data, file_);
	}
	return;
}
void write(vector<struct st*> ss, int root, ostream& cout_){
	int temp = 0;
	for (; temp < ss.size(); temp++){
		if (ss[temp]->data == root){
			break;
		}
	}
	if (temp<ss.size()){
		cout_ << ss[temp]->data << endl;
		write(ss, ss[temp]->next->data, cout_);
		write(ss, ss[temp]->next->next->data, cout_);
	}
	return;
}
int main(){
	vector<struct st*> ss(1);
	ifstream file_("file1.txt");
	int dt;
	ss[0] = nullptr;
	while (!file_.eof()){
		file_ >> dt;
		push(ss, ss[0], ss[0], dt);
	}
	ofstream file_2("file2.txt");
	write(ss, ss[0]->data, cout);
	write(ss, ss[0]->data, file_2);
	system("pause");
	return 0;
}