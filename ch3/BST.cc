
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <iostream>


template <class Key, class Value>
class BST
{
public:
	BST(){
		root_ = NULL;
	}

	void put(Key key, Value val){
		root_ = put(root_, key, val);
	}

	Value* get(const Key& key){
		Node* x = root_;

		while (x != NULL){
			if (x->key_ > key){
				x = x->left_;
			}else if (x->key_ < key){
				x = x->right_;
			}else{
				return &x->value_;
			}
		}

		return NULL;
	}

	void mdelete(const Key& key){
		root_ = mdelete(root_, key);
	}



	bool contains(const Key& key){
		Node* x = root_;

		while (x != NULL){
			if (x->key_ > key){
				x = x->left_;
			}else if (x->key_ < key){
				x = x->right_;
			}else{
				return true;
			}
		}

		return false;
	}

	bool isEmpty(){
		return size() == 0;
	}

	int size(){
		return size(root_);
	}

	Key min(){
		return min(root_)->key_;
	}

	

	Key max(){
		Node* x = root_;
		while (x->right_ != NULL){
			x = x->right_;
		}

		return x->key_;
	}

	const Key* floor(const Key& key){
		Node* x = floor(root_, key);
		if (x == NULL) return NULL;
		else return &x->key_;
	}
	

	const Key* ceiling(const Key& key){
		Node* x = ceiling(root_, key);
		if (x == NULL) return NULL;
		else return &x->key_;
	}

	int rank(const Key& key){
		return rank(key, root_);
	}


	const Key* select(int k){
		if (k < 0 || k >= size()) return NULL;
		Node* x = select(root_, k);
		return &x->key_;
	}


	void deleteMin(){
		if (isEmpty()) return;

		root_ = deleteMin(root_);
	}

	void deleteMax(){
		if (isEmpty()) return;

		root_ = deleteMax(root_);
	}


	int size(const Key& low, const Key& high){
		if (low > high) return 0;
		if (contains(high)) return rank(high) - rank(low) + 1;

		return rank(high) - rank(low);
	}

	std::vector<const Key*> keys(const Key& low, const Key& high){
		std::vector<const Key*> v;
		keys(root_, v, low, high);

		return v;
	}

	

	std::vector<const Key*> keys(){
		std::vector<const Key*> v;
		keys(root_, v, min(), max());
		return v;
	}

private:
	struct Node
	{
		Key key_;
		Value value_;
		Node* left_;
		Node* right_;
		int size_;

		Node(Key key, Value val, int size){
			key_ = key;
			value_ = val;
			size_ = size;
			left_ = NULL;
			right_ = NULL;
		}
	};

	Node* min(Node* x){
		if (x->left_ == NULL) return x;
		else return min(x->left_);
	}

	Node* mdelete(Node* x, const Key& key){
		if (x == NULL) return NULL;

		if (key < x->key_){
			x->left_ = mdelete(x->left_, key);
		}else if (key > x->key_){
			x->right_ = mdelete(x->right_, key);
		}else{
			if (x->right_ == NULL) return x->left_;
			if (x->left_ == NULL) return x->right_;

			Node* t = x;
			x = min(t->right_);
			x->right_ = noReleaseDeleteMin(t->right_);
			x->left_ = t->left_;

			delete t;
		}

		x->size_ = size(x->left_) + size(x->right_) + 1;
		return x;
	}

	Node* deleteMin(Node* x){
		if (x->left_ == NULL){
			Node* right = x->right_;
			delete x;
			return right;	
		} 

		x->left_ = deleteMin(x->left_);
		x->size_ = size(x->left_) + size(x->right_) + 1;
		return x; 
	}

	Node* noReleaseDeleteMin(Node* x){
		if (x->left_ == NULL){
			return x->right_;
		} 

		x->left_ = noReleaseDeleteMin(x->left_);
		x->size_ = size(x->left_) + size(x->right_) + 1;
		return x; 
	}

	Node* deleteMax(Node* x){
		if (x->right_ == NULL){
			Node* left = x->left_;
			delete x;
			return left;
		}

		x->right_ = deleteMax(x->right_);
		x->size_ = size(x->left_) + size(x->right_) + 1;
		return x;
	}

	void keys(Node* x, std::vector<const Key*>& v, const Key& low, const Key& high){
		if (x == NULL) return;

		if (low < x->key_) keys(x->left_, v, low, high);
		if (low <= x->key_ && x->key_ <= high) v.push_back(&x->key_);
		if (x->key_ < high) keys(x->right_, v, low, high);
	}


	Node* select(Node* x, int k){
		int t = size(x->left_);
		if (t > k) return select(x->left_, k);
		else if (t < k) return select(x->right_, k-t-1);
		else return x;
	}

	Node* put(Node* x, Key key, Value val){
		if (x == NULL){
			return new Node(key, val, 1);
		}
	
		if (x->key_ > key){
			x->left_ = put(x->left_, key, val);
		}else if (x->key_ < key){
			x->right_ = put(x->right_, key, val);
		}else{
			x->value_ = val;
		}
	

		x->size_ = 1 + size(x->left_) + size(x->right_);
		return x;
	}

	int size(const Node* x){
		if (x == NULL){
			return 0;
		}
		return x->size_;
	}

	Node* floor(Node* x, const Key& key){
		if (x == NULL) return NULL;

		if (key < x->key_){
			return floor(x->left_, key);
		}else if (key == x->key_){
			return x;
		}

		Node* t = floor(x->right_, key);
		if (t != NULL) return t;
		else return x;
	}

	Node* ceiling(Node* x, const Key& key){
		if (x == NULL) return NULL;

		if (key > x->key_){
			return ceiling(x->right_, key);
		}else if (key == x->key_){
			return x;
		}

		Node* t = ceiling(x->left_, key);
		if (t != NULL) return t;
		else return x;
	}


	int rank(const Key& key, Node* x){
		if (x == NULL) return 0;
		if (key < x->key_) return rank(key, x->left_);
		else if (key > x->key_) return 1 + size(x->left_) + rank(key, x->right_);
		else return size(x->left_);
	}

	Node* root_;

};


int main(int argc, const char* argv[])
{
	BST<std::string, int> tree;

	char str[80] = {0};
	int n;
	while (scanf("%s%d", &str, &n) != EOF){
		std::string s(str);
		tree.put(s, n);
	}

	char* f = const_cast<char*>(argv[1]);
	std::string test_str(f);

	
	//int* n1 = tree.get(f);
	//printf("test tree get:%s value:%d\n", f, *n1);

	//const std::string* f2 = tree.ceiling(f);
	//printf("ceiling:%s\n", f2->c_str());

	//int s = tree.size();
	//printf("size %d\n", s);
	

	//std::string key(f);
	//int r = tree.rank(key);
	//printf("key:%s rank %d\n", key.c_str(), r);

	//printf("tree contains:%s %d\n", f, tree.contains(test_str));

	//int sn = atoi(f);
	//printf("select %d get key:%s\n", sn, tree.select(sn)->c_str());

	//char* f2 = const_cast<char*>(argv[2]);
	//std::string test_str2(f2);
	//std::vector<const std::string*> rkeys = tree.keys(test_str, test_str2);
	//for (std::vector<const std::string*>::iterator it = rkeys.begin(); it != rkeys.end(); it++){
	//	std::cout << *(*it) << " ";
	//}

	//char* f2 = const_cast<char*>(argv[2]);
	//std::string test_str2(f2);
	//int sn = tree.size(test_str, test_str2);
	//printf("size between %s ~ %s is %d\n", f, f2, sn);

	//tree.deleteMin();
	//printf("after delete min, min is %s\n", tree.min().c_str());

	//tree.deleteMax();
	//printf("after delete max, max is %s\n", tree.max().c_str());

	
	
	tree.mdelete(test_str);
	printf("after delete %s, keys are:", f);

	std::vector<const std::string*> keys = tree.keys();
	for (std::vector<const std::string*>::iterator it = keys.begin(); it != keys.end(); it++){
		printf(" %s", (*it)->c_str());
	}
	printf("\n");
	
	return 0;
}