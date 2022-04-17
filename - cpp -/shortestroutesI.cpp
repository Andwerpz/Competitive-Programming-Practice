
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

vector<ll> cost;

//CSES 1671

//it's just dikjstra's algorithm.

//instead of storing node : cost pairs in a priority queue, we can define a new set comparator and save
//the cost information in a seperate array. 

//be careful when doing this though. If you only compare two items using their costs, if two items have equal
//costs, then they will be judged as equal, and only one of them will be allowed to exist within the set. 

//so when defining the comparator, you also need to check whether the two node ids are equal. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, ll>>> c(n, vector<pair<int, ll>>());
    for(int i = 0; i < m; i++){
        int a, b, w;
        cin >> a >> b >> w;
        a --;
        b --;
        c[a].push_back({b, (ll) w});
    }
    cost = vector<ll>(n, (ll) 1e18);
    cost[0] = 0;
    auto compare = [] (int a, int b) {return cost[a] != cost[b]? cost[a] < cost[b] : a < b;};
    set<int, decltype(compare)> q(compare);
    q.insert(0);
    vector<bool> v(n);
    while(q.size() != 0) {
        // for(int i : q){
        //     cout << i << " : " << cost[i] << endl;
        // }
        int curNode = *q.begin();
        ll curCost = cost[curNode];
        //cout << "Visiting: " << curNode << endl;
        q.erase(curNode);
        v[curNode] = true;
        for(auto [nNode, nCost] : c[curNode]){
            //cout << "Next: " << nNode << " New Cost: " << (curCost + nCost) << endl;
            if(cost[nNode] > curCost + nCost){
                if(q.find(nNode) != q.end()){
                    q.erase(nNode);
                    cost[nNode] = curCost + nCost;
                    q.insert(nNode);
                    //cout << "Updating: " << nNode << " Success: " << (q.find(nNode) != q.end()) << endl;
                }
                else{
                    cost[nNode] = curCost + nCost;
                }
            }
            if(!v[nNode]){
                if(q.find(nNode) == q.end()){
                    q.insert(nNode);
                }
            }
        }
        //cout << endl;
    }
    //cout << endl;
    for(ll i : cost){
        cout << i << " ";
    }
    cout << endl;
    
    return 0;
}
