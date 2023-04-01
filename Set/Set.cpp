#include <bits/stdc++.h>
using namespace std;

class Array {
protected:
    int *arr;
    unsigned int nSize;
    void expand(unsigned int offset) {
        int *p = new int [nSize + offset];
        if (arr != NULL) {
            for (unsigned int i = 0; i < nSize; ++i) {
                p[i] = arr[i];
            }
            delete [] arr;
        }
        arr = p;
        nSize += offset;
    }
public:
    Array(unsigned int n) {
        if (0 == n) {
            nSize = 0;
            arr = NULL;
        }
        else {
            nSize = n;
            arr = new int [nSize];
        }
    }
    Array(const Array& obj) {
        if (NULL == obj.arr) {
            nSize = 0;
            arr = NULL;
        }
        else {
            nSize = obj.nSize;
            arr = new int[nSize];
            for (unsigned int i = 0; i < nSize; ++i) {
                arr[i] = obj.arr[i];
            }
        }
    }
    ~Array() {
        if (NULL != arr) {
            delete [] arr;
            nSize = 0;
        }
    }
    int& operator[](unsigned int index) {
        if (index >= nSize) {
            expand(index - nSize + 1);
        }
        return arr[index];
    }
    int operator[](unsigned int index) const {
        if (index < nSize) {
            return arr[index];
        }
        return 0;
    }
    Array& operator=(const Array& obj) {
        if (this == &obj)
            return *this;

        if (NULL != arr)
            delete [] arr;

        if (NULL == obj.arr) {
            nSize = obj.nSize;
            arr = NULL;
            return *this;
        }

        nSize = obj.nSize;
        arr = new int[nSize];
        for (unsigned int i = 0; i < nSize; ++i)
            arr[i] = obj.arr[i];
        return *this;
    }
};

class Set : protected Array {
public:
    Set(unsigned int n = 0) : Array(n) {}

    void insert(int value) {
        //检查元素是否已存在
        for (unsigned int i = 0; i < nSize; ++i) {
            if (arr[i] == value) {
                return;
            }
        }
        //将元素插入到合适位置
        unsigned int i;
        for (i = 0; i < nSize; ++i) {
            if (arr[i] > value) {
                break;
            }
        }
        //将元素插入到位置i
        if (i >= nSize) {
            //需要扩展数组大小
            expand(1);
            arr[i] = value;
        } else {
            //将元素插入位置i
            expand(1); //可能的bug: 若预先申请了空间，不能直接expand 
            for (unsigned int j = nSize; j > i; --j) {
                arr[j] = arr[j-1];
            }
            arr[i] = value;
        }
    }

    Set operator*(const Set& other) const { //交
        Set result;
        unsigned int i = 0;
        unsigned int j = 0;
        while (i < nSize && j < other.nSize) {
            if (arr[i] < other.arr[j]) {
                ++i;
            } else if (arr[i] > other.arr[j]) {
                ++j;
            } else {
                result.insert(arr[i]);
                ++i;
                ++j;
            }
        }
        return result;
    }

    Set operator+(const Set& other) const { //并
        Set result(nSize + other.nSize);
        unsigned int i = 0;
        unsigned int j = 0;
        unsigned int pos = 0;
        int nOverSize = 0;
        while (i < nSize && j < other.nSize) {
            if (arr[i] < other.arr[j]) {
                result[pos] = arr[i];
                ++i;
            } else if (arr[i] > other.arr[j]) {
                result[pos] = other.arr[j];
                ++j;
            } else {
                result[pos] = arr[i];
                ++i;
                ++j;
                nOverSize++;
            }
            ++pos;
        }
        //将剩余元素复制到结果集中
        while (i < nSize) {
            result[pos] = arr[i];
            ++i;
            ++pos;
        }
        while (j < other.nSize) {
            result[pos] = other.arr[j];
            ++j;
            ++pos;
        }
        result.expand(-nOverSize); //减去多余的size
        return result;
    }

    Set operator-(const Set& other) const {
        Set result;
        unsigned int i = 0;
        unsigned int j = 0;
        while (i < nSize && j < other.nSize) {
            if (arr[i] < other.arr[j]) {
                result.insert(arr[i]);
                ++i;
            } else if (arr[i] > other.arr[j]) {
                ++j;
            } else {
                ++i;
                ++j;
            }
        }
        //将剩余元素复制到结果集中
        while (i < nSize) {
            result.insert(arr[i]);
            ++i;
        }
        return result;
    }

    void display() const {
      if (nSize == 0) {
          std::cout << "" << std::endl;
          return;
      }
      for (unsigned int i = 0; i <= nSize-1; ++i) {
          std::cout << arr[i] << " ";
      }
      cout << std::endl;
    }
};

int main()
{
  int m, n, x;
  Set a, b, c, d, e;
  cin >> m;
  for (int i = 0; i < m; ++i)  {
    cin >> x;
    a.insert(x);
  }
  cin >> n;
  for (int i = 0; i < n; ++i)  {
    cin >> x;
    b.insert(x);
  }
  a.display();
  b.display();
  c = a + b; //注意符号意义，这里用+表示并，*表示交
  d = a * b;
  e = a - b;
  c.display();
  d.display();
  e.display();
  return 0;
}