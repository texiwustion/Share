#include <bits/stdc++.h>
using namespace std;

unordered_set<string> s;
int totN = 5;
int tree_count = 0;
int idx = 1;

void arrange(int arr[],int idx,int N,int &tree_count)
{
    if (N <= 0) {
        int total = unique(arr, arr+totN) - arr;
        if (total != totN) return;
        sort(arr, arr+totN, greater<int>());
        string str = "";
        for (int i = totN - 1; i >= 0; --i) {
            str += to_string(arr[i]) + " ";
        }
        if (s.count(str) == 0) { // 如果当前结果没有出现过，则输出
            s.insert(str);
            tree_count++;
            cout << str << endl;
        }
        return;
    }
    arr[N-1] = idx;
    arrange(arr, idx<<1, N-1, tree_count);
    arrange(arr, idx<<1|1, N-1, tree_count);
    arr[N-2] = idx<<1|1;
    arrange(arr, idx<<1, N-2, tree_count);
    arr[N-2] = idx<<1;
    arrange(arr, idx<<1|1, N-2, tree_count);
}
// 示例
int main() {
    int arr[totN];
    arrange(arr, idx, totN, tree_count);
    cout << tree_count << endl;
    return 0;
}