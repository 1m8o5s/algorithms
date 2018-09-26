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

void put_to_file(FILE * fp, struct st * arr, int width, int height){
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			fprintf(fp, "(%2d, %3d) ", (arr+i*width+j)->a1, (arr+i*width+j)->a2);
		}
		fprintf(fp, "\n");
	}
}

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
	}
	if (top < j)quick_sort(arr, top, j, height, width, rs);
	if (i < bot)quick_sort(arr, i, bot, height, width, rs);
}
int main(){
	int width, height;
	setlocale(LC_ALL, "ukr");
	puts("Введiть ширину масиву");
	scanf("%d", &width);
	puts("Введiть висоту масиву");
	scanf("%d", &height);

	struct st* stru = (struct st*)malloc(height*width*sizeof(struct st));
	rand_push(stru, width, height);

	put_to_file(stdout, stru, width, height);
	FILE * fp = fopen("file1.txt", "w");
	put_to_file(fp, stru, width, height);
	fclose(fp);
	puts("\n");

	//quick_sort
	struct result *rs = (struct result *)malloc(sizeof(struct result));
	rs->comparison = 0;
	rs->permutations = 0;
	quick_sort(stru, 0, height-1, height, width, rs);

	//shell_sort
	//struct result * rs = shell_sort(stru, width, height);
	
	printf("Кiлькiсть порiвнянь: %d Кiлькiсть перестановок: %d\n", rs->comparison, rs->permutations);
	put_to_file(stdout, stru, width, height);
	FILE * fd = fopen("file2.txt", "w");
	fprintf(fd, "Кiлькiсть порiвнянь: %d Кiлькiсть перестановок: %d\n", rs->comparison, rs->permutations);
	put_to_file(fd, stru, width, height);
	fclose(fd);
	system("pause");
	return 0;
}
