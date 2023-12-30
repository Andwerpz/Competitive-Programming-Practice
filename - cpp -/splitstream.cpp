#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2021 - J

//we can just naively compute the answer for each query. 

//just determine the position of the requested character in the stream and traverse all the way up to the base
//input stream, and return the answer. 

//to do this, we probably want to precompute for each stream, the total size of the stream. We do this to properly
//handle splits and merges. 

struct Node;
struct Edge;

vector<Node> nodes;
vector<Edge> edges(1e6);

struct Edge {
    int parent = -1; //points to nodes
    int child = -1; //points to nodes
    int size = 0;
    int id = -1;

    Edge() {

    }

    int query(int k);
};

struct Node {
    int size = -1;
    int x = -1, y = -1, z = -1; //IDs of edges x, y, z
    bool isSplit = false;
    bool isMerge = false;
    int id = -1;

    Node() {

    }

    int query(int k) {
        //cout << "QUERY NODE : " << this->id << " " << k << " " << size << "\n";
        if(k >= size) return -1;
        //return value at index k
        if(isSplit) {
            return edges[x].query((k));
        } else {
            int lastalternating = min(edges[x].size, edges[y].size) * 2;
            if(k < lastalternating) {
                if(k % 2 == 0){
                    return edges[x].query(k / 2);
                }
                else {
                    return edges[y].query(k / 2);
                }
            }
            else {
                if(edges[y].size > edges[x].size) {
                    return edges[y].query(k - lastalternating / 2);
                }
                else {
                    return edges[x].query(k - lastalternating / 2);
                }
            }
        }
    }

};

int Edge::query(int k) {
    //cout << "QUERY EDGE : " << this->id << " " << k << " " << size << "\n";
    if(parent == -1) {
        return k + 1;
    }
    if(nodes[parent].isSplit) {
        if(nodes[parent].y == id) {//left node from split
            return nodes[parent].query(k * 2);
        } else {
            return nodes[parent].query(k * 2 + 1);
        }
    } else {
        return nodes[parent].query(k);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int m, n, Q; cin >> m >> n >> Q;

    for(int i = 0; i < n; i++) {
        char type; cin >> type;
        int x, y, z; cin >> x >> y >> z;
        x--; y--; z--;
        if(type == 'S') {
            edges[x].child = nodes.size(); edges[x].id = x;
            edges[y].parent = nodes.size(); edges[y].id = y;
            edges[z].parent = nodes.size(); edges[z].id = z;
            Node node;
            node.id = i;
            node.x = x;
            node.y = y;
            node.z = z;
            node.isSplit = true;
            node.size = 0;
            nodes.push_back(node);
        } else if(type == 'M') {
            edges[x].child = nodes.size(); edges[x].id = x;
            edges[y].child = nodes.size(); edges[y].id = y;
            edges[z].parent = nodes.size(); edges[z].id = z;
            Node node;
            node.id = i;
            node.x = x;
            node.y = y;
            node.z = z;
            node.isMerge = true;
            node.size = 0;
            nodes.push_back(node);
        }
    }
    edges[0].size = m;
    nodes[edges[0].child].size += edges[0].size;
    vector<int> indegree(n, 0);
    queue<int> q;
    for(int i = 0; i < n; i++){
        indegree[i] = (nodes[i].isSplit? 1 : 2);
        if(nodes[i].isSplit) {
            if(nodes[i].x == 0) {
                indegree[i] --;
            }
        }
        else {
            if(nodes[i].x == 0){
                indegree[i] --;
            }
            if(nodes[i].y == 0){
                indegree[i] --;
            }
        }
        if(indegree[i] == 0){
            q.push(i);
        }
    }
    vector<bool> visited(1e5);
    while(q.size()) {
        int cur = q.front();
        q.pop();
        if(nodes[cur].isSplit) {
            int y = nodes[cur].y;
            int z = nodes[cur].z;
            edges[y].size += nodes[cur].size / 2;
            edges[z].size += nodes[cur].size / 2;
            if(nodes[cur].size % 2 == 1) {
                edges[y].size ++;
            }
            if(edges[y].child != -1) {
                nodes[edges[y].child].size += edges[y].size;
                indegree[edges[y].child] --;
                if(indegree[edges[y].child] == 0) {
                    q.push(edges[y].child);
                }
            }
            if(edges[z].child != -1){
                nodes[edges[z].child].size += edges[z].size;
                indegree[edges[z].child] --;
                if(indegree[edges[z].child] == 0){
                    q.push(edges[z].child);
                }
            }
        }
        else {
            int z = nodes[cur].z;
            edges[z].size += nodes[cur].size;
            if(edges[z].child != -1){
                nodes[edges[z].child].size += edges[z].size;
                indegree[edges[z].child] --;
                if(indegree[edges[z].child] == 0){
                    q.push(edges[z].child);
                }
            }
        }
    }
    for(int i = 0; i < Q; i++){
        int ind, k;
        cin >> ind >> k;
        ind --;
        k --;
        int ans = edges[ind].query(k);
        if(ans == -1){
            cout << "none\n";
        }
        else {
            cout << ans << "\n";
        }
    }

    
    return 0;
}
