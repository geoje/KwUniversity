#include <iostream>
#include <algorithm>
#include <vector>
#define DOUBLE_ULONG_MAX 8589934591 // 2^33 - 1
using namespace std;

typedef long long ll;

int n, *arr;
ll **dp;
pair<vector<int>, vector<int>> subset;

// 부분집합 합 갯수에 대한 DP Table인 2차원 배열(dp)을 작성
ll SubsetSumDP(int sum)
{
    bool numerous = false;

    // 비밀이 숨겨져 있다
    for (int i = 0; i < n; i++)
        dp[i][0] = 1;
    // 첫 요소 처리
    dp[0][arr[0]] = 1;

    // DP 테이블 만들기
    for (int i = 1; i < n; i++)
        for (int j = 1; j <= sum; j++)
        {
            dp[i][j] = dp[i - 1][j] + (j >= arr[i] ? dp[i - 1][j - arr[i]] : 0);
            if (dp[i][j] > DOUBLE_ULONG_MAX)
                numerous = true;
        }

    return numerous ? -1 : dp[n - 1][sum] / 2;
}
// SubsetSumDP 함수에서 작성된 DP Table을 이용해 부분집합을 구함
void SubsetPair(int i, int j)
{
    if (i == 0)
    {
        if (j)
            subset.second.push_back(arr[0]);
        else
            subset.first.push_back(arr[0]);
        return;
    }

    // 내가 사용되지 않은 경우
    if (dp[i - 1][j])
    {
        SubsetPair(i - 1, j);
        subset.first.push_back(arr[i]);
    }
    // 내가 사용된 경우
    else
    {
        SubsetPair(i - 1, j - arr[i]);
        subset.second.push_back(arr[i]);
    }
}

int main()
{
    // Input
    while (!(cin >> n).fail())
    {
        arr = new int[n];

        int sum = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
            sum += arr[i];
        }

        if (sum % 2)
        {
            cout << "0\nNo subset (Sum is odd)\n";
            delete[] arr;
            continue;
        }

        // 2차원 배열 초기화
        int m = sum / 2 + 1;
        dp = new ll *[n];
        for (int i = 0; i < n; i++)
            dp[i] = new ll[m]{
                0,
            };

        // Process
        sort(arr, arr + n);
        ll count = SubsetSumDP(sum / 2);

        // Output
        if (count == 0)
            cout << "No subset (Count is zero)\n";
        else
        {
            SubsetPair(n - 1, m - 1);
            if (count == -1)
                cout << "NUMEROUS\n";
            else
                cout << count << '\n';

            cout << '{' << subset.first[0];
            for (int i = 1; i < subset.first.size(); i++)
                cout << ',' << subset.first[i];

            cout << "},{" << subset.second[0];

            for (int i = 1; i < subset.second.size(); i++)
                cout << ',' << subset.second[i];
            cout << "}\n";
        }

        // Free allocation
        for (int i = 0; i < n; i++)
            delete[] dp[i];
        delete[] dp, arr;

        subset.first.clear();
        subset.second.clear();
    }

    return 0;
}
