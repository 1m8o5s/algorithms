/*
T3
*^заповнюЇ масив випадковими числами;
*^виводить несортований масив на екран;
*^записуЇ його у файл (текстовий);  ^
*виконуЇ сортуванн€ заданим методом ≥з п≥драхунком к≥лькост≥ операц≥й
пор≥вн€нн€ ≥ перестановок;
*^виводить на екран к≥льк≥сть пор≥вн€нь та перестановок;
*^виводить на екран сортований масив.
*^заносить результати у новий файл, спочатку к≥льк≥сть пор≥вн€нь та
перестановок, пот≥м весь масив.



*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
struct st{
	int a1;
	int a2;
};
struct result{
	int permutations;
	int comparison;
};
void swap(struct st * a, struct st * b){
	struct st * tmp = (struct st*)malloc(sizeof(struct st));
	*tmp = *a;
	*a = *b;
	*b = *tmp;
	free(tmp);
}
void ultra_swap(struct st * arr, int fst, int scnd, int g, int n){
	for (int i = 0; i < n; i++){
		swap(arr + fst*n + i, arr + scnd*n + i); 
	}
}

void rand_push(struct st * stru, int width, int height){
	srand(time(0));
	for (int i = 0; i < width*height; i++){
		(stru+i)->a1 = rand()%100;
		(stru+i)->a2 = rand()%200;
	}
}
/*void put_to_file(FILE * fp, int * arr, int width, int height){
	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			fprintf(fp, "%d ", *(arr + width*i + j));
		}
		fprintf(fp, "\n");
	}
}*/
void put_to_file(FILE * fp, struct st * arr, int width, int height){
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			fprintf(fp, "(%d, %d) ", (arr+i*width+j)->a1, (arr+i*width+j)->a2);
		}
		puts("\n");
	}
}

//struct result * shell_sort(int* arr, int width, int height){
//	struct result * res = (struct result*)malloc(sizeof(struct result));
//	res->permutations = 0;
//	res->comparison = 0;
//	int k = height / 2;
//	while (k != 0){
//		for (int i = 0; i < k; i++){
//			for (int j = i; j < height; j += k){
//				for (int f = j; f >= 0; f -= k){
//					if (*(arr + f*height) < *(arr + j*height)){
//						ultra_swap(arr, f, j, height, width);
//						res->permutations++;
//					}
//					res->comparison++;
//				}
//			}
//		}
//
//		k--;
//	}
//	return res;
//}


struct result * shell_sort(struct st* arr, int width, int height){
	struct result * res = (struct result*)malloc(sizeof(struct result));
	res->permutations = 0;
	res->comparison = 0;
	int k = height / 2;
	while (k != 0){
		for (int i = 0; i < k; i++){
			for (int j = i; j < height; j += k){
				for (int f = j; f >= 0; f -= k){
					if ((arr + f*width)->a1 < (arr + j*width)->a1){
						ultra_swap(arr, f, j, height, width);
						res->permutations++;
					}
					res->comparison++;
					if (((arr + f*width)->a1 == (arr + j*width)->a1) && ((arr + f*width)->a2 < (arr + j*width)->a2)){
						ultra_swap(arr, f, j, height, width);
						res->permutations++;
					}
					res->comparison++;
				}
			}
		}
		k--;
	}
	return res;
}
void quick_sort(struct st* arr, int top, int bot, int height, int width, struct result * rs){
	int i = top;
	int j = bot;
	int tmp;
	int c = (arr + (top + bot + 1) / 2 * width)->a1;
	while (i <= j){
		while ((arr + i*width)->a1 > c){
			i++;
			rs->comparison++;
		}
		while ((arr + j*width)->a1 < c){
			j--;
			rs->comparison++;
		}
		if (i <= j){
			if (((arr + i*width)->a1 == (arr+j*width)->a1) && ((arr+i*width)->a2 > (arr+j*width)->a2)){
			}
			else{
				ultra_swap(arr, i, j, height, width);
				rs->permutations++;
			}
			i++;
			j--;
			rs->comparison++;
		}
		rs->comparison++;
		put_to_file(stdout, arr, width, height);
		puts("\n");
	}
	if (top < j)quick_sort(arr, top, j, height, width, rs);
	if (i < bot)quick_sort(arr, i, bot, height, width, rs);
}
int main(){
	int width, height;
	setlocale(LC_ALL, "ukr");
	puts("¬ведiть ширину масиву");
	scanf("%d", &width);
	puts("¬ведiть висоту масиву");
	scanf("%d", &height);
	struct st* stru = (struct st*)malloc(height*width*sizeof(struct st));
	//before sorting
	rand_push(stru, width, height);
	put_to_file(stdout, stru, width, height);
	//FILE * fp = fopen("file.txt", "w");
	//put_to_file(fp, stru, width, height);
	puts("\n");
	//fclose(fp);


	//
	struct result * rs = shell_sort(stru, width, height);
	put_to_file(stdout, stru, width, height);
	//struct result *rs = (struct result *)malloc(sizeof(struct result));

	rs->comparison = 0;
	rs->permutations = 0;

	//quick_sort(stru, 0, height-1, height, width, rs);
	//put_to_file(stdout, stru, width, height);
	//after sorting
	//printf("%d %d\n", rs->permutations, rs->comparison);
	//FILE * fd = fopen("file1.txt", "w");
	//fprintf(fp, "%d %d\n", rs->permutations, rs->comparison);
	//fclose(fd);
	system("pause");
	return 0;
}
