#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
struct st{
	int data;
	struct st*next;
};
bool search(vector<int>where_, int what){
	for (int i = 0; i < where_.size(); i++)
		if (where_[i] == what)
			return true;
	return false;
}
void fillGraph(vector<struct st*>&graph, int l, int r){
	if (graph[l] == nullptr){
		graph[l] = (struct st*)malloc(sizeof(struct st));
		graph[l]->data = r;
		graph[l]->next = nullptr;
	}
	else{
		struct st* tmp;
		for (tmp = graph[l]; tmp->next != nullptr; tmp = tmp->next){}
		tmp->next = (struct st*)malloc(sizeof(struct st));
		tmp->next->data = r;
		tmp->next->next = nullptr;
	}
	if (graph[r] == nullptr){
		graph[r] = (struct st*)malloc(sizeof(struct st));
		graph[r]->data = l;
		graph[r]->next = nullptr;
	}
	else{
		struct st* tmp;
		for (tmp = graph[r]; tmp->next != nullptr; tmp = tmp->next){}
		tmp->next = (struct st*)malloc(sizeof(struct st));
		tmp->next->data = l;
		tmp->next->next = nullptr;
	}
}
void writeMarks(vector<struct st*> graph){
	cout << endl;
	for (int i = 0; i < graph.size(); i++){
		cout << i << "\t ";
	}
	cout << endl;
}
void writeRepresentationOfGraph(vector<struct st*> graph){
	for (int i = 0; i < graph.size(); i++){
		cout << endl << i << " : ";
		for (struct st* tmp = graph[i]; tmp != nullptr; tmp = tmp->next)
			cout << "\t " << tmp->data;
	}
}
bool isConncetedGraph(vector<int> graph_marks, vector<struct st*> graph, vector<int>&visited, int temp_mark){
	if (graph_marks.size() < 2)
		return graph_marks.size();
	visited.push_back(temp_mark);
	for (struct st* tmp_ptr = graph[temp_mark]; tmp_ptr != nullptr; tmp_ptr = tmp_ptr->next){
		if (!search(visited, tmp_ptr->data)){
			if (search(graph_marks, tmp_ptr->data)){
				isConncetedGraph(graph_marks, graph, visited, tmp_ptr->data);
			}
		}
	}
	if (visited.size() == graph_marks.size()){
		return true;
	}
	return false;
}
int count_(vector<int> graph_marks, vector<struct st*> graph, int remove){
	vector<int>visited;
	int sum = 0;
	if (graph_marks.size()){
		if (!isConncetedGraph(graph_marks, graph, visited, graph_marks[0])){
			sum++;
		}
	}
	else{
		return 0;
	}
	//delete visited;
	vector<vector<int>>subgraphs_marks;
	subgraphs_marks.resize(graph_marks.size());
	for (int i = remove; i < graph_marks.size(); i++){
		for (int j = 0; j < graph_marks.size()-i-1; j++){
			subgraphs_marks[i].push_back(graph_marks[j]);
		}
		for (int j = graph_marks.size() - i; j < graph_marks.size(); j++){
			subgraphs_marks[i].push_back(graph_marks[j]);
		}
	}
	for (int i = 0; i < subgraphs_marks.size(); i++){
		sum += count_(subgraphs_marks[i], graph, i);
	}
	return sum;
}
int main(){
	int number_of_vertex;
	cout << "Enter number of vertex: ";
	cin >> number_of_vertex;
	vector<struct st*> graph(number_of_vertex);
	ifstream fin("graph.txt");
	int l;
	int r;
	while (true){
		if (fin.eof())
			break;
		fin >> l >> r;
		fillGraph(graph, l, r);
	}
	vector<int>g_m(number_of_vertex);
	for (int i = 0; i < number_of_vertex; i++){
		g_m[i] = i;
	}
	cout << "Number of nezvyazn pidgraphs = " << count_(g_m, graph, 0)+1;
	writeMarks(graph);
	writeRepresentationOfGraph(graph);
	return 0;
}