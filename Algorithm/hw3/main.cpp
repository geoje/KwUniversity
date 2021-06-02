#include <iostream>
using namespace std;

int dx[] = {0, -1, 0, 1};
int dy[] = {1, 0, -1, 0};
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

void turn(int i, int j)
{
    map[i][j] = !map[i][j];
    push[i][j] = !push[i][j];
    for (int k = 0; k < 4; k++)
    {
        int ni = i + dx[k];
        int nj = j + dy[k];
        if (ni >= 0 && nj >= 0 && ni < n && nj < n)
            map[ni][nj] = !map[ni][nj];
    }
}
void light(int i, int j)
{
    // 체크 도중 이미 나온 답보다 쓰레기인 경우 탐색 끝냄
    if (curCount >= ansCount)
        return;

    // 현재 끝까지 내려 왔고
    if (i == n)
    {
        bool isSolution = true;
        for (int j = 0; j < n; j++)
            if (map[n - 1][j])
            {
                isSolution = false;
                break;
            }

        // 솔루션일 경우
        if (isSolution)
        {
            // Current best와 Answer을 업데이트
            ansCount = curCount;
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    answer[i][j] = push[i][j];
        }

        return;
    }

    // 다음 위치 계산
    bool nextLine = j == n - 1;
    int ni = nextLine ? i + 1 : i;
    int nj = nextLine ? 0 : j + 1;

    // Promising1: 첫번째 줄일 경우
    if (i == 0)
    {
        int memCount = curCount;
        // 안누르고 바로 체크
        light(ni, nj);

        // 누르고 체크
        turn(i, j);
        curCount = memCount + 1;
        light(ni, nj);

        // 체크가 끝나면 원상 복귀
        turn(i, j);
        curCount = memCount;
    }
    // Promising2: 위쪽 전등이 켜져있을 경우
    else if (map[i - 1][j])
    {
        // 현재 위치 누르고 체크
        turn(i, j);
        curCount++;
        light(ni, nj);

        // 체크가 끝나면 원상 복귀
        turn(i, j);
    }
    // Promising 하지 않다면 다음으로 넘기기
    else
        light(ni, nj);
}

int main()
{
    char c;
    cin >> n;
    ansCount = n * n + 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            cin >> c;
            if (c == 'O')
                map[i][j] = true;
        }

    light(0, 0);

    if (ansCount - 1 == n * n)
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