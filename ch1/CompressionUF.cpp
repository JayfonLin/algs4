//
// Created by Jeff on 2016/10/23.
//
// 问题：动态连通性
// 描述：构造一个连通网络，可以查询网络的连通分量、2个触点是否属于同一连通分量
// 可优化：路径压缩
//

#include <cstdio>


class UnionFind
{
public:
	UnionFind(int N){

		id = new int[N];
		sz = new int[N];
		for (int i = 0; i < N; i++){
			id[i] = i;
			sz[i] = 1;
		}

		count = N;
	}

	void Union(int p, int q){
		
		int p_root = Find(p);
		int q_root = Find(q);

		if (p_root == q_root){
			return;
		}

		
		if (sz[q_root] < sz[p_root]){
			id[q_root] = p_root;
			sz[p_root] += sz[q_root];
		}else{
			id[p_root] = q_root;
			sz[q_root] += sz[p_root];
		}
		

		count--;
	}

	int Find(int p){
		int root = p;

		while (root != id[root]){
			root = id[root];
		}
		
		int newp;
		while (p != root){
			newp = id[p];
			id[p] = root;
			p = newp;
		}
		
		return root;
	}

	bool Connected(int p, int q){
		return Find(p) == Find(q);
	}

	int Count(){
		return count;
	}

private:
	int* id;
	int* sz;
	int count;
};


int main(int argc, char *argv[])
{
	int N;
	scanf("%d", &N);

	int p, q;
	UnionFind uf(N);

	while (scanf("%d %d", &p, &q) != EOF){
		//printf("%d %d\n", p, q);
		uf.Union(p, q);
	}

	printf("%d components\n", uf.Count());
	return 0;
}