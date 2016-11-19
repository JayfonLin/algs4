
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdio>


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

	Value* get(Key key){
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

	void mdelete(const Key& key);

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
		Node* x = root_;
		while (x->left_ != NULL){
			x = x->left_;
		}

		return x->key_;
	}

	Key max(){
		Node* x = root_;
		while (x->right_ != NULL){
			x = x->right_;
		}

		return x->key_;
	}

	Key floor(const Key& key){
		Node* x = root_;
		Node* parent;
		while (x != NULL){
			if (x->key_ > key){
				parent = x;
				x = x->right_;
			}else if (x->key_ < key){
				x = x->left_;
			}else{
				return x->key_;
			}
		}

		return parent->key_;
	}

	Key ceiling(Key key);
	int rank(Key key);
	Key select(int k);
	void deleteMin();
	void deleteMax();
	int size(Key low, Key high);
	std::vector<Key> keys(Key low, Key high);
	std::vector<Key> keys();

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
		}
	};

	Node* put(Node* x, Key key, Value val){
		if (x == NULL){
			return new Node(key, val, 1);
		}
	
		if (x->key_ > key){
			x->left_ = put(x->left_, key, val);
		}else if (x->key_ < key){
			x->right_ = put(x->left_, key, val);
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

	std::string fl = tree.floor(f);
	printf("floor:%s\n", fl.c_str());

	return 0;
}