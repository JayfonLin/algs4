#include <cstdio>
#include <cstdlib>

class MaxPQ
{
public:
	MaxPQ(int max){
		a_ = new int[max+1];
		size_ = 0;
		capacity_ = max+1;
	}

	MaxPQ(int a[], int size){
		a_ = new int[size+1];
		size_ = 0;
		capacity_ = size+1;

		for (int i = 0; i <= size; ++i){
			a_[i+1] = a[i];
		}

		for (int k = size_/2; k >= 1; --k){
			Sink(k);
		}
		
	}

	void Insert(int v){
		if (size_ >= capacity_-1){
			Resize(2*capacity_);
		}

		a_[++size_] = v;
		Swim(size_);

	}

	int Max(){
		return a_[1];
	}
	int DelMax(){
		int v = a_[1];

		int temp = a_[size_];
		a_[size_] = a_[1];
		a_[1] = temp;

		--size_;
		Sink(1);

		if ((size_ > 0) && (size_ == (capacity_-1)/4)){
			Resize(capacity_/2);
		}

		return v;
	}

	bool IsEmpty(){
		return size_ == 0;
	}

	int Size(){
		return size_;
	}

private:

	void Swim(int k){
		int temp;
		while (k > 1 && a_[k] > a_[k/2]){
			temp = a_[k];
			a_[k] = a_[k/2];
			a_[k/2] = temp;

			k = k/2;
		}
	}

	void Sink(int k){
		int i = 2*k;
		int temp;
		while (i <= size_){
			if (i < size_ && a_[i] < a_[i+1]){
				++i;
			}
			if (a_[k] >= a_[i]){
				break;
			}

			temp = a_[k];
			a_[k] = a_[i];
			a_[i] = temp;

			k = i;
			i = 2*k;
		}
	}

	void Resize(int capacity){
		if (capacity < size_){
			return;
		}

		int* temp = new int[capacity];
		for (int i = 1; i <= size_; ++i){
			temp[i] = a_[i];
		}

		a_ = temp;
		capacity_ = capacity;
	}

	int* a_;
	int size_;
	int capacity_;
};

void HeapSort(){
	MaxPQ pq(10);
	int num;
	while (scanf("%d", &num) != EOF){
		pq.Insert(num);
	}

	while(!pq.IsEmpty()){
		printf("%d\n", pq.DelMax());
	}
}

void TopM(const char* argv[]){
	int m = atoi(argv[1]);
	MaxPQ pq(m+1);
	int num;
	while (scanf("%d", &num) != EOF){
		
		pq.Insert(num);

		if (pq.Size() > m){
			pq.DelMax();
		}
	}

	while(!pq.IsEmpty()){
		printf("%d\n", pq.DelMax());
	}
}


int main(int argc, const char* argv[])
{
	TopM(argv);
	return 0;
}