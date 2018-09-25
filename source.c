void merge_sort(int * arr, int n){
	if (n != 1){
		int * arr1 = (int *)malloc(n / 2 * sizeof(int));
		int * arr2 = (int *)malloc((n - n/2)*sizeof(int));
		for (int i = 0; i < n / 2; i++){
			arr1[i] = arr[i];
		}
		for (int i = n/2; i < n; i++){
			arr2[i-n/2] = arr[i];
		}
		merge_sort(arr1, n / 2);
		merge_sort(arr2, n - n / 2);
		int g = 0, m = 0, t = 0;
		while (1){
			if ((g < n/2)&&(m < n-n/2)){
				if (arr1[g] < arr2[m]){
					arr[t] = arr1[g];
					n++;
				}
				else{
					arr[t] = arr2[m];
					m++;
				}
				t++;
			}
			else{
				if ((g >= n/2) && (m < n-n/2)){
					for (int j = m; j < n - n / 2; j++){
						arr[t++] = arr2[j];
					}
				}
				else if ((g >= 0) && (m < 0)){
					for (int j = g; j < n / 2; j++){
						arr[t++] = arr1[j];
					}
				}
				else{
					break;
				}
			}
		}
		free(arr1);
		free(arr2);
	}
}