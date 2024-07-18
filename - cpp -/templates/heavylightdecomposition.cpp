#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

#include "lca.cpp"
#include "segtreelazy.cpp"

// -- REMEMBER -- 
//always check that the lazysegtree settings are exactly what you need. 
//don't forget to modify the range combine function. 

//a relatively kinda dumb implementation of heavy-light decomposition. 
//note that this implementation is not very optimized; you'll probably TLE on tight time constraints. 
//O(log(n)) query, O(log(n)^2) modify any path along the tree. 

template <typename T>
struct HLD {
    LCA lca;
    vector<vector<int>> edges;
    vector<bool> toParentHeavy;
    vector<bool> hasOutHeavy;
    vector<int> parent;
    vector<int> subtreeSize;

    SegtreeLazy<T> segt;
    vector<int> segEndInd; //stores the index at which this heavy path ends. 
    vector<int> segBeginInd; //stores the index at which this heavy path begins.
    vector<int> segParent; //what is the parent node of this heavy path?
    vector<int> segPos;    //stores the index of each node within the segment tree. 

    vector<T> maxSegCache;    //stores results to segments which take up the entire heavy path

    void calcSubtreeSize(int cur, int p = -1) {
        parent[cur] = p;
        subtreeSize[cur] = 1;
        for(int i = 0; i < edges[cur].size(); i++){
            int next = edges[cur][i];
            if(next == p){
                continue;
            }
            calcSubtreeSize(next, cur);
            subtreeSize[cur] += subtreeSize[next];
        }
    }

    void calcHLD(int cur, int p = -1) {
        for(int i = 0; i < edges[cur].size(); i++){
            int next = edges[cur][i];
            if(next == p){
                continue;
            }
            if(subtreeSize[next] > subtreeSize[cur] / 2) {
                hasOutHeavy[cur] = true;
                toParentHeavy[next] = true;
            }
            calcHLD(next, cur);
        }
    }

    HLD(int n, int root, vector<vector<int>> adjList, T updateNeutral, T queryNeutral, T initVal, function<T(T, T)> fmodify, function<T(T, T, int)> fmodifyk, function<T(T, T)> fcombine) {
        this->lca = LCA(n, root, adjList);
        
        this->edges = adjList;
        this->parent = vector<int>(n, -1);
        this->subtreeSize = vector<int>(n, 0);
        this->toParentHeavy = vector<bool>(n, false);
        this->hasOutHeavy = vector<bool>(n, false);
        this->calcSubtreeSize(root);
        this->calcHLD(root);

        //create the segment tree needed to do the range updates. 
        this->segt = SegtreeLazy<T>(n, updateNeutral, queryNeutral, initVal, fmodify, fmodifyk, fcombine);
        this->segBeginInd = vector<int>(n, -1);
        this->segEndInd = vector<int>(n, -1);
        this->segParent = vector<int>(n, -1);
        this->segPos = vector<int>(n, -1);

        //find the positions of the nodes in the segment tree. 
        int posPtr = 0;
        for(int i = 0; i < n; i++){
            if(this->hasOutHeavy[i]) {
                //we want to have each heavy path be contiguous in the segment tree, so we want to start at the beginning. 
                continue;
            }
            int begin = posPtr;
            int cur = i;
            vector<int> heavyPath(0);
            heavyPath.push_back(cur);
            this->segPos[cur] = posPtr ++;
            while(toParentHeavy[cur]) {
                cur = parent[cur];
                heavyPath.push_back(cur);
                this->segPos[cur] = posPtr ++;
            }
            cur = parent[cur];
            for(int j = 0; j < heavyPath.size(); j++){
                this->segBeginInd[heavyPath[j]] = begin;
                this->segEndInd[heavyPath[j]] = posPtr;
                this->segParent[heavyPath[j]] = cur;
            }
        }

        //compute max cache values
        this->maxSegCache = vector<T>(n);
        for(int i = 0; i < n; i++){
            if(this->segPos[i] == this->segBeginInd[i]) {
                int begin = this->segBeginInd[i];
                int end = this->segEndInd[i];
                this->maxSegCache[begin] = this->segt.query(begin, end);
            }
        }
    }

    void modify(int a, int b, T val) {
        int _lca = this->lca.lca(a, b);
        _modify(a, _lca, val);
        _modify(b, _lca, val);
        this->modify(_lca, val);
    }

    void modify(int a, T val) {
        this->segt.modify(this->segPos[a], val);

        //update cache
        int begin = this->segBeginInd[a];
        int end = this->segEndInd[a];
        this->maxSegCache[begin] = this->segt.query(begin, end);
    }

    T query(int a, int b) {
        int _lca = this->lca.lca(a, b);
        T ret = this->segt.qneut;
        ret = this->segt.fcombine(ret, _query(a, _lca));
        ret = this->segt.fcombine(ret, _query(b, _lca));
        ret = this->segt.fcombine(ret, this->query(_lca));
        return ret;
    }

    T query(int a) {
        return this->segt.query(this->segPos[a]);
    }

    private:
        void _modify(int a, int _lca, int val) {
            //while a and _lca aren't in the same heavy path
            while(this->segEndInd[a] != this->segEndInd[_lca]) {
                //modify until the end of the segment a belongs to. 
                this->segt.modify(this->segPos[a], this->segEndInd[a], val);
                a = this->segParent[a];

                //update cache
                int begin = this->segBeginInd[a];
                int end = this->segEndInd[a];
                this->maxSegCache[begin] = this->segt.query(begin, end);
            }
            //a and _lca are in the same heavy path. Now, just modify the segment from a to _lca, not including _lca. 
            this->segt.modify(this->segPos[a], this->segPos[_lca], val);
        }

        T _query(int a, int _lca) {
            T ret = this->segt.qneut;
            while(this->segEndInd[a] != this->segEndInd[_lca]) {
                //see if we can use the cache
                if(this->segBeginInd[a] == this->segPos[a]) {
                    //use the cache
                    ret = this->segt.fcombine(ret, this->maxSegCache[this->segBeginInd[a]]);
                }
                else {
                    ret = this->segt.fcombine(ret, this->segt.query(this->segPos[a], this->segEndInd[a]));
                }
                a = this->segParent[a];
            }
            ret = this->segt.fcombine(ret, this->segt.query(this->segPos[a], this->segPos[_lca]));
            return ret;
        }
};

int main() {

    int n = 100;
    vector<vector<int>> c(n, vector<int>(0));   //placeholder adjacency list

    // -- ASSIGNMENT MODIFY, MAXIMUM QUERY --
    {
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
        function<int(int, int, int)> fmodifyk = [](const int src, const int val, const int k) -> int{return val;};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return max(a, b);};
        HLD<int> hld(n, 0, {}, 0, -1e9, 0, fmodify, fmodifyk, fcombine);
    }

    return 0;
}