#ifndef NETWORK_FLOW_H_
#define NETWORK_FLOW_H_

#include <bits/stdc++.h>
#define MAX_SIZE 1000

namespace Arrange {

class Graph {
  public:
    Graph();
    bool bfs(int, int, int);
    void EdmondsKarp(int, int, int);
    int edge[MAX_SIZE][MAX_SIZE];   // Store graph edge info
    int flow[MAX_SIZE][MAX_SIZE];   // Store flows
    // For finding augmenting path using BFS
    int pre[MAX_SIZE];              // Store the pre-vertex in augmenting path
    int visit[MAX_SIZE];            // If the vertex is visited before
};

} // namespace Arrange

#endif // NETWORK_FLOW_H_