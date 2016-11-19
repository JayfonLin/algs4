
#include <cstdio>
#include <ctime>

const int kMaxN = 10000000;
int x[kMaxN];


void insertion_sort(int n){
	int num;
	int i, j;

	for (i = 1; i < n; i++){
		num = x[i];
		for (j = i-1; 0 <= j; j--){
			if (num > x[j]){
				x[j+1] = x[j];
			}else{
				break;
			}
		}

		if (i != j+1){
			x[j+1] = num;
		}
		
	}
}


int main()
{
	int num;
	int count = 0;
	while (scanf("%d", &num) != EOF){
		x[count++] = num;
	}

	int start = clock();

	insertion_sort(count);

	int clicks = clock() - start;

	for (int i = 0; i < count; i++){
		printf("%d\n", x[i]);
	}

	printf("\n\ncost time:%f\n", (float)clicks / CLOCKS_PER_SEC);

	return 0;
}