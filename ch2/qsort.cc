#include <cstdio>
#include <vector>
#include <ctime>
#include <cstdlib>


int partition(std::vector<int>&a, int low, int high){
	int p = a[low];
	int i = low, j = high+1;
	while (1){
		do {
		 	i++;
		 } while (i <= high && a[i] < p);

		 do {
		 	j--;
		 } while (a[j] > p);

		 if (i > j){
		 	break;
		 }

		 int temp = a[i];
		 a[i] = a[j];
		 a[j] = temp;
	}

	int temp = a[low];
	a[low] = a[j];
	a[j] = temp;

	return j;
}

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
	if (high - low < 50){
		insertion_sort(a, low, high);
		return;
	}

	int mid = partition(a, low, high);

	sort(a, low, mid-1);
	sort(a, mid+1, high);
}


void shuffle(std::vector<int>& a){
	int length = a.size();
	int exch_pos;
	int temp;
	for (int i = length-1; i > 0; i--){
		exch_pos = rand() % i;
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