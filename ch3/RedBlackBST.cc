
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <string>
#include <stack>


template <class Key, class Value>
class RedBlackBST
{
public:
	RedBlackBST(){
		root_ = NULL;
	}

	void put(const Key& key, const Value& val){
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

	bool is23(){
		Node* x = root_;
		std::stack<Node*> s;
		if (x != NULL){
			s.push(x);
		}

		while(!s.empty()){
			x = s.top();
			s.pop();

			if (isRed(x->right_)){
				return false;
			}

			if (x != root_ && isRed(x) && isRed(x->left_)){
				return false;
			}

			if (x->left_ != NULL){
				s.push(x->left_);
			}

			if (x->right_ != NULL){
				s.push(x->right_);
			}
		}

		return true;
	}

	bool isBST(){
		return isBST(root_, NULL, NULL);
	}

	bool isRedBlackBST(){
		return isBST() && is23() && isBalanced(); 
	}

	void deleteMin(){
		if (isEmpty()){
			return;
		}

		if (!isRed(root_->left_) && !isRed(root_->right_)) {
			root_->color_ = kRed;
		}

		root_ = deleteMin(root_);
		if (!isEmpty()) {
			root_->color_ = kBlack;
		}

		assert(isRedBlackBST());
	}

	void deleteMax(){
		if (isEmpty()){
			return;
		}

		if (!isRed(root_->left_) && !isRed(root_->right_)){
			root_->color_ = kRed;
		}

		root_ = deleteMax(root_);
		if (!isEmpty()){
			root_->color_ = kBlack;
		}

		assert(isRedBlackBST());
	}

	bool isEmpty(){
		return root_ == NULL;
	}

	bool contains(const Key& key){
		return get(key) != NULL;
	}

	void mdelete(const Key& key){
		if (!contains(key)){
			return;
		}

		if (!isRed(root_->left_) && !isRed(root_->right_)){
			root_->color_ = kRed;
		}

		root_ = mdelete(root_, key);
		if (!isEmpty()){
			root_->color_ = kBlack;
		}

		assert(isRedBlackBST());
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

	Node* mdelete(Node* h, const Key& key){
		assert( get(h, key) != NULL );

		if (key < h->key_){
			if (!isRed(h->left_) && !isRed(h->left_->left_)){
				h = moveRedLeft(h);
			}
			h->left_ = mdelete(h->left_, key);
		}else{
			if (isRed(h->left_)){
				h = rotateRight(h);
			}
			if (key == h->key_ && h->right_ == NULL){
				delete h;
				return NULL;
			}
			if (!isRed(h->right_) && !isRed(h->right_->left_)){
				h = moveRedRight(h);
			}
			if (key == h->key_){
				Node* x = min(h->right_);
				h->key_ = x->key_;
				h->value_ = x->value_;

				h->right_ = deleteMin(h->right_);
			}
			else{
				h->right_ = mdelete(h->right_, key);
			}
		}

		return balance(h);
	}

	Node* deleteMin(Node* h){
		if (h->left_ == NULL){
			delete h;
			return NULL;
		}

		if (!isRed(h->left_) && !isRed(h->left_->left_)){
			h = moveRedLeft(h);
		}

		h->left_ = deleteMin(h->left_);
		return balance(h);
	}

	Node* deleteMax(Node* h){
		if (isRed(h->left_)){
			h = rotateRight(h);
		}

		if (h->right_ == NULL){
			delete h;
			return NULL;
		}

		if (!isRed(h->right_) && !isRed(h->right_->left_)){
			h = moveRedRight(h);
		}

		h->right_ = deleteMax(h->right_);

		return balance(h);
	}

	Node* moveRedLeft(Node* h){
		assert(h != NULL);
		assert( isRed(h) && !isRed(h->left_) && !isRed(h->left_->left_) );

		flipColors(h);
		if (isRed(h->right_->left_)){
			h->right_ = rotateRight(h->right_);
			h = rotateLeft(h);
			flipColors(h);
		}

		return h;
	}

	Node* moveRedRight(Node* h){
		assert(h != NULL);
		assert( isRed(h) && !isRed(h->right_) && !isRed(h->right_->left_));

		flipColors(h);
		if (isRed(h->left_->left_)){
			h = rotateRight(h);
			flipColors(h);
		}

		return h;
	}

	bool isBST(Node* x, const Key* min, const Key* max){
		if (x == NULL) return true;

		if (min != NULL && *min >= x->key_){
			return false;
		}

		if (max != NULL && *max <= x->key_){
			return false;
		}

		return isBST(x->left_, min, &x->key_) && isBST(x->right_, &x->key_, max);
	}

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

	Node* balance(Node* h){
		assert(h != NULL);

		if (isRed(h->right_)){
			h = rotateLeft(h);
		}

		if (isRed(h->left_) && isRed(h->left_->left_)){
			h = rotateRight(h);
		}

		if (isRed(h->left_) && isRed(h->right_)){
			flipColors(h);
		}

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
		assert( (h != NULL) && (h->left_ != NULL) && (h->right_ != NULL) );
		assert( (!isRed(h) && isRed(h->left_) && isRed(h->right_)) 
			|| (isRed(h) && !isRed(h->left_) && !isRed(h->right_)) );

		h->color_ = !h->color_;
		h->left_->color_ = !h->left_->color_;
		h->right_->color_ = !h->right_->color_;
	}

	Node* min(Node* h){
		assert( h != NULL);

		if (h->left_ == NULL){
			return h;
		}

		return min(h->left_);
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
	printf("is red-black binary tree:%d\n", tree.isRedBlackBST());

	char* f = const_cast<char*>(argv[1]);
	std::string test_str(f);

	int* val = tree.get(f);
	printf("key:%s get value:%d\n", f, *val);


	tree.mdelete(test_str);
	tree.deleteMin();
	tree.deleteMax();

	return 0;
}