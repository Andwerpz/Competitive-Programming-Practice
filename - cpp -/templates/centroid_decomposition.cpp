#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//useful for problems involving queries centered around specific nodes in a tree. 

//if we want to answer queries of type
//1 : color some node red
//2 : query some node for the closest red node
//then we'd want to use bottom up. When coloring, update all your centroid ancestors as to what
//red node is closest to them. When answering queries, look for the nearest red node to each centroid ancestor.

//if we want to compute some property for every node in the tree, then top down divide + conquer is good.
//refer to cielthecommander.cpp

struct CentroidDecomp {
    CentroidDecomp() {
        //yay
    }

    vector<bool> vis;
    vector<int> centroid_parent;
    vector<int> size;   //size of subtree in original tree
    vector<vector<int>> edges;

    int find_size(int cur, int p = -1) {
        if(vis[cur]) {
            return 0;
        }
        size[cur] = 1;
        for(int i = 0; i < edges[cur].size(); i++){
            int next = edges[cur][i];
            if(next != p){
                size[cur] += find_size(next, cur);
            }
        }
        return size[cur];
    }

    int find_centroid(int cur, int p, int sub_size) {
        for(int i = 0; i < edges[cur].size(); i++){
            int next = edges[cur][i];
            if(next == p){
                continue;
            }
            if(!vis[next] && size[next] > sub_size / 2) {
                return find_centroid(next, cur, sub_size);
            }
        }
        return cur;
    }

    void init_centroid(int cur, int p = -1) {
        find_size(cur);
        int centroid = find_centroid(cur, -1, size[cur]);
        vis[centroid] = true;
        centroid_parent[centroid] = p;
        for(int i = 0; i < edges[centroid].size(); i++){
            int next = edges[centroid][i];
            if(!vis[next]){
                init_centroid(next, centroid);
            }
            
        }
    }

    //returns an array 'a' where the parent of node i is a[i]. 
    //if i is the root, then a[i] = -1. 
    vector<int> calc_centroid_decomp(int n, vector<vector<int>>& adj_list) {
        edges = adj_list;
        vis = vector<bool>(n, false);
        centroid_parent = vector<int>(n, -1);
        size = vector<int>(n, -1);
        init_centroid(0);
        return centroid_parent;
    }
};

//takes in adjacency list, returns a list of the centroids of the tree. 
vector<int> findCentroid(const vector<vector<int>> &g) {
    int n = g.size();
    vector<int> centroid;
    vector<int> sz(n);
    function<void (int, int)> dfs = [&](int u, int prev) {
            sz[u] = 1;
            bool is_centroid = true;
            for (auto v : g[u]) if (v != prev) {
                    dfs(v, u);
                    sz[u] += sz[v];
                    if (sz[v] > n / 2) is_centroid = false;
            }
            if (n - sz[u] > n / 2) is_centroid = false;
            if (is_centroid) centroid.push_back(u);
    };
    dfs(0, -1);
    return centroid;
}
