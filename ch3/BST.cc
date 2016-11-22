
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cassert>

template <class Key, class Value>
class BST
{
public:
	BST(){
		root_ = NULL;
	}

	void put(const Key& key, const Value& val){
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

	const Key* min(){
		if (isEmpty()) return NULL;

		return &min(root_)->key_;
	}

	

	const Key* max(){
		if (isEmpty()) return NULL;

		Node* x = root_;
		while (x->right_ != NULL){
			x = x->right_;
		}

		return &x->key_;
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
		keys(root_, v, *min(), *max());
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

		Node(const Key& key, const Value& val, int size){
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

	Node* put(Node* x, const Key& key, const Value& val){
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

/*
bulid a binary tree below:

                               haha
                                |
            apple               |          peach
              |                              |
         NULL |  bitch               hello   |    wocao
                  |                    |            
              NULL|good            NULL|kaka 
*/
void TestBuildTree(BST<std::string, int>& tree){

	tree.put(std::string("haha"), 20);
	tree.put(std::string("apple"), 93);
	tree.put(std::string("peach"), 19);
	tree.put(std::string("bitch"), 18);
	tree.put(std::string("hello"), 28);
	tree.put(std::string("wocao"), 74);
	tree.put(std::string("good"), 77);
	tree.put(std::string("kaka"), 91);

}

void TestTreeGet(BST<std::string, int>& tree){

	std::string s1("hello");
	int* retNum = tree.get(s1);
	if (*retNum == 28){
		printf("tree.get passed.\n");
	}else{
		printf("tree.get failed.\n");
	}

	std::string s2("notFound");
	int* retNum2 = tree.get(s2);
	if (retNum2 == NULL){
		printf("tree.get passed.\n");
	}else{
		printf("tree.get failed.\n");
	}
}

void TestFloor(BST<std::string, int>& tree){
	std::string s1("wocao");
	const std::string* floor1 = tree.floor(s1);

	std::string s2("hella");
	const std::string* floor2 = tree.floor(s2);
	const std::string expected2("haha");

	if (*floor1 == s1 && *floor2 == expected2){
		printf("tree.floor passed.\n");
	}else{
		printf("tree.floor failed.\n");
	}

}

void TestTreeCeiling(BST<std::string, int>& tree){
	std::string s1("bitch");
	const std::string* ceiling1 = tree.ceiling(s1);

	std::string s2("goodd");
	const std::string* ceiling2 = tree.ceiling(s2);
	std::string expected2("haha");
	if (*ceiling1 == s1 && *ceiling2 == expected2){
		printf("tree.ceiling passed.\n");
	}else{
		printf("tree.ceiling failed.\n");
	}

}

void TestTreeSize(BST<std::string, int>& tree){
	int size = tree.size();
	if (size == 8){
		printf("tree.size passed.\n");
	}else{
		printf("tree.size failed.\n");
	}
}

void TestTreeRank(BST<std::string, int>& tree){
	std::string s1("peach");
	int r1 = tree.rank(s1);

	std::string s2("applf");
	int r2 = tree.rank(s2);

	if (r1 == 6 && r2 == 1){
		printf("tree.rank passed.\n");
	}else{
		printf("tree.rank failed.\n");
	}
}

void TestTreeSelect(BST<std::string, int>& tree){
	const std::string* s1 = tree.select(5);
	std::string expected1("kaka");

	const std::string* s2 = tree.select(-1);
	const std::string* s3 = tree.select(8);

	if (*s1 == expected1 && s2 == NULL && s3 == NULL){
		printf("tree.select passed.\n");
	}else{
		printf("tree.select failed.\n");
	}

}

void TestTreeContains(BST<std::string, int>& tree){
	const std::string s1("good");
	bool c1 = tree.contains(s1);

	const std::string s2("notContains");
	bool c2 = tree.contains(s2);

	if (c1 && !c2){
		printf("tree.contains passed.\n");
	}else{
		printf("tree.contains failed.\n");
	}

}

void TestTreeKeys(BST<std::string, int>& tree){
	std::vector<const std::string*> v = tree.keys();
	assert(*v[0] == std::string("apple"));
	assert(*v[1] == std::string("bitch"));
	assert(*v[2] == std::string("good"));
	assert(*v[3] == std::string("haha"));
	assert(*v[4] == std::string("hello"));
	assert(*v[5] == std::string("kaka"));
	assert(*v[6] == std::string("peach"));
	assert(*v[7] == std::string("wocao"));

	printf("tree.keys passed.\n");
}

void TestDeleteMin(BST<std::string, int>& tree){
	
	tree.deleteMin();
	const std::string* s1 = tree.min();
	if (*s1 == std::string("bitch")){
		printf("tree.deleteMin passed.\n");
	}else{
		printf("tree.deleteMin failed.\n");
	}
}

void TestDeleteMax(BST<std::string, int>& tree){

	tree.deleteMax();
	const std::string* s1 = tree.max();
	if (*s1 == std::string("peach")){
		printf("tree.deleteMax passed.\n");
	}else{
		printf("tree.deleteMax failed.\n");
	}
}

void TestTreeDelete(BST<std::string, int>& tree){
	std::string d("peach");
	tree.mdelete(d);

	std::string d2("notExist");
	tree.mdelete(d2);

	if (!tree.contains(d) && !tree.contains(d2)){
		printf("tree.mdelete passed.\n");
	}else{
		printf("tree.mdelete failed.\n");
	}

	std::vector<const std::string*> ks = tree.keys();
	for (std::vector<const std::string*>::iterator it = ks.begin(); it != ks.end(); ++it){
		tree.mdelete(*(*it));
	}

	if (tree.isEmpty()){
		printf("tree.mdelete passed.\n");
	}else{
		printf("tree.mdelete failed.\n");
	}

}

void Test(){
	BST<std::string, int> tree;
	TestBuildTree(tree);
	TestTreeGet(tree);
	TestFloor(tree);
	TestTreeCeiling(tree);
	TestTreeSize(tree);
	TestTreeRank(tree);
	TestTreeSelect(tree);
	TestTreeContains(tree);
	TestTreeKeys(tree);
	TestDeleteMin(tree);
	TestDeleteMax(tree);
	TestTreeDelete(tree);
}


int main(int argc, const char* argv[])
{

	Test();

	return 0;
}