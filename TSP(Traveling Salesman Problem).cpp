/** https://www.acmicpc.net/problem/2098 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
int n, w[16][16], dp[16][1<<16];

int dfs(int cur, int visit) {
    if(visit+1 == 1<<n) return (w[cur][0]==0 ? INF : w[cur][0]);
    if(dp[cur][visit]!=-1) return dp[cur][visit];
    dp[cur][visit] = INF;
    for(int next=0;next<n;next++) {
        if(!(visit & (1<<next)) && w[cur][next]) {
            dp[cur][visit] = min(dp[cur][visit], dfs(next, visit | (1<<next)) + w[cur][next]);
        }
    }
    return dp[cur][visit];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            cin >> w[i][j];
        }
    }
    memset(dp, -1, sizeof dp);
    cout << dfs(0, 1);
}
