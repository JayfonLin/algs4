
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <string>

template <class Key, class Value>
class RedBlackBST
{
public:
	RedBlackBST(){
		root_ = NULL;
	}

	void put(Key key, Value val){
		root_ = insert(root_, key, val);
		root_->color_ = kBlack;
	}

	Value* get(const Key& key){
		return get(root_, key);
	}

	bool isBalanced(){
		int black = 0;
		Node* x = root_;
		while (x != NULL){
			if (!isRed(x)) black++;
			x = x->left_;
		}

		return isBalanced(root_, black);
	}

	

private:
	struct Node
	{
		Key key_;
		Value value_;
		Node* left_;
		Node* right_;
		bool color_;

		Node(const Key& key, const Value& val, bool color){
			key_ = key;
			value_ = val;
			color_ = color;
			left_ = NULL;
			right_ = NULL;
		}
	};

	bool isBalanced(Node* x, int black){
		if (x == NULL) return black == 0;
		if (!isRed(x)) black--;
		return isBalanced(x->left_, black) && isBalanced(x->right_, black);
	}

	Value* get(Node* x, const Key& key){
		while (x != NULL){
			if (key < x->key_) x = x->left_;
			else if (key > x->key_) x = x->right_;
			else return &x->value_;
		}

		return NULL;
	}

	Node* insert(Node* h, const Key& key, const Value& val){
		if (h == NULL){
			return new Node(key, val, kRed);
		}

		if (key < h->key_){
			h->left_ = insert(h->left_, key, val);
		}else if (key > h->key_){
			h->right_ = insert(h->right_, key, val);
		}else{
			h->value_ = val;
		}

		if (isRed(h->right_) && !isRed(h->left_)) h = rotateLeft(h);
		if (isRed(h->left_) && isRed(h->left_->left_)) h = rotateRight(h);
		if (isRed(h->left_) && isRed(h->right_)) flipColors(h);

		return h;
	}

	bool isRed(Node* x){
		if (x == NULL) return false;

		return x->color_ == kRed; 
	}

	Node* rotateLeft(Node* h){
		assert( (h != NULL) && isRed(h->right_) );

		Node* x = h->right_;
		h->right_ = x->left_;
		x->left_ = h;
		x->color_ = h->color_;
		h->color_ = kRed;
		return x;
	}

	Node* rotateRight(Node* h){
		assert( (h != NULL) && isRed(h->left_) );

		Node* x = h->left_;
		h->left_ = x->right_;
		x->right_ = h;
		x->color_ = h->color_;
		h->color_ = kRed;
		return x;
	}

	void flipColors(Node* h){
		assert( !isRed(h) && isRed(h->left_) && isRed(h->right_) );

		h->color_ = kRed;
		h->left_->color_ = kBlack;
		h->right_->color_ = kBlack;
	}


	enum {
		kRed = 0,
		kBlack = 1
	};

	Node* root_;

};


int main(int argc, const char* argv[])
{
	RedBlackBST<std::string, int> tree;

	char str[80] = {0};
	int n;
	while (scanf("%s%d", &str, &n) != EOF){
		std::string s(str);
		tree.put(s, n);
	}

	printf("is balanced tree:%d\n", tree.isBalanced());

	char* f = const_cast<char*>(argv[1]);
	std::string test_str(f);

	int* val = tree.get(f);
	printf("key:%s get value:%d\n", f, *val);

	return 0;
}