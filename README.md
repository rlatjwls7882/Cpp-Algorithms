# Well-Known 알고리즘 정리

## 목표
* 증명보다는 알고리즘 구현 위주로 설명 추가
* 알고리즘 복습 및 추가 (LCA, BCC, EEA, ...)
* 기초 알고리즘도 추가 (dp, two pointer, MST(Kruskal, Prim, Solin), sweeping, imos, ...)

## 목차
* 기본 알고리즘
  * Binary Search (이분 탐색)
  * Prefix Sum (누적 합)
  * DSU (Disjoint Set Union, 분리 집합)
  * Backtracking (백트래킹)
* 그래프
  * 경로 탐색
    * 기본 탐색
      * DFS (Depth First Search, 깊이 우선 탐색)
      * BFS (Breadth First Search, 너비 우선 탐색)
    * 최단 경로
      * Dijkstra's Algorithm
      * Bellman-Ford Algorithm
      * Floyd-Warshall Algorithm
      * SPFA (Shortest Path Faster Algorithm)
  * DAG(Directed Acyclic Graph)
    * Kahn’s Algorithm (Topological Sort, 위상 정렬)
  * 유량
    * Kuhn's Algorithm (Maximum Bipartite Matching, 이분 매칭)
    * Edmonds-Karp Algorithm
    * Dinic's Algorithm
    * MCMF (Min Cost Max Flow) Algorithm
  * 컴포넌트 분해
    * Tarjan’s Algorithm (SCC)
    * 2-SAT (2-Satisfiability Problem)
  * 트리
    * Segment Tree
    * Lazy Propagation
    * Merge Sort Tree
    * HLD (Heavy Light Decomposition)
* 문자열
  * KMP (Knuth-Morris-Pratt) Algorithm
  * Trie
  * Aho-Corasick
* 기하
  * CCW (Counter ClockWise) Algorithm
  * Line Intersection
  * Graham's scan (Convex Hull, 볼록껍질)
* DP
  * TSP (Traveling Salesman Problem, 외판원 순회 문제)
  * Deque Trick
* 쿼리 처리
  * Offline Query
  * Sqrt Decomposition (Square Root Decomposition, 평방 분할)
  * Mo's Algorithm
  * Parallel Binary Search (병렬 이분 탐색)

## [Binary Search (이분 탐색)](src/기본%20알고리즘/Binary%20Search.md)
정렬된 데이터에서 원하는 값을 찾기 위해 탐색 범위를 절반씩 줄여가는 알고리즘

시간복잡도 : O(MlogN) (N : 데이터 개수, M : 탐색 횟수)

## [Prefix Sum (누적 합)](src/기본%20알고리즘/Prefix%20Sum.md)
배열의 각 인덱스까지의 합을 미리 계산해 두어, 임의 구간의 합을 O(1)에 구하는 알고리즘

시간복잡도 : 전처리 O(N), 쿼리 O(1) (N : 데이터 개수)

## [DSU (Disjoint Set Union, 분리 집합)](src/기본%20알고리즘/Disjoint%20Set%20Union.md)
서로 겹치지 않는 집합을 관리하고 합치거나 찾는 연산을 효율적으로 처리하는 자료구조

시간복잡도 : O(α(N)) (α : 역아커만 함수 ≒ 상수 시간, N : 데이터 개수)

## [Backtracking (백트래킹)](src/기본%20알고리즘/Backtracking.md)
모든 경우를 탐색하되, 해답이 될 수 없는 경로는 중간에 가지치기하여 탐색을 중단하는 완전 탐색 알고리즘

시간복잡도 : 최악 O(Kⁿ) (K : 선택지 개수, n : 깊이)

## [DFS (Depth First Search, 깊이 우선 탐색)](src/그래프/경로%20탐색/기본%20탐색/DFS.md)
그래프에서 한 정점점에서 한 경로를 끝까지 따라간 뒤 막히면 이전 분기점으로 되돌아가 다른 분기를 탐색하는 알고리즘

시간복잡도 : O(V+E) (V : 정점 수, E : 간선 수)

## [BFS (Breadth First Search, 너비 우선 탐색)](src/그래프/경로%20탐색/기본%20탐색/BFS.md)
그래프에서 시작 정점에서 가까운 정점부터 차례대로 탐색하는 알고리즘

시간복잡도 : O(V+E) (V : 정점 수, E : 간선 수)

## [Dijkstra's Algorithm](src/그래프/경로%20탐색/최단%20경로/Dijkstra's%20Algorithm.md)
가중치가 음수가 없는 그래프에서, 시작 정점으로부터 누적 거리가 가장 짧은 정점부터 차례대로 탐색하여 최단 거리를 구하는 알고리즘

시간복잡도 : O(ElogV) (V : 정점 수, E : 간선 수)

## [Bellman-Ford Algorithm](src/그래프/경로%20탐색/최단%20경로/Bellman-Ford%20Algorithm.md)
가중치가 음수인 그래프에서도, 모든 간선을 최대 V-1번 완화해 최단 거리를 구하고 음수 사이클 여부를 판별하는 알고리즘

시간복잡도 : O(VE) (V : 정점 수, E : 간선 수)

## [Floyd-Warshall Algorithm](src/그래프/경로%20탐색/최단%20경로/Floyd-Warshall%20Algorithm.md)
모든 정점 쌍 사이의 최단 거리를 DP로 구하는 알고리즘

시간복잡도 : O(V³), 공간복잡도 : O(V²)

## [SPFA (Shortest Path Faster Algorithm)](src/그래프/경로%20탐색/최단%20경로/SPFA.md)
큐를 사용해 Bellman-Ford의 간선 완화를 [휴리스틱](https://en.wikipedia.org/wiki/Heuristic_(computer_science))으로 가속하여 최단 거리를 구하는 알고리즘

시간복잡도 : 경험적 평균 O(V+E), 최악 O(VE) (V : 정점 수, E : 간선 수)

## [Kahn’s Algorithm (Topological Sort, 위상 정렬)](src/그래프/DAG/Kahn’s%20Algorithm.md)
방향성이 있고 사이클이 없는 그래프[(DAG)](https://ko.wikipedia.org/wiki/유향_비순환_그래프)에서, 모든 정점을 선행 관계를 만족하도록 나열하는 알고리즘

시간복잡도 : O(V+E) (V : 정점 수, E : 간선 수)

## [Kuhn's Algorithm (Maximum Bipartite Matching, 이분 매칭)](src/그래프/유량/Kuhn's%20Algorithm.md)
그래프를 [이분 그래프](https://ko.wikipedia.org/wiki/이분_그래프)로 나타내었을 때 최대 매칭 수(왼쪽 정점과 오른쪽 정점의 쌍의 수)를 찾는 알고리즘

시간복잡도 : O(VE) (V : 양쪽 그룹 중 더 큰 정점의 크기)

## [Edmonds-Karp Algorithm](src/그래프/유량/Edmonds-Karp%20Algorithm.md)
그래프에서 시작 지점에서 유량을 흘려서, 도착지점까지 유량이 얼마나 도착하는지 찾는 알고리즘

시간복잡도 : O(VE²)

## [Dinic's Algorithm](src/그래프/유량/Dinic's%20Algorithm.md)
Edmonds-Karp 알고리즘을 최적화한 알고리즘

시간복잡도 : O(V²E)

## [MCMF (Min Cost Max Flow) Algorithm](src/그래프/유량/MCMF%20Algorithm.md)
Edmonds-Karp 알고리즘에 SPFA(Shortest Path Faster Algorithm)를 합쳐 최대의 유량을 흘리면서, 그 중에서 최소 비용을 찾는 알고리즘

시간복잡도 : O(FVE) (F : 최대 유량)

## [Tarjan’s Algorithm (SCC)](src/그래프/컴포넌트%20분해/Tarjan’s%20Algorithm.md)
그래프에서 나타나는 [SCC (Strongly Connected Component)](https://ko.wikipedia.org/wiki/강한_연결_요소)을 한번의 dfs로 뽑아내는 알고리즘

시간복잡도 : O(V+E) (V : 정점 수, E : 간선 수)

## [2-SAT (2-Satisfiability Problem)](src/그래프/컴포넌트%20분해/2-SAT.md)
2개의 변수로 이루어진 [CNF](https://ko.wikipedia.org/wiki/논리곱_표준형)가 주어졌을 때, 이를 만족시도록 변수에 (True/False)를 대입 가능한지 [Implication Graph](https://en.wikipedia.org/wiki/Implication_graph)를 만들어 SCC를 형성해 확인하는 문제

시간복잡도 : O(V+E) (V : 정점 수, E : 간선 수)

## [Segment Tree](src/그래프/트리/Segment%20Tree.md)
포화 이진 트리 구조를 이용하여 구간 쿼리를 최적화하는 알고리즘

시간복잡도 : O(QlogN) (Q : 쿼리의 수)

## [Lazy Propagation](src/그래프/트리/Lazy%20Propagation.md)
세그먼트 트리에서 구간 업데이트를 지연 방식으로 처리하여, 최적화하는 알고리즘 

시간복잡도 : O(QlogN) (Q : 쿼리의 수)

## [Merge Sort Tree](src/그래프/트리/Merge%20Sort%20Tree.md)
세그먼트 트리에 합병 정렬된 내용을 담아 범위탐색 시간을 줄인 알고리즘 

시간복잡도 : O(NlogN), 공간복잡도 : O(NlogN)

## [HLD (Heavy Light Decomposition)](src/그래프/트리/HLD.md)
트리에서 세그먼트 트리로 구간 쿼리를 최적화하는 알고리즘

시간복잡도 : O(Qlog²N) (Q : 쿼리의 수)

## [KMP (Knuth-Morris-Pratt) Algorithm](src/문자열/KMP(Knuth-Morris-Pratt%20Algorithm).md)
한 문자열에서 다른 문자열이 어디에 등장하는지 찾아주는 문자열 검색 알고리즘

시간복잡도 : O(N+M) (N+M : 두 문자열의 길이 합)

## [Trie](src/문자열/Trie.md)
여러 문자열을 공통 접두사로 압축해 저장하는 자료구조

시간복잡도 : O(S) (S : 모든 문자열의 길이)

## [Aho-Corasick](src/문자열/Aho-Corasick.md)
Trie구조에 실패함수를 추가한 일대다 패턴매칭 알고리즘

시간복잡도 : O(S) (S : 모든 문자열의 길이)

## [CCW (Counter ClockWise) Algorithm](src/기하/CCW(Counter%20ClockWise)%20Algorithm.md)
세 점이 이루는 방향이 시계 방향인지, 반시계 방향인지 판별하는 알고리즘

시간복잡도 : O(1)

## [Line Intersection](src/기하/Line%20Intersection.md)
두 선분이 서로 교차하는지 CCW를 통해 판별하는 알고리즘

시간복잡도 : O(1)

## [Graham's scan (Convex Hull)](src/기하/Graham's%20scan%20(Convex%20Hull).md)
기준점을 잡아 점들을 각도로 정렬한 후, 스택을 이용해 볼록 껍질의 방향성을 유지하지 않는 점을 제거하며 볼록 껍질을 찾는 알고리즘

시간복잡도 : O(NlogN)

## [TSP (Traveling Salesman Problem, 외판원 순회 문제)](src/DP/TSP.md)
비트마스킹 + DP로 모든 도시를 한 번씩 순회하고 다시 시작 도시로 돌아오는 최소 비용을 계산하는 알고리즘

시간복잡도 : O(N x 2<sup>N</sup>)

## [Deque Trick](src/DP/Deque%20Trick.md)
덱에 단조 증가 또는 단조 감소하는 인덱스를 유지하여 슬라이딩 윈도우 내에서 최소값 또는 최대값을 O(1)에 찾는 알고리즘

시간복잡도 : O(N)

## [Offline Query](src/쿼리%20처리/Offline%20Query.md)
복잡한 연산을 단순화하기 위해, 쿼리의 처리 순서를 바꿔 답을 찾는 테크닉

## [Sqrt Decomposition (Square Root Decomposition)](src/쿼리%20처리/Sqrt%20Decomposition(Square%20Root%20Decomposition).md)
값을 √N개씩 연속된 구간들로 나누어 관리하여 특정 구간에 대한 쿼리를 O(√N) 시간에 처리하는 알고리즘

시간복잡도 : O(Q√N) (Q : 쿼리의 수)

## [Mo's Algorithm](src/쿼리%20처리/Mo's%20Algorithm.md)
Sqrt Decomposition을 구간 쿼리에 적용시켜 전체 쿼리를 O(Q√N) 시간에 해결하는 알고리즘

시간복잡도 : O(Q√N)

## [Parallel Binary Search (병렬 이분 탐색)](src/쿼리%20처리/Parallel%20Binary%20Search.md)
이분 탐색 쿼리가 여러 번 주어질 때, 중복되는 부분을 최소화하는 알고리즘

시간복잡도 : O((N+Q)logN)
