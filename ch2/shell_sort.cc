
#include <cstdio>
#include <ctime>
#include <algorithm>

const int kMaxN = 10000000;
int x[kMaxN];

int cmp(int a, int b){
	return a > b;
}


void shell_sort(int n){
	int h = 1;
	int sub = 3;
	while (h < n/sub){
		h = h*sub + 1;
	}

	int i, j;
	int num;
	while (h >= 1){
		for (i = h; i < n; i++){
			num = x[i];

			for (j = i; j >= h; j -= h){
				if (num > x[j-h]){
					x[j] = x[j-h];
				}else{
					break;
				}
			}

			if (i != j){
				x[j] = num;
			}
			
		}

		h /= sub;
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

	//shell_sort(count);
	std::sort(x, x+count, cmp);

	int clicks = clock() - start;

	for (int i = 0; i < count; i++){
		printf("%d\n", x[i]);
	}

	printf("\n\ncost time:%f\n", (float)clicks / CLOCKS_PER_SEC);

	return 0;
}