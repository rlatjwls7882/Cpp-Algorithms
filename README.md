# 대회 / 코딩테스트 알고리즘 정리
본 문서는 **알고리즘의 동작 방식과 구현**을 중심으로 가능한 한 간단하게 설명하여, 학습 및 복습 시 빠르게 참고할 수 있는 자료를 목표로 합니다.

정확한 증명이나 자세한 설명은 본 문서의 범위를 벗어나므로, 필요한 경우 다른 자료를 참고하시기 바랍니다.

또한 **차례의 순서는 정확한 난이도 순서를 의미하지 않습니다.** 각 알고리즘 제목 옆에 표시된 난이도는 작성자의 경험을 바탕으로 임의로 설정한 것이므로, 실제 난이도와 다를 수 있습니다.

난이도는 해당 알고리즘이 사용되는 문제의 **최소 티어**를 기준으로 설정하였으며, 실제로는 더 높은 난이도를 요구할 수도 있습니다.

다만 같은 깊이에 있는 항목들은 가능한 한 **학습하기 쉬운 순서**로 배치하려고 노력했습니다. 앞의 알고리즘을 이해하면 다음 알고리즘을 비교적 자연스럽게 학습할 수 있도록 구성했지만, 개인의 배경 지식이나 학습 목적에 따라 학습 순서는 달라질 수 있습니다.

# 현재 리메이크중

## 차례
* 자료구조
  * DSU (Disjoint Set Union, 분리 집합) 🟡 Gold V
* 기본 알고리즘
  * Binary Search (이분 탐색) ⚪ Silver IV
  * Prefix Sum (누적 합) ⚪ Silver III
  * Two Pointer (두 포인터) ⚪ Silver III
  * Backtracking (백트래킹) ⚪ Silver III
* 그래프
  * 경로 탐색
    * DFS (Depth First Search, 깊이 우선 탐색) ⚪ Silver II
    * BFS (Breadth First Search, 너비 우선 탐색) ⚪ Silver II
  * 최단 경로
    * Dijkstra's Algorithm 🟡 Gold IV
    * Bellman-Ford Algorithm 🟡 Gold IV
    * Floyd-Warshall Algorithm 🟡 Gold IV
    * SPFA (Shortest Path Faster Algorithm) 🟡 Gold IV
  * DAG(Directed Acyclic Graph)
    * Kahn’s Algorithm (Topological Sort, 위상 정렬) 🟡 Gold III
  * 최소 스패닝 트리
    * Kruskal’s Algorithm 🟡 Gold IV
  * 유량
    * Kuhn's Algorithm (Maximum Bipartite Matching, 이분 매칭) 🟢 Platinum IV
    * Edmonds-Karp Algorithm 🟢 Platinum IV
    * Dinic's Algorithm 🟢 Platinum II
    * MCMF (Min Cost Max Flow) Algorithm (SPFA 구현) 🟢 Platinum III
    * Hopcroft-Karp Algorithm 🟢 Platinum III
  * 컴포넌트 분해
    * Tarjan’s Algorithm (SCC) 🟢 Platinum V
    * 2-SAT (2-Satisfiability) 🟢 Platinum IV
  * 세그먼트 트리
    * Segment Tree (세그먼트 트리) 🟡 Gold I
    * Fenwick Tree (Binary Indexed Tree, 펜윅 트리) 🟢 Platinum V
    * Walking on Segment Tree (세그 워크) 🟢 Platinum V
    * Dynamic Segment Tree (동적 세그먼트 트리) 🟢 Platinum V
    * Segment Tree with Lazy Propagation 🟢 Platinum IV
    * Merge Sort Tree 🟢 Platinum III
    * Sparse Segment Tree (Dynamic Segment Tree with Lazy Propagation) 🟢 Platinum I
    * HLD (Heavy Light Decomposition) 🟢 Platinum I
* 문자열
  * KMP (Knuth-Morris-Pratt) Algorithm 🟢 Platinum V
  * Trie 🟢 Platinum IV
  * Aho-Corasick (아호-코라식) 🟢 Platinum II
* 수학
  * 정수론
    * Naive Primality Test (소수 판정) ⚪ Silver IV
    * Sieve of Eratosthenes (에라토스테네스의 체) ⚪ Silver III
    * Euclidean Algorithm (유클리드 호제법) ⚪ Silver IV
    * Exponentiation by Squaring (빠른 거듭제곱) ⚪ Silver I
    * Modular Multiplicative Inverse (모듈러 곱셈의 역원) 🟡 Gold I
  * 기하
    * CCW (CounterclockWise) Algorithm 🟡 Gold V
    * Line Intersection 🟡 Gold II
    * Graham's Scan (Convex Hull, 볼록 껍질) 🟢 Platinum V
    * Point in Convex Polygon (볼록 다각형 내부의 점 판정) 🟢 Platinum III
    * Rotating Calipers (회전하는 캘리퍼스) 🟢 Platinum III
* 스위핑
  * Sweeping Algorithm 🟡 Gold V
  * Imos Method (いもす法) 🟢 Platinum IV
* DP
  * TSP (Traveling Salesman Problem, 외판원 순회 문제) 🟡 Gold I
  * Deque Trick 🟢 Platinum V
  * Convex Hull Trick 🟢 Platinum II
* 쿼리 처리
  * Offline Query 🟢 Platinum IV
  * Square Root Decomposition (제곱근 분할법) 🟢 Platinum II
  * Mo's Algorithm 🟢 Platinum II
  * PBS (Parallel Binary Search, 병렬 이분 탐색) 🟢 Platinum I


 
# 여기부터 리메이크 필요, 완료된건 뒤쪽에




## [Graham's Scan (Convex Hull)](src/수학/기하/Graham's%20Scan.md) 🟢 Platinum V
기준점을 잡아 점들을 각도로 정렬한 후, 스택을 이용해 볼록 껍질의 방향성을 유지하지 않는 점을 제거하며 볼록 껍질을 찾는 알고리즘

시간복잡도 : O(NlogN)

## [Point in Convex Polygon (볼록 다각형 내부의 점 판정)](src/수학/기하/Point%20in%20Convex%20Polygon.md) 🟢 Platinum III
볼록 다각형에 대해, 기준점을 잡고 이분 탐색을 이용해 점이 내부에 있는지 O(logN)에 판정하는 알고리즘

시간복잡도 : O(logN) (N : 볼록 껍질의 점의 수)

## [Rotating Calipers (회전하는 캘리퍼스)](src/수학/기하/Rotating%20Calipers.md) 🟢 Platinum III
볼록 껍질에서 모든 점 쌍 중 가장 먼 두 점 등을 O(N)에 찾는 알고리즘

시간복잡도 : O(N) (그라함 스캔 제외)

## [Sweeping Algorithm](src/스위핑/Sweeping%20Algorithm.md) 🟡 Gold V
선을 한쪽 방향으로 이동시키며 정렬된 이벤트를 순서대로 처리해 문제를 해결하는 알고리즘

시간복잡도 : O(NlogN) (N : 이벤트 개수, 정렬 O(NlogN) + 스캔 O(N))

## [Imos Method (いもす法)](src/스위핑/Imos%20Method.md) 🟢 Platinum IV
구간(또는 영역)의 증가·감소량을 차분 배열(Difference Array)에 기록한 뒤, 최종적으로 누적 합을 구해 전체 상태를 복원하는 알고리즘

시간복잡도 : O($N^D+Q$) (N : 각 차원의 크기, D : 차원 수, Q : 쿼리 수)

## [TSP (Traveling Salesman Problem, 외판원 순회 문제)](src/DP/TSP.md) 🟡 Gold I
비트마스킹 + DP로 모든 도시를 한 번씩 순회하고 다시 시작 도시로 돌아오는 최소 비용을 계산하는 알고리즘

시간복잡도 : O(N² x $2^N$) (N : 도시의 수, $2^N$ : 가능한 방문 조합의 수)

## [Deque Trick](src/DP/Deque%20Trick.md) 🟢 Platinum V
덱에 단조 증가 또는 단조 감소하는 인덱스를 유지하여 슬라이딩 윈도우 내에서 최소값 또는 최대값을 O(1)에 찾는 알고리즘

시간복잡도 : O(N)

## [Convex Hull Trick](src/DP/Convex%20Hull%20Trick.md) 🟢 Platinum II
DP를 볼록껍질 형태로 나타내 최적화하는 방법

시간복잡도 : $O(N \log N)$

## [Offline Query](src/쿼리%20처리/Offline%20Query.md) 🟢 Platinum IV
복잡한 연산을 단순화하기 위해, 답에 영향을 주지 않도록 쿼리 순서를 재배열해 답을 찾는 테크닉

## [Square Root Decomposition (제곱근 분할법)](src/쿼리%20처리/Square%20Root%20Decomposition.md) 🟢 Platinum II
값을 $\sqrt N$개씩 연속된 구간들로 나누어 관리하여 특정 구간에 대한 쿼리를 O($\sqrt N$) 시간에 처리하는 알고리즘

시간복잡도 : O($Q\sqrt N$) (Q : 쿼리의 수)

## [Mo's Algorithm](src/쿼리%20처리/Mo's%20Algorithm.md) 🟢 Platinum II
제곱근 분할을 구간 쿼리에 적용시켜 전체 쿼리를 O($Q\sqrt N$) 시간에 해결하는 알고리즘

시간복잡도 : O($Q\sqrt N$)

## [PBS (Parallel Binary Search, 병렬 이분 탐색)](src/쿼리%20처리/PBS.md) 🟢 Platinum I
이분 탐색 쿼리가 여러 번 주어질 때, 각 쿼리를 개별 이분탐색하지 않고 같은 mid끼리 묶어 한 번의 검증으로 여러 쿼리를 처리하는 오프라인 기법.

시간복잡도 : O((N+Q)logC) (C : 최대 이분탐색 범위)




# 여기부터 리메이크 완료





## DSU (Disjoint Set Union, 분리 집합) 🟡 Gold V
서로 겹치지 않는(서로소) 집합을 관리하여 합치기와 대표 원소 찾기 연산을 효율적으로 처리하는 자료구조

시간복잡도: $O(\alpha(N))$ ($\alpha(x)$: 역아커만 함수 $\approx$ 상수 시간, $N$: 데이터 개수)

## Segment Tree (세그먼트 트리) 🟡 Gold I
완전 이진 트리 형태로 구간 정보를 저장하여 구간 쿼리와 업데이트를 $O(\log N)$에 처리하는 자료구조

시간복잡도: $O(Q\log N)$ ($Q$: 쿼리의 수)

## Fenwick Tree (Binary Indexed Tree, 펜윅 트리) 🟢 Platinum V
배열의 누적합을 부분 구간 합 형태로 저장하여 구간 합과 업데이트를 $O(\log N)$에 처리하는 자료구조

시간복잡도: $O(\log N)$

## Walking on Segment Tree (세그 워크) 🟢 Platinum V
세그먼트 트리의 누적 정보를 이용해 루트에서 리프까지 내려가며 k번째 원소를 찾는 테크닉

시간 복잡도: $O(Q\log N)$ ($Q$: 쿼리의 수)

## Dynamic Segment Tree (동적 세그먼트 트리) 🟢 Platinum V
세그먼트 트리에서 필요한 노드만 생성하여 큰 범위의 구간 쿼리를 처리하는 테크닉

시간복잡도: $O(Q\log N)$ ($Q$: 쿼리의 수)

## Segment Tree with Lazy Propagation 🟢 Platinum IV
세그먼트 트리에서 구간 업데이트를 지연 방식으로 처리하여 구간 연산을 효율적으로 수행하는 테크닉

시간복잡도: $O(Q\log N$) ($Q$: 쿼리의 수)

## Merge Sort Tree 🟢 Platinum III
세그먼트 트리의 각 노드에 정렬된 배열을 저장하여 구간에서 특정 값보다 큰(또는 작은) 원소를 빠르게 찾는 자료구조

시간복잡도: $O(NlogN)$, 공간복잡도: $O(NlogN)$

## Sparse Segment Tree (Dynamic Segment Tree with Lazy Propagation) 🟢 Platinum I
Dynamic Segment Tree에 Lazy Propagation을 적용한 자료구조

시간복잡도: $O(Q\log N)$ ($Q$: 쿼리의 수)

## HLD (Heavy Light Decomposition) 🟢 Platinum I
트리 경로 쿼리를 여러 개의 구간 쿼리로 분해하여 처리하는 알고리즘

시간복잡도: $O(Q\log^2N)$ ($Q$: 쿼리의 수)

## Binary Search (이분 탐색) ⚪ Silver IV
정렬된 데이터에서 탐색 범위를 절반씩 줄여가며 원하는 값을 찾는 알고리즘

시간복잡도: $O(M\log N)$ ($N$: 데이터 개수, $M$: 탐색 횟수)

## Prefix Sum (누적 합) ⚪ Silver III
배열의 누적 합을 미리 계산하여 임의 구간의 합을 $O(1)$에 구하는 알고리즘

시간복잡도: 전처리 $O(N)$, 쿼리 $O(1)$ ($N$: 데이터 개수)

## Two Pointer (두 포인터) ⚪ Silver III
두 개의 포인터를 움직이며 배열에서 조건을 만족하는 쌍을 효율적으로 찾는 알고리즘

시간복잡도: $O(N)$ ($N$: 데이터 개수)

## Backtracking (백트래킹) ⚪ Silver III
모든 경우를 탐색하면서 해답이 될 수 없는 경로는 가지치기하여 탐색을 줄이는 완전 탐색 기법

시간복잡도: 최악 $O(K^n)$ ($K$: 선택지 개수, $n$: 깊이)

## DFS (Depth First Search, 깊이 우선 탐색) ⚪ Silver II
그래프에서 한 경로를 가능한 깊게 탐색하다가 막히면 이전 분기점으로 돌아가 다른 경로를 탐색하는 알고리즘

시간복잡도: $O(V+E)$ ($V$: 정점 수, $E$: 간선 수)

## BFS (Breadth First Search, 너비 우선 탐색) ⚪ Silver II
그래프에서 시작 정점으로부터 가까운 정점부터 차례대로 탐색하는 알고리즘

시간복잡도: $O(V+E)$ ($V$: 정점 수, $E$: 간선 수)

## Dijkstra's Algorithm 🟡 Gold IV
가중치가 음수가 없는 그래프에서 시작 정점으로부터의 최단 거리를 구하는 알고리즘

시간복잡도: $O(ElogV)$ ($V$: 정점 수, $E$: 간선 수)

## Bellman-Ford Algorithm 🟡 Gold IV
가중치가 음수인 그래프에서도 최단 거리를 구하고 음수 사이클의 존재 여부를 판별하는 알고리즘

시간복잡도: $O(VE)$ ($V$: 정점 수, $E$: 간선 수)

## Floyd-Warshall Algorithm 🟡 Gold IV
DP를 이용해 모든 정점 쌍 사이의 최단 거리를 구하는 알고리즘

시간복잡도: $O(V^3)$, 공간복잡도: $O(V^2)$ ($V$: 정점 수)

## SPFA (Shortest Path Faster Algorithm) 🟡 Gold IV
Bellman-Ford를 기반으로 큐를 사용해 갱신이 필요한 정점만 처리하여 최단 거리를 구하는 알고리즘

시간복잡도: 경험적 평균 $O(V+E)$, 최악 $O(VE)$ ($V$ : 정점 수, $E$ : 간선 수)

## Kahn’s Algorithm (Topological Sort, 위상 정렬) 🟡 Gold III
[방향성이 있고 사이클이 없는 그래프(DAG)](https://ko.wikipedia.org/wiki/유향_비순환_그래프)에서 선행 관계를 만족하도록 정점을 나열하는 알고리즘

시간복잡도: $O(V+E)$ ($V$: 정점 수, $E$: 간선 수)

## Kruskal’s Algorithm 🟡 Gold IV
간선을 가중치 순으로 정렬한 뒤 사이클이 생기지 않는 간선만 선택하여 최소 스패닝 트리를 만드는 알고리즘

시간복잡도: $O(E\log E)$ ($E$: 간선 수)

## Kuhn's Algorithm (Maximum Bipartite Matching, 이분 매칭) 🟢 Platinum IV
[이분 그래프](https://ko.wikipedia.org/wiki/이분_그래프)에서 서로 겹치지 않는 간선의 최대 집합(최대 매칭)을 찾는 알고리즘

시간복잡도: $O(VE)$ ($V$: 왼쪽 그룹의 정점 수)

## Edmonds-Karp Algorithm 🟢 Platinum IV
그래프에서 시작 지점(source)에서 유량을 흘려서, 도착 지점(sink)까지 유량이 얼마나 도착하는지 찾는 알고리즘

시간복잡도: $O(VE^2)$ ($V$: 정점 수, $E$: 간선 수)

## Dinic's Algorithm 🟢 Platinum II
Edmonds-Karp를 개선한 방법으로, 레벨 그래프와 블로킹 플로우를 이용해 최대 유량을 구하는 알고리즘

시간복잡도: $O(V^2E)$ ($V$: 정점 수, $E$: 간선 수)

## MCMF (Min Cost Max Flow) Algorithm (SPFA 구현) 🟢 Platinum III
SPFA로 최단 비용 경로를 반복적으로 찾아 최소 비용 최대 유량을 구하는 알고리즘

시간복잡도: $O(FVE)$ ($V$: 정점 수, $E$: 간선 수, $F$: 최대 유량)

## Hopcroft-Karp Algorithm 🟢 Platinum III
Kuhn's Algorithm을 개선해 Shortest Augmenting Path를 여러개씩 찾는 알고리즘

시간복잡도 : O($E\sqrt V$)

## Tarjan’s Algorithm (SCC) 🟢 Platinum V
그래프에서 [SCC (Strongly Connected Component)](https://ko.wikipedia.org/wiki/강한_연결_요소)를 한 번의 DFS로 찾는 알고리즘

시간복잡도: $O(V + E)$ ($V$: 정점 수, $E$: 간선 수)

## 2-SAT (2-Satisfiability)) 🟢 Platinum IV
2-[CNF](https://ko.wikipedia.org/wiki/논리곱_표준형) 식이 주어졌을 때 [Implication Graph](https://en.wikipedia.org/wiki/Implication_graph)를 만들고 SCC를 이용해 식이 만족 가능한지 판단하는 알고리즘

시간복잡도: $O(V + E)$ ($V$: 정점 수, $E$: 간선 수)

## KMP (Knuth-Morris-Pratt) Algorithm 🟢 Platinum V
문자열의 prefix 정보를 이용해 패턴의 등장 위치를 빠르게 찾는 알고리즘

시간복잡도: $O(N+M)$ ($N+M$: 두 문자열의 길이 합)

## Trie 🟢 Platinum IV
여러 문자열을 공통 접두사 단위로 묶어 저장하는 문자열 자료구조

시간복잡도: $O(S)$, 공간복잡도: $O(S)$ ($S$: 모든 문자열의 길이)

## Aho-Corasick (아호-코라식) 🟢 Platinum II
Trie에 실패 링크를 추가하여 다중 패턴을 동시에 검색하는 문자열 매칭 알고리즘

시간복잡도: $O(S)$, 공간복잡도: $O(S)$ ($S$: 모든 문자열의 길이)

## Naive Primality Test (소수 판정) ⚪ Silver IV
2부터 $\sqrt N$까지의 정수 중 약수가 존재하는지 확인하여 소수 여부를 판별하는 알고리즘

시간복잡도: $O(\sqrt N)$

## Sieve of Eratosthenes (에라토스테네스의 체) ⚪ Silver III
배수를 제거하는 방식으로 $1$부터 $N$까지의 소수를 구하는 전처리 알고리즘

시간복잡도 : $O(N\log{\log{N}})$

## Euclidean Algorithm (유클리드 호제법) ⚪ Silver IV
나머지 연산을 반복하여 두 수의 최대공약수를 구하는 알고리즘

시간복잡도: $O(\log(\min(A,B)))$

## Exponentiation by Squaring (빠른 거듭제곱) ⚪ Silver I
거듭제곱을 분할 정복으로 계산하여 $x^N$을 빠르게 구하는 알고리즘

시간복잡도: $O(\log N)$

## Modular Multiplicative Inverse (모듈러 곱셈의 역원) 🟡 Gold I
모듈러 연산에서 나눗셈을 곱셈으로 변환하기 위해 사용하는 모듈러 역원을 구하는 알고리즘

시간복잡도: $O(\log N)$

## CCW (CounterclockWise) Algorithm 🟡 Gold V
세 점이 이루는 회전 방향(시계, 반시계, 일직선)을 판별하는 알고리즘

시간복잡도: $O(1)$

## Line Intersection 🟡 Gold II
CCW를 이용하여 두 선분의 교차 여부를 판별하는 알고리즘

시간복잡도: $O(1)$

## License
[![CC BY-NC-SA 4.0](https://licensebuttons.net/l/by-nc-sa/4.0/88x31.png)](https://creativecommons.org/licenses/by-nc-sa/4.0/)
Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0). See LICENSE.md for more info.
