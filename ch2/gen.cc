#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[])
{
	int max_num = atoi(argv[1]);
	int gen_num = atoi(argv[2]);
	int i = 0;
	int r;
	srand(time(NULL));
	while (i++ < gen_num){
		r = rand() % max_num + 1;
		printf("%d\n", r);
	}

	return 0;
}