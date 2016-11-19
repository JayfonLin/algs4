#include <cstdio>
#include <vector>

void Sink(std::vector<int>& a, int k, int size){
	int i = 2*k+1;
	int temp;
	while (i <= size-1){
		if (i < size-1 && a[i] < a[i+1]){
			++i;
		}
		if (a[k] > a[i]){
			break;
		}

		temp = a[k];
		a[k] = a[i];
		a[i] = temp;

		k = i;
		i = 2*k+1;
	}
}



void Sort(std::vector<int>& a){
	int size = a.size();
	for (int i = (size-2)/2; i >= 0; --i){
		Sink(a, i, size);
	}

	
	int temp;
	while (size > 1){
		temp = a[0];
		a[0] = a[size-1];
		a[size-1] = temp;

		--size;
		Sink(a, 0, size);
	}
}

int main()
{
	int num;
	std::vector<int> a;
	while (scanf("%d", &num) != EOF){
		a.push_back(num);
	}

	Sort(a);

	for (int i = 0; i < a.size(); ++i){
		printf("%d\n", a[i]);
	}

	return 0;
}