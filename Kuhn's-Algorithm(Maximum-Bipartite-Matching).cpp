/** https://www.acmicpc.net/problem/11375 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

const int MAX = 1001;
int A[MAX], B[MAX];
bool visited[MAX];
vector<vector<int>> conn(MAX);

bool dfs(int cur) {
    visited[cur]=true;
    for(int next:conn[cur]) {
        if(B[next]==-1 || !visited[B[next]] && dfs(B[next])) {
            A[cur] = next;
            B[next] = cur;
            return true;
        }
    }
    return false;
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0);
    int N, M; cin >> N >> M;

    for(int i=1;i<=N;i++) {
        int cnt; cin >> cnt;
        while(cnt--) {
            int j; cin >> j;
            conn[i].push_back(j);
        }
    }

    memset(A, -1, sizeof A);
    memset(B, -1, sizeof B);
    int cnt=0;
    for(int i=1;i<=N;i++) {
        if(A[i]==-1) {
            memset(visited, false, sizeof visited);
            if(dfs(i)) cnt++;
        }
    }
    cout << cnt;
}
