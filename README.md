# 대회 / 코딩테스트 알고리즘 정리
본 문서는 **알고리즘의 동작 방식과 구현**을 중심으로 설명하여, 학습 및 복습 시 빠르게 참고할 수 있는 자료를 목표로 합니다.
* TODO) 새로 공부 (Hungarian, Hopcroft-Karp Algorithm, Gaussian Elimination)
* TODO) 복습 (LCA, BCC, EEA, Sprague-Grundy Theorem, Convex Hull Trick)  
* TODO) 설명 추가
  * 정수론 (Euclidean Algorithm, Fermat's Little Theorem, Euler Phi, Inclusion–Exclusion Principle)
  * 기초 알고리즘 (Sliding Window, Meet in the Middle)
  * 기하 (Shoelace Formula)
  * DP (LIS, LCS, MSIS)
  * 트리 (Fenwick Tree)

## 목차
* 기본 알고리즘
  * Binary Search (이분 탐색) ⚪ Silver IV
  * Prefix Sum (누적 합) ⚪ Silver III
  * Two Pointer ⚪ Silver III
  * DSU (Disjoint Set Union, 분리 집합) 🟡 Gold V
  * Backtracking ⚪ Silver III
* 그래프
  * 경로 탐색
    * 기본 탐색
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
    * Dinic's Algorithm 🟢 Platinum I
    * MCMF (Min Cost Max Flow) Algorithm 🟢 Platinum III
  * 컴포넌트 분해
    * Tarjan’s Algorithm (SCC) 🟢 Platinum V
    * 2-SAT (2-Satisfiability) 🟢 Platinum IV
  * 트리
    * Segment Tree 🟡 Gold I
    * Walking on Segment Tree 🟢 Platinum V
    * Segment Tree with Lazy Propagation 🟢 Platinum IV
    * Merge Sort Tree 🟢 Platinum III
    * HLD (Heavy Light Decomposition) 🟢 Platinum I
* 문자열
  * KMP (Knuth-Morris-Pratt) Algorithm 🟢 Platinum V
  * Trie 🟢 Platinum IV
  * Aho-Corasick 🟢 Platinum II
* 수학
  * 정수론
    * Naive Primality Test (소수 판정) ⚪ Silver IV
    * Sieve of Eratosthenes (에라토스테네스의 체) ⚪ Silver III
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
* 쿼리 처리
  * Offline Query 🟢 Platinum IV
  * Square Root Decomposition (평방 분할, 제곱근 분할) 🟢 Platinum II
  * Mo's Algorithm 🟢 Platinum II
  * PBS (Parallel Binary Search, 병렬 이분 탐색) 🟢 Platinum I

## [Binary Search (이분 탐색)](src/기본%20알고리즘/Binary%20Search.md) ⚪ Silver IV
정렬된 데이터에서 원하는 값을 찾기 위해 탐색 범위를 절반씩 줄여가는 알고리즘

시간복잡도 : O(MlogN) (N : 데이터 개수, M : 탐색 횟수)

## [Prefix Sum (누적 합)](src/기본%20알고리즘/Prefix%20Sum.md) ⚪ Silver III
배열의 각 인덱스까지의 합을 미리 계산해 두어, 임의 구간의 합을 O(1)에 구하는 알고리즘

시간복잡도 : 전처리 O(N), 쿼리 O(1) (N : 데이터 개수)

## [Two Pointer](src/기본%20알고리즘/Two%20Pointer.md) ⚪ Silver III
두 개의 포인터를 움직이며 배열이나 리스트에서 원하는 조건을 만족하는 구간을 효율적으로 찾는 알고리즘

시간복잡도 : O(NlogN) (N : 데이터 개수, 정렬 O(NlogN) + 스캔 O(N))

## [DSU (Disjoint Set Union, 분리 집합)](src/기본%20알고리즘/DSU.md) 🟡 Gold V
서로 겹치지 않는 집합을 관리하고 합치거나 찾는 연산을 효율적으로 처리하는 자료구조

시간복잡도 : O(α(N)) (α : 역아커만 함수 ≒ 상수 시간, N : 데이터 개수)

## [Backtracking](src/기본%20알고리즘/Backtracking.md) ⚪ Silver III
모든 경우를 탐색하되, 해답이 될 수 없는 경로는 중간에 가지치기하여 탐색을 중단하는 완전 탐색 알고리즘

시간복잡도 : 최악 O(Kⁿ) (K : 선택지 개수, n : 깊이)

## [DFS (Depth First Search, 깊이 우선 탐색)](src/그래프/경로%20탐색/기본%20탐색/DFS.md) ⚪ Silver II
그래프에서 한 정점에서 한 경로를 끝까지 따라간 뒤 막히면 이전 분기점으로 되돌아가 다른 분기를 탐색하는 알고리즘

시간복잡도 : O(V+E) (V : 정점 수, E : 간선 수)

## [BFS (Breadth First Search, 너비 우선 탐색)](src/그래프/경로%20탐색/기본%20탐색/BFS.md) ⚪ Silver II
그래프에서 시작 정점에서 가까운 정점부터 차례대로 탐색하는 알고리즘

시간복잡도 : O(V+E) (V : 정점 수, E : 간선 수)

## [Dijkstra's Algorithm](src/그래프/경로%20탐색/최단%20경로/Dijkstra's%20Algorithm.md) 🟡 Gold IV
가중치가 음수가 없는 그래프에서, 시작 정점으로부터 누적 거리가 가장 짧은 정점부터 차례대로 탐색하여 최단 거리를 구하는 알고리즘

시간복잡도 : O(ElogV) (V : 정점 수, E : 간선 수)

## [Bellman-Ford Algorithm](src/그래프/경로%20탐색/최단%20경로/Bellman-Ford%20Algorithm.md) 🟡 Gold IV
가중치가 음수인 그래프에서도, 모든 간선을 최대 V-1번 완화해 최단 거리를 구하고 음수 사이클 여부를 판별하는 알고리즘

시간복잡도 : O(VE) (V : 정점 수, E : 간선 수)

## [Floyd-Warshall Algorithm](src/그래프/경로%20탐색/최단%20경로/Floyd-Warshall%20Algorithm.md) 🟡 Gold IV
모든 정점 쌍 사이의 최단 거리를 DP로 구하는 알고리즘

시간복잡도 : O(V³), 공간복잡도 : O(V²)

## [SPFA (Shortest Path Faster Algorithm)](src/그래프/경로%20탐색/최단%20경로/SPFA.md) 🟡 Gold IV
큐를 사용해 Bellman-Ford의 간선 완화를 [휴리스틱](https://en.wikipedia.org/wiki/Heuristic_(computer_science))으로 가속하여 최단 거리를 구하는 알고리즘

시간복잡도 : 경험적 평균 O(V+E), 최악 O(VE) (V : 정점 수, E : 간선 수)

## [Kahn’s Algorithm (Topological Sort, 위상 정렬)](src/그래프/DAG/Kahn’s%20Algorithm.md) 🟡 Gold III
방향성이 있고 사이클이 없는 그래프[(DAG)](https://ko.wikipedia.org/wiki/유향_비순환_그래프)에서, 모든 정점을 선행 관계를 만족하도록 나열하는 알고리즘

시간복잡도 : O(V+E) (V : 정점 수, E : 간선 수)

## [Kruskal’s Algorithm](src/그래프/최소%20스패닝%20트리/Kruskal’s%20Algorithm.md) 🟡 Gold IV
간선을 가중치 순으로 정렬해 사이클을 피하며 [최소 스패닝 트리](https://en.wikipedia.org/wiki/Minimum_spanning_tree)를 만드는 알고리즘

시간복잡도 : O(ElogE) (E : 간선 수)

## [Kuhn's Algorithm (Maximum Bipartite Matching, 이분 매칭)](src/그래프/유량/Kuhn's%20Algorithm.md) 🟢 Platinum IV
그래프를 [이분 그래프](https://ko.wikipedia.org/wiki/이분_그래프)로 나타내었을 때 최대 매칭 수(왼쪽 정점과 오른쪽 정점의 쌍의 수)를 찾는 알고리즘

시간복잡도 : O(VE) (V : 왼쪽 그룹의 정점 수)

## [Edmonds-Karp Algorithm](src/그래프/유량/Edmonds-Karp%20Algorithm.md) 🟢 Platinum IV
그래프에서 시작 지점에서 유량을 흘려서, 도착지점까지 유량이 얼마나 도착하는지 찾는 알고리즘

시간복잡도 : O(VE²)

## [Dinic's Algorithm](src/그래프/유량/Dinic's%20Algorithm.md) 🟢 Platinum I
Edmonds-Karp 알고리즘을 최적화한 알고리즘으로, 레벨 그래프를 구성해 블로킹 플로우를 흘려 불필요한 탐색을 줄여 최대 유량을 구하는 알고리즘

시간복잡도 : O(V²E)

## [MCMF (Min Cost Max Flow) Algorithm](src/그래프/유량/MCMF%20Algorithm.md) 🟢 Platinum III
Edmonds-Karp 알고리즘에 SPFA(Shortest Path Faster Algorithm)를 합쳐 최대의 유량을 흘리면서, 그 중에서 최소 비용을 찾는 알고리즘

시간복잡도 : O(FVE) (F : 최대 유량)

## [Tarjan’s Algorithm (SCC)](src/그래프/컴포넌트%20분해/Tarjan’s%20Algorithm.md) 🟢 Platinum V
그래프에서 나타나는 [SCC (Strongly Connected Component)](https://ko.wikipedia.org/wiki/강한_연결_요소)을 한번의 dfs로 뽑아내는 알고리즘

시간복잡도 : O(V+E) (V : 정점 수, E : 간선 수)

## [2-SAT (2-Satisfiability)](src/그래프/컴포넌트%20분해/2-SAT.md) 🟢 Platinum IV
2개의 변수로 이루어진 [CNF](https://ko.wikipedia.org/wiki/논리곱_표준형)가 주어졌을 때, 이를 만족시도록 변수에 (True/False)를 대입 가능한지 [Implication Graph](https://en.wikipedia.org/wiki/Implication_graph)를 만들어 SCC를 형성해 확인하는 문제

시간복잡도 : O(V+E) (V : 정점 수, E : 간선 수)

## [Segment Tree](src/그래프/트리/Segment%20Tree.md) 🟡 Gold I
완전 이진 트리 구조를 이용하여 구간 쿼리를 최적화하는 알고리즘

시간복잡도 : O(QlogN) (Q : 쿼리의 수)

## [Walking on Segment Tree](src/그래프/트리/Walking%20on%20Segment%20Tree.md) 🟢 Platinum V
세그먼트 트리의 구간 합을 이용하여 이분 탐색으로 k번째 원소를 찾는 테크닉

시간 복잡도 : O(QlogN) (Q : 쿼리의 수)

## [Segment Tree with Lazy Propagation](src/그래프/트리/Segment%20Tree%20with%20Lazy%20Propagation.md) 🟢 Platinum IV
세그먼트 트리에서 구간 업데이트를 지연 방식으로 처리하여, 최적화하는 알고리즘 

시간복잡도 : O(QlogN) (Q : 쿼리의 수)

## [Merge Sort Tree](src/그래프/트리/Merge%20Sort%20Tree.md) 🟢 Platinum III
세그먼트 트리에 합병 정렬된 내용을 담아 범위탐색 시간을 줄인 알고리즘 

시간복잡도 : O(NlogN), 공간복잡도 : O(NlogN)

## [HLD (Heavy Light Decomposition)](src/그래프/트리/HLD.md) 🟢 Platinum I
트리에서 세그먼트 트리로 구간 쿼리를 최적화하는 알고리즘

시간복잡도 : O(Qlog²N) (Q : 쿼리의 수)

## [KMP (Knuth-Morris-Pratt) Algorithm](src/문자열/KMP%20Algorithm.md) 🟢 Platinum V
한 문자열에서 다른 문자열이 어디에 등장하는지 찾아주는 문자열 검색 알고리즘

시간복잡도 : O(N+M) (N+M : 두 문자열의 길이 합)

## [Trie](src/문자열/Trie.md) 🟢 Platinum IV
여러 문자열을 공통 접두사로 압축해 저장하는 자료구조

시간복잡도 : O(S), 공간복잡도 : O(S) (S : 모든 문자열의 길이)

## [Aho-Corasick](src/문자열/Aho-Corasick.md) 🟢 Platinum II
Trie구조에 실패 링크를 추가한 일대다 패턴매칭 알고리즘

시간복잡도 : O(S), 공간복잡도 : O(S) (S : 모든 문자열의 길이)

## [Naive Primality Test (소수 판정)](src/수학/정수론/Naive%20Primality%20Test.md) ⚪ Silver IV
2부터 √N까지 약수가 있는지 확인하여 N이 소수인지 판별하는 알고리즘

시간복잡도 : O(√N)

## [Sieve of Eratosthenes (에라토스테네스의 체)](src/수학/정수론/Sieve%20of%20Eratosthenes.md) ⚪ Silver III
1부터 N까지의 소수를 미리 구하는 전처리 알고리즘

시간복잡도 : $O(N\log{\log{N}})$

## [CCW (CounterclockWise) Algorithm](src/수학/기하/CCW%20Algorithm.md) 🟡 Gold V
세 점이 이루는 방향이 시계 방향인지, 반시계 방향인지 판별하는 알고리즘

시간복잡도 : O(1)

## [Line Intersection](src/수학/기하/Line%20Intersection.md) 🟡 Gold II
두 선분이 서로 교차하는지 CCW를 통해 판별하는 알고리즘

시간복잡도 : O(1)

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

시간복잡도 : O(N<sup>D</sup>+Q) (N : 각 차원의 크기, D : 차원 수, Q : 쿼리 수)

## [TSP (Traveling Salesman Problem, 외판원 순회 문제)](src/DP/TSP.md) 🟡 Gold I
비트마스킹 + DP로 모든 도시를 한 번씩 순회하고 다시 시작 도시로 돌아오는 최소 비용을 계산하는 알고리즘

시간복잡도 : O(N² x $2^N$) (N : 도시의 수, $2^N$ : 가능한 방문 조합의 수)

## [Deque Trick](src/DP/Deque%20Trick.md) 🟢 Platinum V
덱에 단조 증가 또는 단조 감소하는 인덱스를 유지하여 슬라이딩 윈도우 내에서 최소값 또는 최대값을 O(1)에 찾는 알고리즘

시간복잡도 : O(N)

## [Offline Query](src/쿼리%20처리/Offline%20Query.md) 🟢 Platinum IV
복잡한 연산을 단순화하기 위해, 답에 영향을 주지 않도록 쿼리 순서를 재배열해 답을 찾는 테크닉

## [Square Root Decomposition (평방 분할, 제곱근 분할)](src/쿼리%20처리/Square%20Root%20Decomposition.md) 🟢 Platinum II
값을 √N개씩 연속된 구간들로 나누어 관리하여 특정 구간에 대한 쿼리를 O(√N) 시간에 처리하는 알고리즘

시간복잡도 : O(Q√N) (Q : 쿼리의 수)

## [Mo's Algorithm](src/쿼리%20처리/Mo's%20Algorithm.md) 🟢 Platinum II
제곱근 분할을 구간 쿼리에 적용시켜 전체 쿼리를 O(Q√N) 시간에 해결하는 알고리즘

시간복잡도 : O(Q√N)

## [PBS (Parallel Binary Search, 병렬 이분 탐색)](src/쿼리%20처리/PBS.md) 🟢 Platinum I
이분 탐색 쿼리가 여러 번 주어질 때, 각 쿼리를 개별 이분탐색하지 않고 같은 mid끼리 묶어 한 번의 검증으로 여러 쿼리를 처리하는 오프라인 기법.

시간복잡도 : O((N+Q)logC) (C : 최대 이분탐색 범위)

## License
[![CC BY-NC-SA 4.0](https://licensebuttons.net/l/by-nc-sa/4.0/88x31.png)](https://creativecommons.org/licenses/by-nc-sa/4.0/)
Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0). See LICENSE.md for more info.
