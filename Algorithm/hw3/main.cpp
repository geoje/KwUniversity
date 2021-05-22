#include <iostream>
using namespace std;

int n, ansCount, curCount = 0;
bool map[20][20] = {
    false,
};
bool push[20][20] = {
    false,
};
bool answer[20][20] = {
    false,
};

const pair<int, int> arounds[] = {{0, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 0}};

bool promising(int i, int j)
{
    return i == 0 ? true : map[i - 1][j];
}
bool isValid(int i, int j)
{
    return i >= 0 && j >= 0 && i < n && j < n;
}
void turn(int i, int j)
{
    push[i][j] = !push[i][j];
    for (pair<int, int> around : arounds)
    {
        int ni = i + around.first;
        int nj = j + around.second;
        if (ni >= 0 && nj >= 0 && ni < n && nj < n)
            map[ni][nj] = !map[ni][nj];
    }
}
bool isSolution()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (map[i][j])
                return false;
    return true;
}
void UpdateAnswer()
{
    ansCount = curCount;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            answer[i][j] = push[i][j];
}
void light(int i, int j)
{
    if (i == n)
        return;

    // 다음 위치 제작
    bool nextLine = j == n - 1;
    int ni = nextLine ? i + 1 : i;
    int nj = nextLine ? 0 : j + 1;

    // 안누르고
    light(ni, nj);

    // 최적의 해를 찾았다면 업데이트
    if (isSolution() && curCount < ansCount)
        UpdateAnswer();

    // 프라미싱 하다면
    if (promising(i, j))
    {

        // 누르고
        turn(i, j);
        curCount++;
        light(ni, nj);

        // 최적의 해를 찾았다면 업데이트
        if (isSolution() && curCount < ansCount)
            UpdateAnswer();

        // 원상 복귀
        turn(i, j);
        curCount--;
    }
}

int main()
{
    char c;
    cin >> n;
    ansCount = n + 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            cin >> c;
            if (c == 'O')
                map[i][j] = true;
        }

    light(0, 0);

    if (ansCount == n + 1)
        cout << "no solution.\n";
    else
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cout << (answer[i][j] ? "O " : "# ");
            cout << '\n';
        }

    return 0;
}