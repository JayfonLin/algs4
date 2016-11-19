#include <cstdio>
#include <vector>
#include <ctime>

void ssort(std::vector<int>& a, int low, int high){
	int m;
	int pos;
	int temp;
	for (int i = low; i < high; i++){
		m = a[i];
		pos = i;
		for (int j = i+1; j < high; j++){
			if (a[j] < m){
				m = a[j];
				pos = j;
			}
		}

		a[pos] = a[i];
		a[i] = m;
		
	}
}

int main()
{

	std::vector<int> a;
	int num;

	while (scanf("%d", &num) != EOF) {
		a.push_back(num);
	}

	int start = clock();

	ssort(a, 0, a.size()-1);

	int clicks = clock() - start;
	for (std::vector<int>::iterator it = a.begin(); it != a.end(); it++){
		printf("%d\n", *it);
	}

	printf("\n\ncost time:%fs\n", (float)clicks/CLOCKS_PER_SEC);

	return 0;
}