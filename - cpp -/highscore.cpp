#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSES - 1673

//we can use the bellman ford algorithm to find the maximum cost path from node 1 to n. 
//if after n * m iterations, we still have to relax path costs, then it means that there is an infinite positive loop. 

//the problem with this is that there might be an infinite loop that once entered, you can't actually get to
//the exit node, meaning that a valid path doesn't include that loop. We can solve this by first looking for
//what nodes can visit the exit node, and do the bellman ford algorithm over only those nodes. 

//to find which nodes can visit the exit node, you can just reverse the directions of all the edges, and do
//bfs on that graph starting from the exit. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> c(n, vector<pair<int, int>>(0));
    vector<vector<pair<int, int>>> cReverse(n, vector<pair<int, int>>(0));
    for(int i = 0; i < m; i++){
        int a, b, cost;
        cin >> a >> b >> cost;
        a --;
        b --;
        c[a].push_back({b, cost});
        cReverse[b].push_back({a, cost});
    }
    set<int> canVisitEnd;
    queue<int> q;
    q.push(n - 1);
    vector<bool> v(n, false);
    v[n - 1] = true;
    canVisitEnd.insert(n - 1);
    while(q.size() != 0){
        int cur = q.front();
        //cout << cur << " : ";
        q.pop();
        for(pair<int, int> i : cReverse[cur]) {
            //cout << i.first << " ";
            if(!v[i.first]){
                v[i.first] = true;
                canVisitEnd.insert(i.first);
                q.push(i.first);
            }
        }
        //cout << "\n";
    }
    // for(int i : canVisitEnd){
    //     cout << i << endl;
    // }
    set<int> inQueue;
    vector<ll> dist(n, 0);
    v = vector<bool>(n, false);
    v[0] = true;
    q.push(0);
    int cnt = 0;
    bool infLoop = false;
    while(q.size() != 0 && cnt < n * m && !infLoop){
        cnt ++;
        int cur = q.front();
        q.pop();
        inQueue.erase(cur);
        for(pair<int, int> i : c[cur]) {
            if(canVisitEnd.find(i.first) == canVisitEnd.end()){
                continue;
            }
            if(!v[i.first] || (dist[cur] + i.second > dist[i.first])) {
                if(i.first == 0){
                    infLoop = true;
                }
                v[i.first] = true;
                dist[i.first] = dist[cur] + i.second;
                if(inQueue.find(i.first) == inQueue.end()) {
                    inQueue.insert(i.first);
                    q.push(i.first);
                }
            }
        }
    }
    if(q.size() != 0 || !v[n - 1] || infLoop){
        cout << "-1\n";
    }
    else{
        cout << dist[n - 1] << "\n";
    }
    
    return 0;
}
