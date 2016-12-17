#include <cstdio>
#include <string>
#include <cstring>

class KMP
{

public:
	KMP(const std::string& pat){
		pattern_ = pat;
		int M = pattern_.length();
		int R = 256;
		dfa_ = new int*[R];

		for (int i = 0; i < R; i++){
			dfa_[i] = new int[M];
			memset(dfa_[i], 0, M*sizeof(int));
		}

		dfa_[pattern_[0]][0] = 1;
		for (int X = 0, j = 1; j < M; j++){
			for (int c = 0; c < R; c++){
				dfa_[c][j] = dfa_[c][X];
			}

			dfa_[pattern_[j]][j] = j+1;
			X = dfa_[pattern_[j]][X];
		}
	}

	int search(const std::string& txt){
		int i;
		int j;
		int N = txt.length();
		int M = pattern_.length();

		for (i = 0, j = 0; i < N && j < M; i++){
			j = dfa_[txt[i]][j];
		}

		if (j == M){
			return i-M;
		}
		else{
			return -1;
		}
	}

private:
	std::string pattern_;
	int** dfa_;

};


int main(int argc, const char* argv[])
{
	std::string pat(argv[1]);
	std::string txt(argv[2]);
	KMP kmp(pat);
	int result = kmp.search(txt);

	printf("search result:%d\n", result);
	return 0;
}