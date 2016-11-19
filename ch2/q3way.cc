
#include <cstdio>
#include <vector>
#include <ctime>
#include <cstdlib>


void insertion_sort(std::vector<int>& a, int low, int high){
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

void sort(std::vector<int>& a, int low, int high)
{
	if (high - low < 16){
		insertion_sort(a, low, high);
		return;
	}

	int p = a[low];
	int i = low+1;
	int lt = low, gt = high;
	
	int temp;
	while (i <= gt){
		if (a[i] < p){
			temp = a[lt];
			a[lt] = a[i];
			a[i] = temp;
			i++;
			lt++;
		}else if (a[i] > p){
			temp = a[gt];
			a[gt] = a[i];
			a[i] = temp;
			gt--;
		}else{
			i++;
		}
	}

	sort(a, low, lt-1);
	sort(a, gt+1, high);
}


void shuffle(std::vector<int>& a){
	int length = a.size();
	int exch_pos;
	int temp;
	for (int i = 0; i < length-1; i++){
		exch_pos = rand() % length;
		temp = a[exch_pos];
		a[exch_pos] = a[i];
		a[i] = temp;
	}
}

int main()
{
	int num;
	std::vector<int> a;
	int count = 0;
	while (scanf("%d", &num) != EOF){
		a.push_back(num);
		count++;
	}

	int start = clock();

	shuffle(a);
	
	sort(a, 0, count-1);
	int clicks = clock() - start;

	for (int i = 0; i < count; i++){
		printf("%d\n", a[i]);
	}

	printf("\n\ncost time:%f\n", (float)clicks / CLOCKS_PER_SEC);
	return 0;
}