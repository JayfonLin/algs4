//
// Created by Jeff on 2016/10/23.
//
// 问题：从无序数字序列中查找数字
// 方案：排序，二分查找
// 不足：有相同数值时，查找返回的是任意一个。可以优化，有相同元素时返回第1个数值
// 
//

#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdio>


int rank(int target, std::vector<int>& a){
    int lo = 0, hi = a.size()-1, mid;
    while (lo <= hi){
        mid = (lo + hi) / 2;
        if (target < a[mid]){
            hi = mid - 1;
        } else if (a[mid] < target){
            lo = mid + 1;
        } else{
            return mid;
        }
    }
    return -1;
}

void readFile(const char* path, std::vector<int>& a){
    std::ifstream in;
    in.open(path, std::ios_base::in);

    if (!in){
        printf("error: unable to open input file:%s", path);
        return;
    }

    int num;
    while (in){
        in >> num;
        a.push_back(num);
    }

    in.close();
    std::sort(a.begin(), a.end());
}

int main(int argc, char *argv[])
{
    std::vector<int> a;
    const char* path = argv[1];

    readFile(path, a);

    int target;
    int index;
    while (scanf("%d", &target) != EOF){
        index = rank(target, a);

        if (index != -1) {
            printf("target:%d in index:%d\n", target, index);
        }else{
            printf("target:%d not found\n", target);
        }
    }

    return 0;
}


