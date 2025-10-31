## Walking on Segment Tree
세그먼트 트리의 구간 합을 이용하여 이분 탐색으로 k번째 원소를 찾는 테크닉

시간 복잡도 : O(QlogN) (Q : 쿼리의 수)

1 ~ N 값에서 k번째로 작은 값을 뽑아내는 상황을 가정하자.

![](https://github.com/user-attachments/assets/e429f587-0b4d-4188-9337-b69e80b1618e)

처음에 모든 정점에 1을 넣어 놓는다.

![](https://github.com/user-attachments/assets/9f679c39-ccc5-4689-8403-1037f9ef3014)

예를 들어 남은 원소 중 3번째로 작은 값 찾는다면,
현재 정점 (1번)에서 왼쪽 자식의 구간 합이 2이기 때문에 적어도 왼쪽 자식 구간은 고려 안해도 된다. (k에 2를 빼고 오른쪽 자식으로 이동.)

![](https://github.com/user-attachments/assets/792c8bea-ad14-49ee-b549-05e9fde5ef99)

현재 정점 (3번)에서 왼쪽 자식의 구간 합이 1이기 때문에 왼쪽 자식 구간에 있을 것이다. (왼쪽 자식으로 이동.)

![](https://github.com/user-attachments/assets/e3ca51b2-4b08-43c9-99a7-8e941d2fba53)

현재 정점 (6번)에 자식이 없기 때문에 탐색을 끝내고 할당된 숫자를 하나 지우고 업데이트한다.

[연습 문제 (백준 31492번)](https://www.acmicpc.net/problem/31492)

``` c++
/** http://boj.kr/9211d3f3c4204034921c0bc3ac2b7dcb 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

const int MAX = 4'000'001;
int a[MAX], _size=1, arr[MAX*4];

// 이미 방문한 정점은 방문 처리 (남은 정점에서 제외)
void update(int x) {
    arr[x]=0;
    while(x>1) {
        x>>=1;
        arr[x] = arr[x*2]+arr[x*2+1];
    }
}

/** 
 * 방문 안한 수 중 k번째 원소 찾기
 * - 해당 정점을 찾았으면 방문 처리 후 return
 * - 왼쪽 구간 합이 k보다 크거나 같으면 왼쪽으로 이동 (walking)
 * - 왼쪽 구간 합이 k보다 작으면 오른쪽으로 이동 (k는 왼쪽 구간만큼 뺀 값으로 설정)
 */
int search(int val, int nodeNum=1, int nodeL=0, int nodeR=_size/2-1) {
    if(nodeL==nodeR) {
        update(nodeNum);
        return nodeL+1;
    }
    int mid = nodeL+nodeR>>1;
    if(val<=arr[nodeNum*2]) return search(val, nodeNum*2, nodeL, mid);
    return search(val-arr[nodeNum*2], nodeNum*2+1, mid+1, nodeR);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;

    // 초기에 모든 값은 1로 설정 (아직 모든 정점을 방문하지 않았다.)
    while(_size<n) _size<<=1;
    _size<<=1;
    for(int i=0;i<n;i++) arr[i+_size/2]=1;
    for(int i=_size/2-1;i>0;i--) arr[i] = arr[i*2]+arr[i*2+1];

    for(int i=0;i<n;i+=2) cin >> a[i];
    for(int i=1;i<n;i+=2) cin >> a[i];

    vector<int> res1, res2;
    for(int i=0;i<n;i++) {
        if(i%2==0) res1.push_back(search(a[i]));
        else res2.push_back(search(a[i]));
    }
    for(int e:res1) cout << e << ' '; cout << '\n';
    for(int e:res2) cout << e << ' ';
}
```
