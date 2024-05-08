#include <bits/stdc++.h>
using namespace std;

//Kattis - thekingofthenorth

//max flow problem. 

typedef long long ll;

template<class T> void printVector(const vector<T>& vec){
    for (size_t i = 0; i < vec.size(); ++i){
        cout << "currentIndex: " << i << ", value: " << vec[i] << "\n";
    }
}

void printGraph(const vector<vector<pair<size_t, long>>>& graph){
    for (size_t i = 0; i < graph.size(); ++ i){
        if (graph[i].size() > 0){
            cout << "currentIndex: " << i << "[";
            for (size_t j = 0; j < graph[i].size() - 1; ++j){
                cout << "(" << graph[i][j].first << ", " << graph[i][j].second << "), ";
            }
            cout << "(" << graph[i][graph[i].size() - 1].first << ", " << graph[i][graph[i].size() - 1].second << ")]\n";
        } else {
            cout << "currentIndex: " << i << "[]\n";
        }
    }
}

ll dinic(int n, vector<vector<pair<int, ll>>> c, int source, int sink) {
    ll ans = 0;
    //redo organization of edges
    vector<pair<int, ll>> edges(0);
    vector<vector<int>> adj(n, vector<int>(0));
    int m = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < c[i].size(); j++){
            int u = i;
            int v = c[i][j].first;
            ll cap = c[i][j].second;
            adj[u].push_back(m);
            adj[v].push_back(m + 1);
            edges.push_back({v, cap});
            edges.push_back({u, 0});
            m += 2;
        }
    }
    while(true) {
        //create level graph
        vector<int> level(n, -1);
        queue<int> q;
        vector<bool> v(n, false);
        v[source] = true;
        q.push(source);
        level[source] = 0;
        while(q.size() != 0){
            int cur = q.front();
            q.pop();
            for(int i = 0; i < adj[cur].size(); i++) {
                int nEdge = adj[cur][i];
                int next = edges[nEdge].first;
                if(v[next]) {
                    continue;
                }
                if(edges[nEdge].second == 0){
                    //no flow
                    continue;
                }
                v[next] = true;
                q.push(next);
                level[next] = level[cur] + 1;
            }
        }
        if(!v[sink]){
            //we're done here
            break;
        }
        while(true) {
            //do dfs until there is no path from source to sink along level graph
            stack<int> s;
            s.push(source);
            stack<int> est;
            stack<int> ist;
            ist.push(0);
            while(s.size() != 0){
                int cur = s.top();
                if(cur == sink) {   
                    //we've found path from source to sink
                    break;
                }
                bool foundNext = false;
                for(int i = ist.top(); i < adj[cur].size(); i++){
                    int nEdge = adj[cur][i];
                    int next = edges[nEdge].first;
                    if(level[next] <= level[cur]){
                        continue;
                    }
                    if(edges[nEdge].second == 0){
                        continue;
                    }
                    s.push(next);
                    est.push(nEdge);
                    ist.pop();
                    ist.push(i + 1);
                    ist.push(0);
                    foundNext = true;
                    break;
                }
                if(!foundNext) {
                    s.pop();
                    ist.pop();
                    if(est.size() != 0){
                        est.pop();
                    }
                    //mark this node as a dead end
                    level[cur] = -1;
                }
            }
            if(s.size() != 0 && s.top() == sink) {
                //found a path yay, now we update flow for edges on path
                ll bn = 1e18;
                vector<int> path(est.size(), 0);
                for(int i = 0; i < path.size(); i++){
                    path[i] = est.top();
                    est.pop();
                    bn = min(bn, edges[path[i]].second);
                }
                for(int i = 0; i < path.size(); i++){
                    //forward edge
                    edges[path[i]].second -= bn;
                    //backwards edge
                    edges[path[i] ^ 1].second += bn;
                }
                ans += bn;
            }
            else {
                //the maximum flow for this level configuration has been reached. 
                break;
            }
        }
    }
    return ans;
}

int main(){
    // input
    size_t numRows, numCols;
    cin >> numRows >> numCols;
    
    // graph initialization
     /*
        graph[0] to graph[numRows * numCols - 1] are inNodes
        graph[numRows * numCols] to graph[2 * numRows * numCols - 1] are outNodes
        graph[2 * numRows * numCols] is super source
    */
    vector<vector<pair<int, ll>>> graph(numRows * numCols * 2 + 1, vector<pair<int, ll>>(0));
    // graph construction
    size_t srcIndex = numRows * numCols * 2;
    for (size_t i = 0; i < numRows; ++i){
        for (size_t j = 0; j < numCols; ++j){
            // initialize node capacities
            long inNodeToOutNodeCapacity;
            cin >> inNodeToOutNodeCapacity;
            long outNodeOutCapacity = LONG_MAX;
            // index calculations
            size_t inNodeIndex = i * numCols + j;
            size_t outNodeIndex = numCols * numRows + inNodeIndex;
            // determine if the node is on the border
            if ((i == 0) || (j == 0) || (i == numRows - 1) || (j == numCols - 1)){
                // imaginary border: connect src node to this node
                graph[srcIndex].push_back(make_pair(inNodeIndex, LONG_MAX));
            }
            // inNode to outNode edge
            graph[inNodeIndex].push_back(make_pair(outNodeIndex, inNodeToOutNodeCapacity));
            // outNode to neighboring nodes
            if (i != 0){ // top neighbor
                size_t neighborIndex = (i - 1) * numCols + j;
                graph[outNodeIndex].push_back(make_pair(neighborIndex, outNodeOutCapacity));
            }
            if (i != numRows - 1){ // bottom neighbor
                size_t neighborIndex = (i + 1) * numCols + j;
                graph[outNodeIndex].push_back(make_pair(neighborIndex, outNodeOutCapacity));
            }
            if (j != 0){ // left neighbor
                size_t neighborIndex = i * numCols + (j - 1);
                graph[outNodeIndex].push_back(make_pair(neighborIndex, outNodeOutCapacity));
            }
            if (j != numCols - 1){ // right neighbor
                size_t neighborIndex = i * numCols + (j + 1);
                graph[outNodeIndex].push_back(make_pair(neighborIndex, outNodeOutCapacity));
            }
        }
    }
    // handle sink node
    size_t dstRow, dstCol;
    cin >> dstRow >> dstCol;
    size_t dstInIndex = dstRow * numCols + dstCol;
    size_t dstOutIndex = numRows * numCols + dstInIndex;
    graph[dstOutIndex].clear(); // clear the outNode of sink

    cout << dinic(graph.size(), graph, srcIndex, dstOutIndex) << "\n";
    
    // // edmonds karp
    // long maxFlow = 0;
    // while (true){
    //     // bfs
    //     queue<size_t> nextToVisit;
    //     vector<size_t> parents;
    //     vector<bool> visitedNodes;
    //     for (size_t i = 0; i < numRows * numCols * 2 + 1; ++i){
    //         parents.push_back(SIZE_MAX);
    //         visitedNodes.push_back(false);
    //     }
    //     nextToVisit.push(srcIndex);
    //     visitedNodes[srcIndex] = true;
    //     while (!nextToVisit.empty()){
    //         size_t nodeIndex = nextToVisit.front();
    //         nextToVisit.pop();
    //         if (nodeIndex == dstOutIndex) {
    //             break;
    //         }
    //         for (auto edge : graph[nodeIndex]){
    //             size_t neighborIndex = edge.first;
    //             long edgeCapacity = edge.second;
    //             if ((!visitedNodes[neighborIndex]) && (edgeCapacity > 0)){
    //                 parents[neighborIndex] = nodeIndex;
    //                 visitedNodes[neighborIndex] = true;
    //                 nextToVisit.push(neighborIndex);
    //             }
    //         }
    //     }
    //     if (parents[dstOutIndex] != dstInIndex){
    //         break;
    //     }
    //     // backtrack
    //     size_t currentNodeIndex = dstOutIndex;
    //     long minEdgeCapacity = LONG_MAX;
    //     vector<pair<size_t, size_t>> edgesToUpdate;
    //     while (currentNodeIndex != srcIndex){
    //         size_t parentNodeIndex = parents[currentNodeIndex];
    //         for (size_t i = 0; i < graph[parentNodeIndex].size(); ++i){
    //             size_t edgeTo = graph[parentNodeIndex][i].first;
    //             long edgeCapacity = graph[parentNodeIndex][i].second;
    //             if (edgeTo == currentNodeIndex){
    //                 edgesToUpdate.push_back(make_pair(parentNodeIndex, i));
    //                 minEdgeCapacity = min(minEdgeCapacity, edgeCapacity);
    //                 break;
    //             }
    //         }
    //         currentNodeIndex = parentNodeIndex;
    //     }
    //     // update maxFlow and edges
    //     maxFlow += minEdgeCapacity;
    //     for (auto edge : edgesToUpdate){
    //         size_t nodeIndex = edge.first;
    //         size_t edgeIndex = edge.second;
    //         graph[nodeIndex][edgeIndex].second -= minEdgeCapacity;
    //     }
    // }
    // cout << maxFlow << "\n";
}