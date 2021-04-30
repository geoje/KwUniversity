#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef vector<vector<bool>> matrix;

vector<vector<int>> sets;
matrix dp;
int n, *arr;

void SubsetSumDP(int sum)
{
    // 첫번 째 열 모두 True: 합이 0인 것은 모두 가능하니깐!
    for (int i = 0; i < n; i++)
        dp[i][0] = true;
    // 첫 요소만 미리 처리
    dp[0][arr[0]] = true;

    // DP 테이블 만들기
    for (int i = 1; i < n; i++)
        for (int j = 1; j <= sum; j++)
            dp[i][j] = dp[i - 1][j] || (j >= arr[i] && dp[i - 1][j - arr[i]]);
}
void SetsFromDP(vector<int> set, int sum, int idx)
{
    // 부분집합 완성
    if (sum == 0)
    {
        reverse(set.begin(), set.end());
        sets.push_back(set);
        return;
    }

    // Sum이 딱 안 맞거나 더 이상 가져올 요소가 없으면 부분집합 실패
    if (sum < 0 || idx < 0)
        return;

    // 현재 idx 번째 요소를 가져올 수 있으면 가져오거나 or 안가져오거나
    if (dp[idx][sum])
    {
        // 안가져오면 다음 요소 탐색
        SetsFromDP(vector<int>(set), sum, idx - 1);

        // 가져오면 집합에 넣고 다음 요소 탐색
        set.push_back(arr[idx]);
        SetsFromDP(set, sum - arr[idx], idx - 1);
    }
}

int main()
{
    // Input

    while (!(cin >> n).fail())
    {
        arr = new int[n];

        int e, sum = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> e;
            arr[i] = e;
            sum += e;
        }

        if (sum % 2)
        {
            cout << "The sum is odd, so it can't be split in half.\n";
            delete[] arr;
            continue;
        }
        dp = matrix(n, vector<bool>(sum / 2 + 1));

        // Process
        sort(arr, arr + n);
        SubsetSumDP(sum / 2);
        SetsFromDP(vector<int>(), sum / 2, n - 1);

        // Output

        cout << sets.size() / 2 << '\n';
        for (int i = 0, j = sets.size() - 1; i < j; i++, j--)
        {
            cout << '{' << sets[i][0];
            for (int k = 1; k < sets[i].size(); k++)
                cout << ',' << sets[i][k];

            cout << "},{" << sets[j][0];

            for (int k = 1; k < sets[j].size(); k++)
                cout << ',' << sets[j][k];
            cout << "}\n";
        }

        delete[] arr;
        sets.clear();
    }

    return 0;
}
