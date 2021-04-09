#include <iostream>
using namespace std;

typedef long long ll;

ll *llMem;

void main()
{
    int n;
    cin >> n;

    // For babo3()
    llMem = new ll[n + 1]();
    llMem[0] = llMem[1] = 1;
    // babo3(n);
    delete[] llMem;
}

// Recursive: O(r^n)
ll babo1(int n)
{
    return n < 2 ? 1 : babo1(n - 1) + babo1(n - 2) + 1;
}

// Iterative: O(n)
ll babo2(int n)
{
    int *arr = new int[n + 1];
    arr[0] = arr[1] = 1;

    for (int i = 2; i <= n; i++)
        arr[i] = arr[i - 1] + arr[i - 2] + 1;

    return arr[n];
}

// Recursive: O(n)
ll babo3(int n)
{
    return llMem[n] ? llMem[n] : llMem[n] = babo3(n - 1) + babo3(n - 2) + 1;
}

// Matrix: O(log(n))
ll babo4(int n)
{
    ll mtAns[2][2] = {{1, 1},
                      {1, 0}};
    ll mtMul[2][2] = {{1, 1},
                      {1, 0}};

    if (n < 2)
        return 1;

    for (; n > 0; n >> 1)
        if (n & 1)
            ;
}
ll **MulBaboMatrix(ll (*a)[2], ll (*b)[2])
{
    ll mtMul[2][2] = {{1, 1},
                      {1, 0}};
}