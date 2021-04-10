#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
typedef vector<vector<ll>> matrix;

ll *mem;

// Recursive: O(r^n)
ll Babo1(int n)
{
    return n < 2 ? 1 : Babo1(n - 1) + Babo1(n - 2) + 1;
}

// Iterative: O(n)
ll Babo2(int n)
{
    ll *arr = new ll[n + 1];

    arr[0] = arr[1] = 1;
    for (int i = 2; i <= n; i++)
        arr[i] = arr[i - 1] + arr[i - 2] + 1;

    return arr[n];
}

// Recursive: O(n)
ll Babo3(int n)
{
    return mem[n] ? mem[n] : mem[n] = Babo3(n - 1) + Babo3(n - 2) + 1;
}

// Matrix: O(log(n))
matrix operator*(matrix &a, matrix &b)
{
    int n = a.size();
    matrix c(n, vector<ll>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                c[i][j] += a[i][k] * b[k][j];

    return c;
}
ll Babo4(int n)
{
    matrix ans = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
    };
    matrix base = {
        {1, 1, 1},
        {1, 0, 0},
        {0, 0, 1},
    };

    for (--n; n > 0; n /= 2)
    {
        if (n & 1)
            ans = ans * base;
        base = base * base;
    }

    return ans[0][0] + ans[0][1] + ans[0][2];
}

int main()
{
    clock_t start, end;
    int n;
    cin >> n;
    cout << "\n";

    // cout << "---- Recursive O(r^n) ----\n";
    // start = clock();
    // for (int i = 0; i < n; i++)
    //     cout << babo1(i) << ' ';
    // end = clock();
    // cout << "\n>> "
    //      << ((float)end - start) / CLOCKS_PER_SEC << " sec\n\n";

    cout << "---- Iterative: O(n) ----\n";
    start = clock();
    for (int i = 0; i < n; i++)
        cout << Babo2(i) << ' ';
    end = clock();
    cout << "\n>> "
         << ((float)end - start) / CLOCKS_PER_SEC << " sec\n\n";

    cout << "---- Recursive: O(n) ----\n";
    start = clock();
    mem = new ll[n + 1]();
    mem[0] = mem[1] = 1;
    for (int i = 0; i < n; i++)
        cout << Babo3(i) << ' ';
    end = clock();
    cout << "\n>> "
         << ((float)end - start) / CLOCKS_PER_SEC << " sec\n\n";

    cout << "---- Matrix: O(log(n)) ----\n";
    start = clock();
    for (int i = 0; i < n; i++)
        cout << Babo4(i) << ' ';
    end = clock();
    cout << "\n>> "
         << ((float)end - start) / CLOCKS_PER_SEC << " sec\n\n";
}