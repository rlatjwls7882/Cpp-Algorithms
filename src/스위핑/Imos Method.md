## Imos Method (いもす法)
구간(또는 영역)의 증가·감소량을 차분 배열(Difference Array)에 기록한 뒤, 최종적으로 누적 합을 구해 전체 상태를 복원하는 알고리즘

시간복잡도 : O(N<sup>D</sup>+Q) (N : 각 차원의 크기, D : 차원 수, Q : 쿼리 수)

![Imos0](https://github.com/user-attachments/assets/4c237655-42f6-487f-81a3-390e009ef54b)
Imos Method로 사각형을 구하는 방식은 4군데를 마킹한 후 오른쪽으로 쓸고, 아래로 쓸면 된다. 자세한 내용은 [Imos Lab](https://imoz.jp/algorithms/imos_method.html)에서 확인 가능하다.

Imos Method로 한 변의 길이가 4인 직각 삼각형을 구해보자.
![Imos1](https://github.com/user-attachments/assets/e762e773-db7f-46dc-a46f-882043ea6719)
이런식으로 6군데를 마킹한 후

![Imos2](https://github.com/user-attachments/assets/fff6e586-3c50-4927-b5d3-fb8eb8f48157)
오른쪽으로 한번 쓸고

![Imos3](https://github.com/user-attachments/assets/43ba44cc-43ff-4537-9da3-6fe793d7c550)
아래로 한번 쓸고

![Imos4](https://github.com/user-attachments/assets/ff209032-0311-49cb-9276-1474b6133e71)
오른쪽 대각선 아래로 한번 쓸면 완성된다.

[연습 문제 (백준 5541번)](https://www.acmicpc.net/problem/5541)

``` c++
/** https://www.acmicpc.net/problem/5541 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

const int MAX = 5002;

int board[MAX][MAX];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    while(m--) {
        int a, b, x; cin >> a >> b >> x;
        board[a-1][b-1]++;
        board[a-1][b]--;
        board[a+x][b-1]--;
        board[a+x][b+x+1]++;
        board[a+x+1][b]++;
        board[a+x+1][b+x+1]--;
    }

    // 오른쪽
    for(int i=0;i<=n;i++) {
        for(int j=0;j<=n;j++) {
            board[i][j+1] += board[i][j];
        }
    }

    // 아래쪽
    for(int i=0;i<=n;i++) {
        for(int j=0;j<=n;j++) {
            board[i+1][j] += board[i][j];
        }
    }

    // 오른쪽 대각선 아래
    for(int i=0;i<=n;i++) {
        for(int j=0;j<=n;j++) {
            board[i+1][j+1] += board[i][j];
        }
    }

    int cnt=0;
    for(int i=0;i<=n;i++) {
        for(int j=0;j<=n;j++) {
            if(board[i][j]) cnt++;
        }
    }
    cout << cnt;
}
```

![Imos5](https://github.com/user-attachments/assets/d06e1cac-385e-433e-8688-0f9b8bf6fb36)
연습 문제의 최종 결과는 이렇게 된다.
