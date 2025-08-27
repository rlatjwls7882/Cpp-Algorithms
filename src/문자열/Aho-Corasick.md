## Aho-Corasick
Trie구조에 실패 링크를 추가한 일대다 패턴매칭 알고리즘

시간복잡도 : O(S), 공간복잡도 : O(S) (S : 모든 문자열의 길이)

![](https://github.com/user-attachments/assets/62bf251e-a3f7-408c-900a-51eeea331a8e)

트라이 구조에 abc, abce, ababcd라는 문자열 세 개가 삽입되었다고 가정하면 아래와 같이 나타내진다.  
처음에는 *이 붙은 이 두 곳 (c, d, e)에만 finish=true로 마킹이 된다.  

그럼 트라이 구조에서 실패 링크란 무엇일까?  
ac를 패턴매칭 해보면 (c에서 매칭 실패) 어디부터 다시 살펴봐야할까? 정답은 루트로 돌아가서(처음부터) c로의 분기가 있는지 살펴봐야한다.  
ababa를 패턴매칭 해보면 (마지막 a에서 매칭 실패) 어디부터 다시 살펴봐야할까? 정답은 a -> b 위치로 돌아가서 a로의 분기가 있는지 확인하면 된다.  
이렇게 어떤 문자에서 매칭에 실패했을 때, **어디서부터 다시 살펴봐야 하는지 위치**를 말한다.

실패 링크를 추가해보자.  

![](https://github.com/user-attachments/assets/849d8912-33d7-45c2-9b24-160e40c90a5c)

root에 도착한다.  
일단 root 다음 위치인 a1의 실패 링크를 루트로 설정한다. (맨 처음 문자가 일치하지 않으면 처음부터 다시 살펴봐야 함.)

![](https://github.com/user-attachments/assets/6a6c8f15-d9b1-4118-b3c1-8a69f1576af0)

a1에 도착한다. (실제로 a1같이 숫자로 마킹된 것은 아니고 같은 문자를 비교하기 쉽게 숫자를 임의로 배정하였다.)  
a1의 다음 위치인 b1의 실패 링크를 a1의 실패 링크인 root로 설정한다. 
b1의 실패 링크인 root에서 b로의 경로가 없기 때문에 실패 링크는 그대로이다.

![](https://github.com/user-attachments/assets/15a71115-b210-42d1-9a74-24da562bec10)

b1에 도착한다.  
b1의 다음 위치인 a2와 c1의 실패 링크를 b1의 실패 링크인 root로 설정한다.  
a2의 실패 링크인 root에서 a로의 경로가 있기 때문에 실패 링크가 a1로 이동한다. (a -> b -> a 까진 매칭 되었고 그 다음문자 m이어서 실패했다면 a 로 돌아가서 a -> m 경로가 있는지 확인해야 함.)  
c1의 실패 링크에서 c로의 경로가 없기 때문에 실패 링크는 그대로이다.

![](https://github.com/user-attachments/assets/8bbc5f41-e0b5-4e47-a80a-91dbe6a5f82c)

이렇게 몇개의 실패 링크가 추가된 후, b2에 도착한다.  
b2의 다음 위치인 c2의 실패 링크를 b2의 실패 링크인 b1으로 설정한다.  
c2의 실패 링크인 b1에서 c로의 경로가 있기 때문에 실패 링크가 c1으로 이동한다.  
최종적으로 가리키는 실패 링크에서 끝나는 단어가 존재하기 때문에 (fail->finish=true) 실패 링크를 타고가기 전 정점에도 finish=true로 마킹해준다.

![](https://github.com/user-attachments/assets/bf0ee3a2-23a1-4443-874e-26d892cd9c41)

c2에 도착한다.  
c2의 다음 위치인 d1의 실패 링크를 c2의 실패 링크인 c1으로 설정한다.  
d1의 실패 링크인 c1에서 d로의 경로가 없기 때문에 실패 링크가 c1의 실패 링크인 root로 이동한다.  
d1의 실패 링크인 루트에서 d로의 경로가 있기 때문에 그대로이다.  

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
     * 아호-코라식의 실패 링크 설정
     * 
     * 현재 문자를 cur로 설정
     * cur에서 다음 문자를 next로 설정
     * ex) 아래와 같이 트라이가 구축되었다면, 첫 a가 cur이고 a에서 이동할 분기 a~z가 next
     *       a - b - c - d
     *      /
     * a - b - c - e
     * 
     * cur이 첫번째 문자인 경우
     * - next의 실패 링크는 루트로 설정.
     * 
     * cur이 첫번째 문자가 아닌 경우
     * - next로 향하는 경로가 있거나 루트에 도달할 때까지 실패 링크를 타고 올라가기.
     * - 만약 경로가 있다면 해당 경로로 이동.
     * - 해당 위치를 실패 링크로 설정.
     * - 만약 실패 링크로 설정한 곳이 문자열의 마지막(finish==true)이라면 next의 finish도 true로 설정(쿼리마다 실제로 실패 링크를 타고 이동하지 않고 마지막 여부를 확인하기 위해)
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
     * - 이동할 수 없는 동안 실패 링크를 타고 올라가기
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
