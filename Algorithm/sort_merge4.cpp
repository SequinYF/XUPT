#include <iostream>
using namespace std;
typedef int Type;

void print(Type a[], int n)
{
    for (int i=0; i<n; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
}

void GetIndex(int a[], int t[], int n, int &m)
{
    // 记录自然分组后每个子串的起始坐标
	int j = 0;
	t[j++] = 0;
	for(int i = 0; i < n-1; i++) {
        if(a[i+1] < a[i]) {
		    t[j++] = i+1;
        }
	}
	m = j;      // m为自然分组的个数
}

void Merge(Type c[], Type d[], int l, int m, int r)
{
    // 合并c[l:m]和c[m+1:r]到d[1:r]
    int i = l, j = m + 1, k = l;
    while (i <= m && j <= r) {
        if (c[i] <= c[j]) {
            d[k++] = c[i++];
        } else {
            d[k++] = c[j++];
        }
    }
    if (i > m) {
        for (int q = j; q <= r; q++) {
            d[k++] = c[q];
        }
    } else {
        for (int q = i; q <= m; q++) {
            d[k++] = c[q];
        }
    }
}

void MergePass(Type x[], Type y[], Type t[], int s, int n, int cnt)
{
    // 合并自然分组后相邻的子数组
	int i = 0;

	while(i <= cnt - 2 * s) {
        // 当自然分组后的子数组个数为偶数时, r = n, 表示恰好两两合并
		int r = ((i + 2 * s) < cnt) ? t[i+2*s] : n;
		Merge(x, y, t[i], t[i+s]-1, r-1);
		i = i + 2 * s;
	}

    if(i + s < cnt) {
		Merge(x, y, t[i], t[i+s]-1, n-1);
    } else if (i < cnt) {
        // 剩余元素直接复制
        for(int j = t[i]; j <= n - 1; j++) {
		    y[j] = x[j];
        }
    }
}

void MergeSort(Type a[], Type t[], int n, int cnt)
{
    Type *b = new Type[n];
    int s = 1;

    while (s < cnt) {
        MergePass(a, b, t, s, n, cnt);      // 合并到数组b
        s += s;
        MergePass(b, a, t, s, n, cnt);      // 合并到数组a
        s += s;
    }

    delete[] b;
}

int main(int argc, char *argv[])
{
    Type a[] = {1, 5, 2, 3, 6, 0, 7, 4, 8};
    int len = sizeof(a) / sizeof(int);
    Type *t = new Type[len];
    int cnt;        // 记录自然分组个数

    GetIndex(a, t, len, cnt);
    MergeSort(a, t, len, cnt);
    print(a, len);

    delete[] t;

    return 0;
}
