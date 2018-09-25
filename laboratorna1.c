/*
T3
*^заповнює масив випадковими числами;
*^виводить несортований масив на екран;
*^записує його у файл (текстовий);  ^
*виконує сортування заданим методом із підрахунком кількості операцій
порівняння і перестановок;
*^виводить на екран кількість порівнянь та перестановок;
*^виводить на екран сортований масив.
*^заносить результати у новий файл, спочатку кількість порівнянь та
перестановок, потім весь масив.



*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define A 6 // maybe vvod z klaviaturi
#define B 6
struct result{
	int perestanovki;
	int porivnyanna;
};
void rand_push(int * arr, int a, int b){
	srand(time(0));
	for (int i = 0; i < a; i++){
		for (int j = 0; j < b; j++){
			*(arr + a*i + j) = rand()%100;
		}
	}
}
void put_to_file(FILE * fp, int * arr, int a, int b){
	for (int i = 0; i < a; i++){
		for (int j = 0; j < b; j++){
			fprintf(fp, "%d ", *(arr + a*i + j));
		}
		fprintf(fp, "\n");
	}
}
struct result * shell_sort(int* arr, int a, int b){
	struct result * res = (struct result*)malloc(sizeof(struct result));
	res->perestanovki = 0;
	res->porivnyanna = 0;
	int k = a/2;
	int tmp;
	while (k!=0){
		printf("\nIM here\n");
		for (int i = 0; i < k; i++){
			printf("\nIM here 2");
			for (int j = i; j < b; j+=k){
				printf("\n IM here j = %d, i = %d\n", j);
				for (int f = j; j > 0; j-=k){
					printf("\n IM here f = %d, k = %d\n", f, k);
					if (*(arr+f*b) > *(arr+j*b)){
						tmp = *(arr+f*b);
						*(arr+f*b) = *(arr+j*b);
						*(arr+j*b) = tmp;
						res->perestanovki++;
					}
					res->porivnyanna++;
				}
			}
		}
		k--;
	}
	return res;

}
void quick_sort(){

}
int main(){
	printf("%d \n", 8/3);
	int arr[A][B];
	//int number_of_perestanovok = 4;
	//int number_of_porivnyann = 2;
	//before sorting
	rand_push(&(arr[0][0]), A, B);
	put_to_file(stdout, &(arr[0][0]), A, B);
	FILE * fp = fopen("file.txt", "w");
	put_to_file(fp, &(arr[0][0]), A, B);
	fclose(fp);
	//
	struct result * rs = shell_sort(&(arr[0][0]), A, B);
	//after sorting
	printf("%d %d\n", rs->perestanovki, rs->porivnyanna);
	put_to_file(stdout, &(arr[0][0]), A, B);
	FILE * fd = fopen("file1.txt", "w");
	fprintf(fp, "%d %d\n", rs->perestanovki, rs->porivnyanna);
	put_to_file(fp, &(arr[0][0]), A, B);
	fclose(fd);
	//
	return 0;
}