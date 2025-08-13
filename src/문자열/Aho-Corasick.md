## Aho-Corasick
Trie구조에 실패함수를 추가한 일대다 패턴매칭 알고리즘

시간복잡도 : O(S) (S : 모든 문자열의 길이)

##

트라이 구조에 abc, abce, ababcd라는 문자열 세 개가 삽입되었다고 가정하면 아래와 같이 나타내진다.
![img1](https://github.com/user-attachments/assets/37acc8cb-b4dc-46d1-af31-ba6908192970)

처음에는 *이 붙은 이 두 곳 (c, d, e)에만 finish=true로 마킹이 된다.

그럼 트라이 구조에서 실패함수란 무엇일까?

ac라는 문자열이 들어왔다면 (c에서 매칭 실패) 어디부터 다시 살펴봐야할까? 정답은 루트로 돌아가서(처음부터) c로의 분기가 있는지 살펴봐야한다.

ababa라는 문자열이 들어왔다면(마지막 a에서 매칭 실패) 어디부터 다시 살펴봐야할까? 정답은 a -> b 로 돌아가서 a로의 분기가 있는지 확인하면 된다.  

이렇게 어떤 문자에서 매칭에 실패했을 때, **어디서부터 다시 살펴봐야 하는지 위치**를 말한다.

##

실패함수를 추가해보자.
![img2](https://github.com/user-attachments/assets/542c62bd-d46f-41d6-b9d7-e8dcc7872289)

실패함수를 역간선으로 나타내주었다.

실패함수를 순서대로 따라가다보면 (계속 매칭에 실패하면) 결국 루트에 도착하게 된다. (처음부터 다시 살펴본다는 의미)

##

![img3](https://github.com/user-attachments/assets/fee712a2-2927-449d-99ed-4715a7d241c2)

실패함수를 추가하면서 abc에서 끝나는 문장이 있다고 하면 ababc에도 finish를 true로 나타낼 수 있다.

prof. abab에서 실패함수를 한번 통과해서 c로 움직인 결과가 finish=true 이기 때문에 

##

[연습문제 (백준 9250번)](https://www.acmicpc.net/problem/9250)

``` c++
/** https://www.acmicpc.net/problem/9250 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

/** 
 * 트라이 구조에서 fail함수만 추가한 형태
 * finish : 문자열의 마지막을 나타내는 변수
 * fail : 현재의 문자가 일치하지 않으면 어디서부터 다시 탐색해야하는지 나타내는 포인터
 */
struct trie {
    trie* go[26] = {0, };
    bool finish=false;
    trie* fail;

    void insert(char* ch) {
        if(*ch==NULL) {
            finish=true;
            return;
        }

        if(!go[*ch-'a']) go[*ch-'a'] = new trie;
        go[*ch-'a']->insert(ch+1);
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    trie* root = new trie;

    while(n--) {
        string s; cin >> s;
        root->insert(&s[0]);
    }

    /** 
     * 아호-코라식의 실패함수 설정
     * 
     * 현재 문자를 cur로 설정
     * cur에서 다음 문자를 next로 설정
     * ex) 아래와 같이 트라이가 구축되었다면, 첫 a가 cur이고 a에서 이동할 분기 a~z가 next
     *       a - b - c - d
     *      /
     * a - b - c - e
     * 
     * cur이 첫번째 문자인 경우
     * - next의 실패함수는 루트로 설정.
     * 
     * cur이 첫번째 문자가 아닌 경우
     * - next로 향하는 경로가 있거나 루트에 도달할 때까지 실패함수를 타고 올라가기.
     * - 만약 경로가 있다면 해당 경로로 이동.
     * - 해당 위치를 실패함수로 설정.
     * - 만약 실패함수로 설정한 곳이 문자열의 마지막(finish==true)이라면 next의 finish도 true로 설정(쿼리마다 실제로 실패함수를 타고 이동하지 않고 마지막 여부를 확인하기 위해)
     */
    queue<trie*> q; q.push(root);
    root->fail = root;
    while(!q.empty()) {
        trie* cur = q.front(); q.pop();
        for(int i=0;i<26;i++) {
            if(!cur->go[i]) continue;
            trie* next = cur->go[i];

            if(cur==root) {
                next->fail = root;
            } else {
                trie* dest = cur->fail;
                while(dest!=root && !dest->go[i]) dest = dest->fail;
                if(dest->go[i]) dest = dest->go[i];
                next->fail = dest;
            }
            if(next->fail->finish) next->finish=true;
            q.push(next);
        }
    }

    /** 
     * 입력된 문자열을 순서대로 살펴보면서
     * - 이동할 수 없는 동안 실패함수를 타고 올라가기
     * - 이동할 수 있는 분기가 존재한다면 이동
     * - 중간에 finish=true인 곳에 도달한다면 부분 문자열이 존재한다는 의미
     */
    int Q; cin >> Q;
    while(Q--) {
        string s; cin >> s;
        trie* cur = root;
        for(int i=0;i<s.length();i++) {
            while(cur!=root && !cur->go[s[i]-'a']) cur = cur->fail;
            if(cur->go[s[i]-'a']) cur = cur->go[s[i]-'a'];
            if(cur->finish) break;
        }
        if(cur->finish) cout << "YES\n";
        else cout << "NO\n";
    }
}
```
