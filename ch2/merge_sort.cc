#include <cstdio>
#include <vector>
#include <ctime>

const int kMaxN = 10000000;
int a[kMaxN];
int aux[kMaxN];


void merge(int a[], int low, int mid, int high){
	for (int k = low; k <= high; k++){
		aux[k] = a[k];
	}

	int i = low, j = mid+1;
	int merge_count = low;
	while (i <= mid && j <= high){
		if (aux[i] < aux[j]){
			a[merge_count++] = aux[i++];
		}else{
			a[merge_count++] = aux[j++];
		}
	}

	while (i <= mid){
		a[merge_count++] = aux[i++];
	}

	while (j <= high){
		a[merge_count++] = aux[j++];
	}
}

void insertion_sort(int a[], int low, int high){
	int v;
	int i, j;
	for (i = low+1; i <= high; i++){
		v = a[i];
		for (j = i; j > low; j--){
			if (v < a[j-1]){
				a[j] = a[j-1];
			}else{
				break;
			}
		}

		a[j] = v;
	}
}

void sort(int a[], int low, int high){
	if (high - low < 16{
		insertion_sort(a, low, high);
		return;
	}

	int mid = (low + high) / 2;
	sort(a, low, mid);
	sort(a, mid+1, high);

	merge(a, low, mid, high);

}




int main()
{

	int num;
	int count = 0;
	while (scanf("%d", &num) != EOF){
		a[count++] = num;
	}

	int start = clock();

	sort(a, 0, count-1);

	int clicks = clock() - start;
	for(int i = 0; i < count; i++){
		printf("%d\n", a[i]);
	}

	printf("\n\n%f\n", (float)clicks / CLOCKS_PER_SEC);

	return 0;
}