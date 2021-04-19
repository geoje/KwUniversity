#include <iostream>
using namespace std;

int BinomialCoefficient(int n, int k)
{
    int arr[n + 1][k + 1];
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= min(i, k); j++)
            arr[i][j] = j == 0 || i == j ? 1 : arr[i - 1][j - 1] + arr[i - 1][j];

    return arr[n][k];
}

int main()
{
    int n, k;
    cin >> n >> k;

    cout << "\n>> " << BinomialCoefficient(n, k) << '\n';
}