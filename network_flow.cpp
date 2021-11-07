// This file is an instance of solving the network flow problem

#include <bits/stdc++.h>
#include "network_flow.h"

namespace Arrange {

Graph::Graph() {
    for (int i = 0; i <= MAX_SIZE; i++) {
        pre[i] = -1;
        visit[i] = false;
        for (int j = 0; j <= MAX_SIZE; j++) {
            edge[i][j] = 0;
            flow[i][j] = 0;
        }
    }
}

bool Graph::bfs(int num_vtx, int src, int dest) {
    std::queue<int> q;
    for (int i = 0; i < num_vtx; i++) {
    	pre[i] = -1;
    	visit[i] = false;
	}
    pre[src] = src;
    visit[src] = true;
    q.push(src);
    while(!q.empty()) {
        int p = q.front();
        q.pop();
        for (int i = 0; i < num_vtx; i++) {
        	int u = (p + i) % num_vtx;
            if (edge[p][u] > 0 && !visit[u]) {
                pre[u] = p;
                visit[u] = true;
                if (u == dest)
                    return true;
                q.push(u);
            }
        }
    }
    return false;
}

void Graph::EdmondsKarp(int num_vtx, int src, int dest) {
    while (bfs(num_vtx, src, dest)) {
        for (int i = dest; i != src; i = pre[i]) {
            edge[pre[i]][i]--;
            flow[pre[i]][i]++;
            edge[i][pre[i]]++;
            flow[i][pre[i]]--;
        }
    }
}

} // namespace Graph