#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
void fillGraph(vector<vector <int> >&graph, int l, int r){
	if (r == l){
		graph[l][l]++;
	}
	else{
		graph[l][r]++;
		graph[r][l]++;
	}
}
void writeGraph(vector<vector <int> > graph){
	for (int i = 0; i < graph.size(); i++){
		cout << "\t"  << i;
	}
	cout << endl << "------------------------------------------------------------------------------------------------------------";
	for (int i = 0; i < graph.size(); i++){
		cout << endl << i << "| ";
		for (int j = 0; j < graph.size(); j++){
			cout << "\t" << graph[i][j];
		}
	}
}
void writeMarksOfGraph(vector<vector<int> > graph){
	for (int i = 0; i < graph.size(); i++){
		cout << i << "\t";
	}
}
int sum(vector<int>g){
	int sum_ = 0;
	for (int i = 0; i < g.size();i++)
		sum_ += g[i];
	return sum_;
}
bool search(vector<int>g, int num){
	for (int i = 0; i < g.size(); i++)
		if (g[i] == num)
			return true;
	return false;
}
bool isCountedGraph(int number_of_not_isolated_vertex, vector<vector<int> >graph, vector<int>&visited, int tmp_mark){
	visited.push_back(tmp_mark);
	for (int i = 0; i < graph.size(); i++)
		if (graph[tmp_mark][i] > 0)
			if (!search(visited, i))
				isCountedGraph(number_of_not_isolated_vertex, graph, visited, i);
	if (visited.size() == number_of_not_isolated_vertex)
		return true;
	return false;
}
bool isEuler(vector<vector <int> > graph){
	vector<int> nonIsolatedMarks;
	for (int i = 0; i < graph.size(); i++)
		if (sum(graph[i]) > 0)
			nonIsolatedMarks.push_back(i);
	vector<int> visited;
	if (isCountedGraph(nonIsolatedMarks.size(), graph, visited, nonIsolatedMarks[0])){
		for (int i = 0; i < graph.size(); i++)
			if (sum(graph[i]) % 2)
				return false;
		return true;
	}
	return false;
}
int main(){
	vector<vector<int> >graph;
	int n;
	cout << "Enter number of vertex in graph: ";
	cin >> n;
	graph.resize(n);
	for (int i = 0; i < n; i++){
		graph[i].resize(n);
		for (int j = 0; j < n; j++)
			graph[i][j] = 0;
	}
	
	ifstream fin("graph.txt");
	int l, r;
	while (true){
		if (fin.eof())
			break;
		fin >> l >> r;
		fillGraph(graph, l, r);
	}
	if (isEuler(graph)){
		cout << endl << "Graph is Eulers";
	}
	else{
		cout << endl << "Graph is not Eulers";
	}
	cout << endl;
	cout << "Graph representation" << endl;
	writeGraph(graph);
	cout << endl << endl << "Marks of vertex: ";
	writeMarksOfGraph(graph);
	cout << endl;
	system("pause");
	return 0;
}
